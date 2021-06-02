/*
 * Copyright 2021 GYC
 */

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include <stdio.h>
#include "gui_guider.h"
// #include "events_init.h"
// #include "custom.h"


void setup_scr_ring_screen(lv_ui *ui){

	//Write codes ring_screen
	ui->ring_screen = lv_obj_create(NULL, NULL);

	//Write codes ring_screen_ring_container
	ui->ring_screen_ring_container = lv_cont_create(ui->ring_screen, NULL);

	//Write style LV_CONT_PART_MAIN for ring_screen_ring_container
	static lv_style_t style_ring_screen_ring_container_main;
	lv_style_init(&style_ring_screen_ring_container_main);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_container_main
	lv_style_set_radius(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_ring_screen_ring_container_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->ring_screen_ring_container, LV_CONT_PART_MAIN, &style_ring_screen_ring_container_main);
	lv_obj_set_pos(ui->ring_screen_ring_container, 0, 0);
	lv_obj_set_size(ui->ring_screen_ring_container, 240, 240);
	lv_obj_set_click(ui->ring_screen_ring_container, false);
	lv_cont_set_layout(ui->ring_screen_ring_container, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->ring_screen_ring_container, LV_FIT_NONE);

	//Write codes ring_screen_ring_big
	ui->ring_screen_ring_big = lv_arc_create(ui->ring_screen, NULL);

	//Write style LV_ARC_PART_BG for ring_screen_ring_big
	static lv_style_t style_ring_screen_ring_big_bg;
	lv_style_init(&style_ring_screen_ring_big_bg);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_big_bg
	lv_style_set_bg_color(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, lv_color_make(0x31, 0x03, 0x10));
	lv_style_set_line_width(&style_ring_screen_ring_big_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->ring_screen_ring_big, LV_ARC_PART_BG, &style_ring_screen_ring_big_bg);

	//Write style LV_ARC_PART_INDIC for ring_screen_ring_big
	static lv_style_t style_ring_screen_ring_big_indic;
	lv_style_init(&style_ring_screen_ring_big_indic);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_big_indic
	lv_style_set_line_color(&style_ring_screen_ring_big_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0x0f, 0x51));
	lv_style_set_line_width(&style_ring_screen_ring_big_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->ring_screen_ring_big, LV_ARC_PART_INDIC, &style_ring_screen_ring_big_indic);
	lv_obj_set_pos(ui->ring_screen_ring_big, 0, 0);
	lv_obj_set_size(ui->ring_screen_ring_big, 240, 240);
	lv_arc_set_bg_angles(ui->ring_screen_ring_big, 0, 360);
	lv_arc_set_angles(ui->ring_screen_ring_big, 0, 200);
	lv_arc_set_rotation(ui->ring_screen_ring_big, 90);
	lv_obj_set_style_local_pad_top(ui->ring_screen_ring_big, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_bottom(ui->ring_screen_ring_big, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_left(ui->ring_screen_ring_big, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_right(ui->ring_screen_ring_big, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);

	//Write codes ring_screen_ring_medium
	ui->ring_screen_ring_medium = lv_arc_create(ui->ring_screen, NULL);

	//Write style LV_ARC_PART_BG for ring_screen_ring_medium
	static lv_style_t style_ring_screen_ring_medium_bg;
	lv_style_init(&style_ring_screen_ring_medium_bg);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_medium_bg
	lv_style_set_bg_color(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, lv_color_make(0x15, 0x20, 0x00));
	lv_style_set_line_width(&style_ring_screen_ring_medium_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->ring_screen_ring_medium, LV_ARC_PART_BG, &style_ring_screen_ring_medium_bg);

	//Write style LV_ARC_PART_INDIC for ring_screen_ring_medium
	static lv_style_t style_ring_screen_ring_medium_indic;
	lv_style_init(&style_ring_screen_ring_medium_indic);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_medium_indic
	lv_style_set_line_color(&style_ring_screen_ring_medium_indic, LV_STATE_DEFAULT, lv_color_make(0xa5, 0xfd, 0x00));
	lv_style_set_line_width(&style_ring_screen_ring_medium_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->ring_screen_ring_medium, LV_ARC_PART_INDIC, &style_ring_screen_ring_medium_indic);
	lv_obj_set_pos(ui->ring_screen_ring_medium, 22, 22);
	lv_obj_set_size(ui->ring_screen_ring_medium, 194, 194);
	lv_arc_set_bg_angles(ui->ring_screen_ring_medium, 0, 360);
	lv_arc_set_angles(ui->ring_screen_ring_medium, 0, 270);
	lv_arc_set_rotation(ui->ring_screen_ring_medium, 90);
	lv_obj_set_style_local_pad_top(ui->ring_screen_ring_medium, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_bottom(ui->ring_screen_ring_medium, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_left(ui->ring_screen_ring_medium, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_right(ui->ring_screen_ring_medium, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);

	//Write codes ring_screen_ring_small
	ui->ring_screen_ring_small = lv_arc_create(ui->ring_screen, NULL);

	//Write style LV_ARC_PART_BG for ring_screen_ring_small
	static lv_style_t style_ring_screen_ring_small_bg;
	lv_style_init(&style_ring_screen_ring_small_bg);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_small_bg
	lv_style_set_bg_color(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x34, 0x2f));
	lv_style_set_line_width(&style_ring_screen_ring_small_bg, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->ring_screen_ring_small, LV_ARC_PART_BG, &style_ring_screen_ring_small_bg);

	//Write style LV_ARC_PART_INDIC for ring_screen_ring_small
	static lv_style_t style_ring_screen_ring_small_indic;
	lv_style_init(&style_ring_screen_ring_small_indic);

	//Write style state: LV_STATE_DEFAULT for style_ring_screen_ring_small_indic
	lv_style_set_line_color(&style_ring_screen_ring_small_indic, LV_STATE_DEFAULT, lv_color_make(0x03, 0xdd, 0xf8));
	lv_style_set_line_width(&style_ring_screen_ring_small_indic, LV_STATE_DEFAULT, 16);
	lv_obj_add_style(ui->ring_screen_ring_small, LV_ARC_PART_INDIC, &style_ring_screen_ring_small_indic);
	lv_obj_set_pos(ui->ring_screen_ring_small, 46, 46);
	lv_obj_set_size(ui->ring_screen_ring_small, 146, 146);
	lv_arc_set_bg_angles(ui->ring_screen_ring_small, 0, 360);
	lv_arc_set_angles(ui->ring_screen_ring_small, 0, 180);
	lv_arc_set_rotation(ui->ring_screen_ring_small, 90);
	lv_obj_set_style_local_pad_top(ui->ring_screen_ring_small, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_bottom(ui->ring_screen_ring_small, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_left(ui->ring_screen_ring_small, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
	lv_obj_set_style_local_pad_right(ui->ring_screen_ring_small, LV_ARC_PART_BG, LV_STATE_DEFAULT, 20);
}

extern lv_ui guider_ui;
void set_ring_as_time(int hour,int minute,int second)
{
	lv_ui *ui = &guider_ui;
	lv_arc_set_angles(ui->ring_screen_ring_small, 0, hour/24.0*360.0);
	lv_arc_set_angles(ui->ring_screen_ring_medium, 0, minute/60.0*360.0);
	lv_arc_set_angles(ui->ring_screen_ring_big, 0, second/60.0*360.0);
}