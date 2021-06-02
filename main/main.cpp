/*

SPDX-License-Identifier: MIT-0

MIT No Attribution

Copyright (c) 2020 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

extern "C" {

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <esp_sntp.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/spi_master.h>

#include <i2c_helper.h>
#include <axp202.h>
#include <pcf8563.h>

#include "font8x13.h"
#include "helpers/wifi.h"
#include "helpers/nvs.h"
#include "lvgl_gui/lvgl_main.h"
#include "sdkconfig.h"

}


static const char *TAG = "main";
static float fb_fps;

pcf8563_t pcf;
axp202_t axp;
struct tm rtc = {0};
spi_device_handle_t spi;

extern "C" void set_ring_as_time(int hour,int minute,int second);

void rtc_task(void *params)
{
    // uint16_t color = rgb565(0, 255, 0);
    // char16_t message[128];

    /* Calculate tm_yday for the first run. */
    mktime(&rtc);

    while (1) {
        pcf8563_read(&pcf, &rtc);
        // swprintf(
        //     message,
        //     sizeof(message),
        //     L"%04d-%02d-%02d",
        //     rtc.tm_year + 1900, rtc.tm_mon + 1, rtc.tm_mday
        // );
        // hagl_put_text(message, 80, 100, color, font8x13);
        ESP_LOGI(TAG, "%04d-%02d-%02d", rtc.tm_year + 1900, rtc.tm_mon + 1, rtc.tm_mday);

        // swprintf(
        //     message,
        //     sizeof(message),
        //     L"%02d:%02d:%02d",
        //     rtc.tm_hour, rtc.tm_min, rtc.tm_sec
        // );
        // hagl_put_text(message, 88, 115, color, font8x13);
        ESP_LOGI(TAG, "%02d:%02d:%02d", rtc.tm_hour, rtc.tm_min, rtc.tm_sec);
        
        set_ring_as_time(rtc.tm_hour,rtc.tm_min,rtc.tm_sec);

        vTaskDelay(1000 / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

void log_task(void *params)
{
    float vacin, iacin, vvbus, ivbus, vts, vgpio0, vgpio1, temp, pbat;
    float vbat, icharge, idischarge, ipsout, cbat, fuel;
    uint8_t power, charge;
    // char buffer[128];

    while (1) {
        axp202_read(&axp, AXP202_ACIN_VOLTAGE, &vacin);
        axp202_read(&axp, AXP202_ACIN_CURRENT, &iacin);
        axp202_read(&axp, AXP202_VBUS_VOLTAGE, &vvbus);
        axp202_read(&axp, AXP202_VBUS_CURRENT, &ivbus);
        axp202_read(&axp, AXP202_TEMP, &temp);
        axp202_read(&axp, AXP202_TS_INPUT, &vts);
        axp202_read(&axp, AXP202_GPIO0_VOLTAGE, &vgpio0);
        axp202_read(&axp, AXP202_GPIO1_VOLTAGE, &vgpio1);
        axp202_read(&axp, AXP202_BATTERY_POWER, &pbat);
        axp202_read(&axp, AXP202_BATTERY_VOLTAGE, &vbat);
        axp202_read(&axp, AXP202_CHARGE_CURRENT, &icharge);
        axp202_read(&axp, AXP202_DISCHARGE_CURRENT, &idischarge);
        axp202_read(&axp, AXP202_IPSOUT_VOLTAGE, &ipsout);
        axp202_read(&axp, AXP202_COULOMB_COUNTER, &cbat);
        axp202_read(&axp, AXP202_FUEL_GAUGE, &fuel);

        ESP_LOGI(TAG,
            "vacin: %.2fV iacin: %.2fA vvbus: %.2fV ivbus: %.2fA vts: %.2fV temp: %.0fC "
            "vgpio0: %.2fV vgpio1: %.2fV pbat: %.2fmW vbat: %.2fV icharge: %.2fA "
            "idischarge: %.2fA, ipsout: %.2fV cbat: %.2fmAh fuel: %.0f%%",
            vacin, iacin, vvbus, ivbus, vts, temp, vgpio0, vgpio1, pbat, vbat, icharge,
            idischarge, ipsout, cbat, fuel
        );

        axp202_ioctl(&axp, AXP202_READ_POWER_STATUS, &power);
        axp202_ioctl(&axp, AXP202_READ_CHARGE_STATUS, &charge);
        ESP_LOGI(TAG,
            "power: 0x%02x charge: 0x%02x",
            power, charge
        );

//         strftime(buffer, 128 ,"%c (day %j)" , &rtc);
//         ESP_LOGI(TAG, "RTC: %s", buffer);

        vTaskDelay(10000 / portTICK_RATE_MS);

        ESP_LOGI(TAG, "fps: %.1f", fb_fps);
    }
    vTaskDelete(NULL);
}

static void sntp_set_rtc(struct timeval *tv)
{
    struct tm *time;

    ESP_LOGI(TAG, "Got SNTP response, setting RTC.");

    time = localtime(&tv->tv_sec);
    pcf8563_write(&pcf, time);
}


#include "bma.hpp"
bma423_t bma;
void accel_task(void *params)
{

    BMA bma423(&bma);

    bma423.begin();

    // Accel parameter structure
    Acfg cfg;
    /*!
        Output data rate in Hz, Optional parameters:
            - BMA4_OUTPUT_DATA_RATE_0_78HZ
            - BMA4_OUTPUT_DATA_RATE_1_56HZ
            - BMA4_OUTPUT_DATA_RATE_3_12HZ
            - BMA4_OUTPUT_DATA_RATE_6_25HZ
            - BMA4_OUTPUT_DATA_RATE_12_5HZ
            - BMA4_OUTPUT_DATA_RATE_25HZ
            - BMA4_OUTPUT_DATA_RATE_50HZ
            - BMA4_OUTPUT_DATA_RATE_100HZ
            - BMA4_OUTPUT_DATA_RATE_200HZ
            - BMA4_OUTPUT_DATA_RATE_400HZ
            - BMA4_OUTPUT_DATA_RATE_800HZ
            - BMA4_OUTPUT_DATA_RATE_1600HZ
    */
    cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    /*!
        G-range, Optional parameters:
            - BMA4_ACCEL_RANGE_2G
            - BMA4_ACCEL_RANGE_4G
            - BMA4_ACCEL_RANGE_8G
            - BMA4_ACCEL_RANGE_16G
    */
    cfg.range = BMA4_ACCEL_RANGE_2G;
    /*!
        Bandwidth parameter, determines filter configuration, Optional parameters:
            - BMA4_ACCEL_OSR4_AVG1
            - BMA4_ACCEL_OSR2_AVG2
            - BMA4_ACCEL_NORMAL_AVG4
            - BMA4_ACCEL_CIC_AVG8
            - BMA4_ACCEL_RES_AVG16
            - BMA4_ACCEL_RES_AVG32
            - BMA4_ACCEL_RES_AVG64
            - BMA4_ACCEL_RES_AVG128
    */
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

    /*! Filter performance mode , Optional parameters:
        - BMA4_CIC_AVG_MODE
        - BMA4_CONTINUOUS_MODE
    */
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;

    // Configure the BMA423 accelerometer
    bma423.accelConfig(cfg);

    // Enable BMA423 accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    bma423.enableAccel();

    
    uint8_t rotation = bma423.direction();
    while (1) {
        if(rotation != bma423.direction()){
          rotation = bma423.direction();
          ESP_LOGW("BMA","direction:%d",rotation);
        }
        Accel acc;
        // if(btn_flag)
        {
        bma423.getAccel(&acc);
        // draw_wave(0,(acc.x + 1024)/2048.0*DISPLAY_HEIGHT,rgb565(255, 0, 0));
        // draw_wave(1,(acc.y + 1024)/2048.0*DISPLAY_HEIGHT,rgb565(0, 255, 0));
        // draw_wave(2,(acc.z + 1024)/2048.0*DISPLAY_HEIGHT,rgb565(0, 0, 255));
        }
        ESP_LOGW("BMA","%d,%d,%d",  acc.x,acc.y,acc.z);
        vTaskDelay(5000/ portTICK_RATE_MS);

    }
    vTaskDelete(NULL);
}



extern "C" void app_main()
{
    ESP_LOGI(TAG, "SDK version: %s", esp_get_idf_version());
    ESP_LOGI(TAG, "Heap when starting: %d", esp_get_free_heap_size());

    ESP_LOGI(TAG, "Initializing display");
    lvgl_main();
    vTaskDelay(1000/ portTICK_RATE_MS);

    static i2c_port_t i2c_port = I2C_NUM_0;

    ESP_LOGI(TAG, "Initializing I2C");
    i2c_init(i2c_port);

    ESP_LOGI(TAG, "Initializing AXP202");
    axp.read = &i2c_read;
    axp.write = &i2c_write;
    axp.handle = &i2c_port;

    axp202_init(&axp);
    // AXP202_ioctl(&axp, AXP202_COULOMB_COUNTER_ENABLE, NULL);
    // AXP202_ioctl(&axp, AXP202_COULOMB_COUNTER_CLEAR, NULL);

    ESP_LOGI(TAG, "Initializing PCF8563");
    pcf.read = &i2c_read;
    pcf.write = &i2c_write;
    pcf.handle = &i2c_port;

    ESP_LOGI(TAG, "Initializing BMA423");
    bma.read = &i2c_read;
    bma.write = &i2c_write;
    bma.handle = &i2c_port;
    
    // hagl_init();
    // hagl_clear_screen();

    ESP_LOGI(TAG, "Initializing non volatile storage");
    nvs_init();

    ESP_LOGI(TAG, "Initializing wifi");
    wifi_init();

    ESP_LOGI(TAG, "Start SNTP sync");
    /* Set your POSIX timezone here. */
    setenv("TZ", "CST-8", 1);
    tzset();

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_set_time_sync_notification_cb(sntp_set_rtc);
    sntp_init();

    ESP_LOGI(TAG, "Heap after init: %d", esp_get_free_heap_size());

    xTaskCreatePinnedToCore(rtc_task, "RTC", 4096, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(log_task, "Log", 4096, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(accel_task, "accel", 4096, NULL, 2, NULL, 1);
    
}


