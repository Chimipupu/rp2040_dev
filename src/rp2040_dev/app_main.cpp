/**
 * @file app_main.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリメイン
 * @version 0.1
 * @date 2026-08-29
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */
#include "app_main.hpp"
#include "pcb_def.hpp"
#include "multi_core_cpu.hpp"
#include <Arduino.h>

#ifdef RGBLED_PIN
#include "app_neopixel.h"
#endif

// ---------------------------------------------------
static cpu_fifo_t s_fifo_cpu_core_0;
static cpu_fifo_t s_fifo_cpu_core_1;

// ---------------------------------------------------
// ********** [CPU Core 0] ***********
/**
 * @brief アプリメイン Core 0
 */
void app_main_core_0(void)
{
    bool ret;
    uint32_t data_type = 0;
    uint32_t local_fifo_data = 0;
    static uint8_t s_fifo_buf_idx = 0;

    ret = cpu_fifo_rx_data(&s_fifo_cpu_core_0.rx_fifo_buf[s_fifo_buf_idx]);

    if(ret != false) {
        local_fifo_data = s_fifo_cpu_core_0.rx_fifo_buf[s_fifo_buf_idx];
        Serial.printf("[DEBUG] CPU Core 0, RX FIFO[%d]: 0x%08X\n", s_fifo_buf_idx, local_fifo_data);
        s_fifo_buf_idx = (s_fifo_buf_idx + 1) % CPU_FIFO_BUF_SIZE;

        data_type = (uint8_t) ((local_fifo_data & CPU_FIFO_DATA_TYPE_BIT) >> 24);

        switch (data_type)
        {
            case CPU_FIFO_DATA_TYPE_RGBLED:
#ifdef RGBLED_PIN
                led_color_t rgb_val;
                rgb_val.rgb = (local_fifo_data & CPU_FIFO_DATA_BIT);
                app_neopixel_set_rgb(0, &rgb_val);
#endif
                break;

            default:
                break;
        }
    }

#ifdef BUTTON_PIN
    btn_polling();
#endif
}

// ---------------------------------------------------
// ********** [CPU Core 1] ***********
/**
 * @brief アプリ初期化 Core 1
 */
void app_main_core_1_init(void)
{
    uint8_t i;

#ifdef RGBLED_PIN
    for(i = 0; i < CPU_FIFO_BUF_SIZE; i++)
    {
        s_fifo_cpu_core_1.tx_fifo_buf[i] = (g_led_color_tbl[i].rgb.rgb | (CPU_FIFO_DATA_TYPE_RGBLED << 24));
        // Serial.printf("[DEBUG] CPU Core 1 Tx FIFO[%d]:  0x%08X\n", s_fifo_cpu_core_1.tx_fifo_buf[i]);
    }
#endif
}

/**
 * @brief アプリメイン Core 1
 */
void app_main_core_1(void)
{
    bool ret;
    static uint8_t s_fifo_buf_idx = 0;

    ret = cpu_fifo_tx_data(s_fifo_cpu_core_1.tx_fifo_buf[s_fifo_buf_idx]);

    if(ret != false) {
        Serial.printf("[DEBUG] CPU Core 1, TX FIFO[%d]: 0x%08X\n", s_fifo_buf_idx, s_fifo_cpu_core_1.tx_fifo_buf[s_fifo_buf_idx]);
        s_fifo_buf_idx = (s_fifo_buf_idx + 1) % CPU_FIFO_BUF_SIZE;
    }

    delay(100);
}

// ---------------------------------------------------