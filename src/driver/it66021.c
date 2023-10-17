#include "it66021.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <log/log.h>

#include "../core/common.hh"
#include "defines.h"
#include "dm5680.h"
#include "hardware.h"
#include "i2c.h"
#include "oled.h"

#define ADDR_IT66021_RING 0x70

void IT66021_Mask_WR(uint8_t is_ring, uint8_t addr, uint8_t mask, uint8_t wdat) {
    uint8_t temp;
    temp = I2C_L_Read(is_ring ? ADDR_IT66021_RING : ADDR_IT66021, addr);
    temp = (temp & ((~mask) & 0xFF)) + (mask & wdat);
    I2C_L_Write(is_ring ? ADDR_IT66021_RING : ADDR_IT66021, addr, temp);
}

void IT66021_OscCalib() {
    uint32_t val = 0, OSCCLK;
    uint8_t temp;

    // Get R100msTimeCnt (RING14[7:0]|RING13[7:0]|RING12[7:0])
    I2C_L_Write(ADDR_IT66021_RING, 0x01, 0x41);
    usleep(100000);
    I2C_L_Write(ADDR_IT66021_RING, 0x01, 0x40);

    val = I2C_L_Read(ADDR_IT66021_RING, 0x14);
    val <<= 8;
    val |= I2C_L_Read(ADDR_IT66021_RING, 0x13);
    val <<= 8;
    val |= I2C_L_Read(ADDR_IT66021_RING, 0x12); // R100msTimeCnt

    OSCCLK = val * 10;

    // oscdiv
    val = (val + 500000) / 1000000; // oscdiv
    LOGI("IT66021: OSCCLK = %d,  oscdiv = %d", OSCCLK, val);

    val <<= 4;
    IT66021_Mask_WR(1, 0x01, 0x70, val & 0x70);

    // Set reference clock, depends on the power consumption and speed setting
    IT66021_Mask_WR(0, 0x54, 0x03, 0x01);

    OSCCLK >>= 2; // now is RCLK

    // Set RCLK parameter into RING02/RING03:
    val = OSCCLK / 1000 / 100;
    temp = val & 0xff;
    IT66021_Mask_WR(1, 0x02, 0xff, temp);

    temp = (val >> 1) & 0x80;
    val = 128 * ((OSCCLK / 1000) % 100) / 100;
    temp |= (val & 0x7F);
    IT66021_Mask_WR(1, 0x03, 0xff, temp);
}

void IT66021_srst() {
    I2C_L_Write(ADDR_IT66021, 0x10, 0xFF);
}

void IT66021_close() {
    DM5680_ResetHDMI_RX(0);
}

void IT66021_init() {
    DM5680_ResetHDMI_RX(0);
    usleep(1000);
    DM5680_ResetHDMI_RX(1);
    usleep(10000);

    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);
    IT66021_Mask_WR(0, 0x10, 0xff, 0x08);
    IT66021_Mask_WR(0, 0x10, 0xff, 0x17);
    IT66021_Mask_WR(0, 0x11, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x18, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x12, 0xff, 0xf8);
    IT66021_Mask_WR(0, 0x10, 0xff, 0x10);
    IT66021_Mask_WR(0, 0x11, 0xff, 0xa0);
    IT66021_Mask_WR(0, 0x18, 0xff, 0xa0);
    IT66021_Mask_WR(0, 0x12, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x0f, 0x03, 0x01);
    IT66021_Mask_WR(0, 0xc0, 0x80, 0x00);
    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);
    IT66021_Mask_WR(0, 0x17, 0xc0, 0x80);
    IT66021_Mask_WR(0, 0x1e, 0xc0, 0x00);
    IT66021_Mask_WR(0, 0x0e, 0xff, 0xff);
    IT66021_Mask_WR(0, 0x86, 0xff, 0xc9);
    IT66021_Mask_WR(0, 0x16, 0x08, 0x08);
    IT66021_Mask_WR(0, 0x1d, 0x08, 0x08);
    IT66021_Mask_WR(0, 0x2b, 0x07, 0x07);
    IT66021_Mask_WR(0, 0x31, 0xff, 0x2c);
    IT66021_Mask_WR(0, 0x34, 0xff, 0xe1);
    IT66021_Mask_WR(0, 0x35, 0x0c, 0x01);
    IT66021_Mask_WR(0, 0x54, 0x0c, 0x09);
    IT66021_Mask_WR(0, 0x6a, 0xff, 0x81);
    IT66021_Mask_WR(0, 0x74, 0xff, 0xa0);
    IT66021_Mask_WR(0, 0x50, 0x1f, 0x12);
    IT66021_Mask_WR(0, 0x65, 0x0c, 0x00);
    IT66021_Mask_WR(0, 0x7a, 0x80, 0x80);
    IT66021_Mask_WR(0, 0x85, 0x02, 0x02);
    IT66021_Mask_WR(0, 0xc0, 0x03, 0x00);
    IT66021_Mask_WR(0, 0x87, 0xff, 0xa9);
    IT66021_Mask_WR(0, 0x71, 0x08, 0x00);
    IT66021_Mask_WR(0, 0x37, 0xff, 0x88);
    IT66021_Mask_WR(0, 0x4d, 0xff, 0x88);
    IT66021_Mask_WR(0, 0x67, 0x80, 0x00);
    IT66021_Mask_WR(0, 0x7a, 0x70, 0x70);
    IT66021_Mask_WR(0, 0x7e, 0x40, 0x00);
    IT66021_Mask_WR(0, 0x52, 0x20, 0x20);
    IT66021_Mask_WR(0, 0x53, 0xc0, 0x40);
    IT66021_Mask_WR(0, 0x58, 0xff, 0xab);
    IT66021_Mask_WR(0, 0x59, 0xff, 0xaa);
    IT66021_Mask_WR(0, 0x0f, 0x03, 0x01);
    IT66021_Mask_WR(0, 0xbc, 0xff, 0x06);
    IT66021_Mask_WR(0, 0xb5, 0x03, 0x03);
    IT66021_Mask_WR(0, 0xb6, 0x07, 0x00);
    IT66021_Mask_WR(0, 0xb1, 0xff, 0x20);
    IT66021_Mask_WR(0, 0xb2, 0xff, 0x01);
    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);
    IT66021_Mask_WR(0, 0x25, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x3d, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x27, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x28, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x29, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x3f, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x40, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x41, 0xff, 0x1f);
    IT66021_Mask_WR(0, 0x22, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x26, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x3a, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x3e, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x20, 0x7f, 0x3f);
    IT66021_Mask_WR(0, 0x38, 0x7f, 0x3f);

    IT66021_Mask_WR(0, 0x0f, 0x03, 0x01);
    IT66021_Mask_WR(0, 0x70, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x71, 0xff, 0x80);
    IT66021_Mask_WR(0, 0x72, 0xff, 0x10);
    IT66021_Mask_WR(0, 0x73, 0xff, 0xb2);
    IT66021_Mask_WR(0, 0x74, 0xff, 0x04);
    IT66021_Mask_WR(0, 0x75, 0xff, 0x65);
    IT66021_Mask_WR(0, 0x76, 0xff, 0x02);
    IT66021_Mask_WR(0, 0x77, 0xff, 0xe9);
    IT66021_Mask_WR(0, 0x78, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x79, 0xff, 0x93);
    IT66021_Mask_WR(0, 0x7a, 0xff, 0x3c);
    IT66021_Mask_WR(0, 0x7b, 0xff, 0x18);
    IT66021_Mask_WR(0, 0x7c, 0xff, 0x04);
    IT66021_Mask_WR(0, 0x7d, 0xff, 0x55);
    IT66021_Mask_WR(0, 0x7e, 0xff, 0x3f);
    IT66021_Mask_WR(0, 0x7f, 0xff, 0x49);
    IT66021_Mask_WR(0, 0x80, 0xff, 0x3d);
    IT66021_Mask_WR(0, 0x81, 0xff, 0x9f);
    IT66021_Mask_WR(0, 0x82, 0xff, 0x3e);
    IT66021_Mask_WR(0, 0x83, 0xff, 0x18);
    IT66021_Mask_WR(0, 0x84, 0xff, 0x04);
    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);

    IT66021_Mask_WR(0, 0x51, 0xff, 0x88);
    IT66021_Mask_WR(0, 0x51, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x52, 0xff, 0x30);
    IT66021_Mask_WR(0, 0x65, 0xff, 0x50);
    IT66021_Mask_WR(0, 0x53, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x77, 0x80, 0x80);
    IT66021_Mask_WR(0, 0x75, 0xff, 0x42);
    IT66021_Mask_WR(0, 0x76, 0xff, 0xe4);
    IT66021_Mask_WR(0, 0x7d, 0xff, 0x30);
    IT66021_Mask_WR(0, 0x7e, 0xff, 0x00);
    IT66021_Mask_WR(0, 0x7b, 0xff, 0x02);

    IT66021_Mask_WR(1, 0x0a, 0xff, 0x00);
    IT66021_Mask_WR(1, 0x08, 0xff, 0x00);
    IT66021_Mask_WR(1, 0x09, 0xff, 0x00);
    IT66021_Mask_WR(1, 0x52, 0xff, 0x00);
    IT66021_Mask_WR(1, 0x53, 0xff, 0x80);
    IT66021_Mask_WR(1, 0x32, 0xff, 0x0c);
    IT66021_Mask_WR(1, 0x81, 0xff, 0x20);
    IT66021_Mask_WR(1, 0x82, 0xff, 0x31);
    IT66021_Mask_WR(1, 0x83, 0xff, 0x78);
    IT66021_Mask_WR(1, 0x84, 0xff, 0x56);
    IT66021_Mask_WR(1, 0x8b, 0xff, 0x68);
    IT66021_Mask_WR(1, 0x8c, 0xff, 0x02);
    IT66021_Mask_WR(1, 0x28, 0x01, 0x00);
    IT66021_Mask_WR(1, 0x0f, 0x20, 0x20);
    IT66021_Mask_WR(1, 0x29, 0x80, 0x80);
    IT66021_Mask_WR(1, 0x39, 0x80, 0x80);
    IT66021_Mask_WR(1, 0x00, 0x8f, 0x01);
    IT66021_Mask_WR(1, 0x01, 0x8c, 0xc4);
    IT66021_Mask_WR(1, 0x0c, 0x89, 0x88);
    IT66021_Mask_WR(1, 0x36, 0xfc, 0xb7);
    IT66021_Mask_WR(1, 0x38, 0x20, 0xf8);
    IT66021_Mask_WR(1, 0x5c, 0xfc, 0x00);
    IT66021_Mask_WR(1, 0x66, 0x03, 0x01);
    IT66021_Mask_WR(1, 0x2a, 0x07, 0x01);
    IT66021_Mask_WR(1, 0x0f, 0x10, 0x00);

    usleep(1000);
}

int IT66021_Sig_det() {
    uint8_t st;

    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);
    st = I2C_L_Read(ADDR_IT66021, 0x99);
    st = (st >> 3) & 0x01;

    return st;
}

#define IT66121_9A_READ_N 5
int IT66021_Get_VTMG(int *freq_ref) {
    int r9a[IT66121_9A_READ_N], r9c, r9d, r9e, r9f, ra3, ra4, ra5;
    int hmax, vmax, hact, vact;
    int i, j;
    double fps;
    int ret = HDMIIN_VTMG_UNKNOW;

    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);

    for (i = 0; i < IT66121_9A_READ_N; i++) {
        r9a[i] = I2C_L_Read(ADDR_IT66021, 0x9a);
    }

    for (i = 0; i < IT66121_9A_READ_N; i++) {
        for (j = IT66121_9A_READ_N - 1; j >= i; j--) {
            if (r9a[j] > r9a[j + 1]) {
                int temp = r9a[j];
                r9a[j] = r9a[j + 1];
                r9a[j + 1] = temp;
            }
        }
    }

    r9c = I2C_L_Read(ADDR_IT66021, 0x9c);
    r9d = I2C_L_Read(ADDR_IT66021, 0x9d);
    r9e = I2C_L_Read(ADDR_IT66021, 0x9e);
    r9f = I2C_L_Read(ADDR_IT66021, 0x9f);
    ra3 = I2C_L_Read(ADDR_IT66021, 0xa3);
    ra4 = I2C_L_Read(ADDR_IT66021, 0xa4);
    ra5 = I2C_L_Read(ADDR_IT66021, 0xa5);

    hmax = ((r9d & 0x3f) << 8) | (r9c & 0xff);
    vmax = ((ra4 & 0x0f) << 8) | (ra3 & 0xff);

    hact = ((r9f & 0x3f) << 8) | (r9e & 0xff);
    vact = ((ra4 & 0xf0) << 4) | (ra5 & 0xff);

    *freq_ref = r9a[1];

    fps = 6831.0 / r9a[1];
    fps = fps * 1000000 / hmax / vmax;

    if (hact == 1920 && vact == 1080) {
        if (fps < 45 || fps >= 65)
            ret = HDMIIN_VTMG_1080Pother;
        else if (fps < 55)
            ret = HDMIIN_VTMG_1080P50;
        else
            ret = HDMIIN_VTMG_1080P60;
    } else if (hact == 1280 && vact == 720) {
        if (fps < 55)
            ret = HDMIIN_VTMG_720P50;
        else if (fps > 80)
            ret = HDMIIN_VTMG_720P100;
        else
            ret = HDMIIN_VTMG_720P60;
    }

    return ret;
}

// get color space
int IT66021_Get_CS() {
    int val;

    IT66021_Mask_WR(0, 0x0f, 0x03, 0x02);
    val = I2C_L_Read(ADDR_IT66021, 0x15);
    IT66021_Mask_WR(0, 0x0f, 0x03, 0x00);

    val = (val >> 5) & 0x03;
    return val;
}

void IT66021_Set_CSMatrix(int cs) {
    if (cs == 0) {
        IT66021_Mask_WR(0, 0x65, 0x03, 0x02);
    } else {
        IT66021_Mask_WR(0, 0x65, 0x03, 0x00);
    }
}
