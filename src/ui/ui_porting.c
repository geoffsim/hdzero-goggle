#include "ui/ui_porting.h"

#include <stdio.h>

#include <log/log.h>

#include "../core/common.hh"
#include "../core/settings.h"
#include "fbtools.h"
#include "lvgl/lvgl.h"

#ifdef EMULATOR_BUILD
#include <SDL2/SDL.h>
static void *fb1, *fb2;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
#ifndef WINDOW_NAME
#define WINDOW_NAME "HDZero"
#endif
#endif

#define DISP_HOR_RES 1920
#define DISP_VER_RES 1080

typedef enum {
    ORBIT_NONE = 0x00,
    ORBIT_D = 0x01,
    ORBIT_R = 0x02,
    ORBIT_U = 0x04,
    ORBIT_L = 0x08,
    ORBIT_FLUSH = 0x10,
} orbit_state_t;

FBDEV fbdev;
static int h_resolution = DISP_HOR_RES;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_buf[DISP_HOR_RES * DISP_VER_RES * 4];
static lv_disp_drv_t disp_drv;
static orbit_state_t disp_orbit_state = ORBIT_NONE;
static int disp_orbit_x, disp_orbit_y;
static lv_disp_t *disp;

static void hdz_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    static int orbit_flush = 0;

    // Manipulates the orbiting speed
    if (++orbit_flush % 500 == 0) {
        disp_orbit_state |= ORBIT_FLUSH;
    }

#ifndef EMULATOR_BUILD
    for (lv_coord_t y = area->y1 + disp_orbit_y; y <= area->y2; y++) {
        fbdev.fb_mem_offset = (y * h_resolution + area->x1 + disp_orbit_x) * 4;
        fbdev.fb_fix.smem_len = 4 * (area->x2 - area->x1 + 1);
        memcpy(fbdev.fb_mem + fbdev.fb_mem_offset, ((char *)color_p), fbdev.fb_fix.smem_len);
        color_p += (area->x2 - area->x1 + 1);
    }

    fb_sync(&fbdev);
#else
    SDL_Rect r;
    r.x = area->x1 + disp_orbit_x;
    r.y = area->y1 + disp_orbit_y;
    r.w = area->x2 + 1 - disp_orbit_x;
    r.h = area->y2 + 1 - disp_orbit_y;

    SDL_UpdateTexture(texture, &r, color_p, disp_drv.hor_res * ((LV_COLOR_DEPTH + 7) / 8));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
#endif

    if (disp_orbit_state & ORBIT_FLUSH) {
        disp_orbit_state &= ~ORBIT_FLUSH;

        int pixels = 1 << g_setting.osd.orbit;

        if (disp_orbit_state & ORBIT_D && disp_orbit_y < pixels) {
            disp_orbit_y += 1;
            if (disp_orbit_y == pixels) {
                disp_orbit_state &= ~ORBIT_D;
                disp_orbit_state |= ORBIT_R;
            }
        } else if (disp_orbit_state & ORBIT_R && disp_orbit_x < pixels) {
            disp_orbit_x += 1;
            if (disp_orbit_x == pixels) {
                disp_orbit_state &= ~ORBIT_R;
                disp_orbit_state |= ORBIT_U;
            }
        } else if (disp_orbit_state & ORBIT_U && disp_orbit_y > 0) {
            disp_orbit_y -= 1;
            if (disp_orbit_y == 0) {
                disp_orbit_state &= !ORBIT_U;
                disp_orbit_state |= ORBIT_L;
            }
        } else if (disp_orbit_state & ORBIT_L && disp_orbit_x > 0) {
            disp_orbit_x -= 1;
            if (disp_orbit_x == 0) {
                disp_orbit_state &= ~ORBIT_L;
                disp_orbit_state |= ORBIT_D;
            }
        }
    }

    lv_disp_flush_ready(disp);
}

int lvgl_init_porting() {
#ifndef EMULATOR_BUILD
    memset(&fbdev, 0x0, sizeof(FBDEV));
    strncpy(fbdev.dev, "/dev/fb0", sizeof(fbdev.dev));
    if (fb_open(&fbdev) == -1) {
        LOGE("open frame buffer error");
        return -1;
    }
    LOGI("register disp drv");

    lv_disp_draw_buf_init(&draw_buf, disp_buf, NULL, DISP_HOR_RES * DISP_VER_RES * 4);

    lv_disp_drv_init(&disp_drv);
#else
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(WINDOW_NAME,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              DISP_HOR_RES, DISP_VER_RES, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    texture = SDL_CreateTexture(renderer,
                                (LV_COLOR_DEPTH == 32) ? (SDL_PIXELFORMAT_ARGB8888) : (SDL_PIXELFORMAT_RGB565),
                                SDL_TEXTUREACCESS_STREAMING,
                                DISP_HOR_RES,
                                DISP_VER_RES);

    fb1 = malloc(DISP_HOR_RES * DISP_VER_RES * ((LV_COLOR_DEPTH + 7) / 8));
    fb2 = malloc(DISP_HOR_RES * DISP_VER_RES * ((LV_COLOR_DEPTH + 7) / 8));

    lv_disp_draw_buf_init(&draw_buf, fb1, fb2, DISP_HOR_RES * DISP_VER_RES);
    lv_disp_drv_init(&disp_drv);
#endif

    disp_drv.full_refresh = 1;
    disp_drv.flush_cb = hdz_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = DISP_HOR_RES;
    disp_drv.ver_res = DISP_VER_RES;
    disp = lv_disp_drv_register(&disp_drv);

    return 0;
}

int lvgl_switch_to_720p() {
    lv_disp_draw_buf_init(&draw_buf, disp_buf, NULL, 1280 * 720 * 4);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = 1280;
    disp_drv.ver_res = 720;
    lv_disp_drv_update(disp, &disp_drv);

    h_resolution = 1280;
    return 0;
}

int lvgl_switch_to_1080p() {
    lv_disp_draw_buf_init(&draw_buf, disp_buf, NULL, 1920 * 1080 * 4);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = 1920;
    disp_drv.ver_res = 1080;
    lv_disp_drv_update(disp, &disp_drv);

    h_resolution = 1920;
    return 0;
}

void lvgl_screen_orbit(bool enable) {
    if (enable) {
        disp_orbit_state = ORBIT_D;
    } else {
        disp_orbit_state = ORBIT_NONE;
        disp_orbit_x = 0;
        disp_orbit_y = 0;
    }
}
