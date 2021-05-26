idf_component_register(
    SRCS "main.cpp"  "helpers/wifi.c"  "helpers/nvs.c" "lvgl_gui/lvgl_main.c"
    "lvgl_gui/setup_scr_ring_screen.c" "lvgl_gui/gui_guider.c"
    INCLUDE_DIRS "./include" "lvgl_gui"
)