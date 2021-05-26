/*
 * Copyright 2021 GYC
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
// #include "guider_fonts.h"

typedef struct
{
	lv_obj_t *ring_screen;
	lv_obj_t *ring_screen_ring_container;
	lv_obj_t *ring_screen_ring_big;
	lv_obj_t *ring_screen_ring_medium;
	lv_obj_t *ring_screen_ring_small;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_ring_screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif