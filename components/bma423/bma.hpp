
#pragma once

#include "bma423.h"
#include "stdio.h"
#include "string.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "driver/i2c.h"

#define log_e(...) ESP_LOGE("BMA", ##__VA_ARGS__ )


enum {
    DIRECTION_TOP_EDGE        = 0,
    DIRECTION_BOTTOM_EDGE     = 1,
    DIRECTION_LEFT_EDGE       = 2,
    DIRECTION_RIGHT_EDGE      = 3,
    DIRECTION_DISP_UP         = 4,
    DIRECTION_DISP_DOWN       = 5
} ;

typedef struct bma4_dev Bma;
typedef struct bma4_accel Accel;
typedef struct bma4_accel_config Acfg;

/* These should be provided by the HAL. */
typedef struct {
    int32_t (* read)(void *handle, uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size);
    int32_t (* write)(void *handle, uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size);
    void *handle;
} bma423_t;


class BMA
{
public:
    BMA(bma423_t *bus);
    ~BMA();
    bool begin();
    void reset();
    uint8_t direction();
    float temperature();

    bool disableAccel();
    bool enableAccel(bool en = true);

    bool disalbeIrq(uint16_t int_map = BMA423_STEP_CNTR_INT);
    bool enableIrq(uint16_t int_map = BMA423_STEP_CNTR_INT);

    void attachInterrupt();

    uint32_t getCounter();
    bool isStepCounter();
    bool isDoubleClick();
    bool readInterrupt();
    bool isTilt();
    bool isActivity();
    bool isAnyNoMotion();
    bool getAccel(Accel *acc);
    uint8_t getIrqStatus();
    const char *getActivity();

    bool resetStepCounter();
    bool enableFeature(uint8_t feature, uint8_t enable );
    bool accelConfig(Acfg &cfg);

    bool set_remap_axes(struct bma423_axes_remap *remap_data);
    bool enableStepCountInterrupt(bool en = true);
    bool enableTiltInterrupt(bool en = true);
    bool enableWakeupInterrupt(bool en = true);
    bool enableAnyNoMotionInterrupt(bool en = true);
    bool enableActivityInterrupt(bool en = true);

private:
    static uint16_t read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len);
    static uint16_t write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len);

    uint16_t config();

    Bma _dev;
    static bma423_t *_bus;
    uint16_t _irqStatus;
    bool _init;
};
