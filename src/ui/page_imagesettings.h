#ifndef _PAGE_IMAGESETTINGS_H
#define _PAGE_IMAGESETTINGS_H


#include "lvgl/lvgl.h"
#include "page_common.h"
lv_obj_t *page_imagesettings_create(lv_obj_t *parent, panel_arr_t *arr);

void page_ims_click();
void set_slider_value();
#endif