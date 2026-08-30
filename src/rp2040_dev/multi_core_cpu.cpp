/**
 * @file multi_core_cpu.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief マルチコアCPU関連処理
 * @version 0.1
 * @date 2026-08-29
 * 
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 * 
 */
#include "multi_core_cpu.hpp"
#include "pcb_def.hpp"
#include "app_main.hpp"
#include <Arduino.h>

#ifdef RGBLED_PIN
#include "app_neopixel.h"
#endif

// ---------------------------------------------------
static cpu_fifo_t s_fifo_cpu_core_0;
static cpu_fifo_t s_fifo_cpu_core_1;

static void _cpu_fifo_proc_cpu_core_0(void);
static void _cpu_fifo_proc_cpu_core_1(void);
// ---------------------------------------------------
// [Static関数]
static void _cpu_fifo_proc_cpu_core_0(void)
{
    bool is_ret_rx_fifo;
    bool is_ret_tx_fifo;
    uint32_t data_type = 0;
    uint32_t local_fifo_data = 0;
    static bool s_is_tx_fifo_data = false;
    static uint8_t s_rx_fifo_buf_idx = 0;
    static uint8_t s_tx_fifo_buf_idx = 0;

    is_ret_rx_fifo = cpu_fifo_rx_data(&s_fifo_cpu_core_0.rx_fifo_buf[s_rx_fifo_buf_idx]);

    if(is_ret_rx_fifo != false) {
        local_fifo_data = s_fifo_cpu_core_0.rx_fifo_buf[s_rx_fifo_buf_idx];
        Serial.printf("[DEBUG] CPU Core 0, RX FIFO[%d]: 0x%08X\n",
                        s_rx_fifo_buf_idx,
                        local_fifo_data
                    );
        s_rx_fifo_buf_idx = (s_rx_fifo_buf_idx + 1) % CPU_FIFO_BUF_SIZE;

        data_type = (uint8_t) ((local_fifo_data & CPU_FIFO_DATA_TYPE_BIT) >> 24);

        switch (data_type)
        {
            case CPU_FIFO_DATA_TYPE_RGBLED:
#ifdef RGBLED_PIN
                led_color_t rgb_val;
                rgb_val.rgb = (local_fifo_data & CPU_FIFO_DATA_BIT);
                app_neopixel_set_rgb(0, &rgb_val);
                s_fifo_cpu_core_0.tx_fifo_buf[s_tx_fifo_buf_idx] = (CPU_FIFO_DATA_TYPE_RESULT << 24) | CPU_FIFO_DATA_RESULT_PROCESS_COMPLETE;
                s_is_tx_fifo_data = true;
#endif
                break;

            default:
                break;
        }
    }

    if(s_is_tx_fifo_data != false) {
        is_ret_tx_fifo = cpu_fifo_tx_data(s_fifo_cpu_core_0.tx_fifo_buf[s_tx_fifo_buf_idx]);

        if(is_ret_tx_fifo != false) {
            s_is_tx_fifo_data = false;
            Serial.printf("[DEBUG] CPU Core 0, TX FIFO[%d]: 0x%08X\n",
                            s_tx_fifo_buf_idx,
                            s_fifo_cpu_core_0.tx_fifo_buf[s_tx_fifo_buf_idx]
                        );
            s_tx_fifo_buf_idx = (s_tx_fifo_buf_idx + 1) % CPU_FIFO_BUF_SIZE;
        }
    }
}

static void _cpu_fifo_proc_cpu_core_1(void)
{
    bool is_ret_tx_fifo = false;
    bool is_ret_rx_fifo = false;
    uint32_t data_type = 0;
    uint32_t local_fifo_data = 0;
    static bool s_is_tx_fifo_data = true;
    static uint8_t s_rx_fifo_buf_idx = 0;
    static uint8_t s_tx_fifo_buf_idx = 0;

    is_ret_rx_fifo = cpu_fifo_rx_data(&s_fifo_cpu_core_1.rx_fifo_buf[s_rx_fifo_buf_idx]);

    if(is_ret_rx_fifo != false) {
        local_fifo_data = s_fifo_cpu_core_1.rx_fifo_buf[s_rx_fifo_buf_idx];
        Serial.printf("[DEBUG] CPU Core 1, RX FIFO[%d]: 0x%08X\n",
                        s_rx_fifo_buf_idx,
                        local_fifo_data
                    );
        s_rx_fifo_buf_idx = (s_rx_fifo_buf_idx + 1) % CPU_FIFO_BUF_SIZE;
        data_type = (uint8_t) ((local_fifo_data & CPU_FIFO_DATA_TYPE_BIT) >> 24);

        switch (data_type)
        {
            case CPU_FIFO_DATA_TYPE_RESULT:
                if((local_fifo_data & CPU_FIFO_DATA_BIT) == CPU_FIFO_DATA_RESULT_PROCESS_COMPLETE) {
                    // 次に送信するFIFOのデータに進める
                    s_tx_fifo_buf_idx = (s_tx_fifo_buf_idx + 1) % CPU_FIFO_BUF_SIZE;
                    s_is_tx_fifo_data = true;
                }
                break;

            default:
                break;
        }
    }

    if(s_is_tx_fifo_data != false) {
        is_ret_tx_fifo = cpu_fifo_tx_data(s_fifo_cpu_core_1.tx_fifo_buf[s_tx_fifo_buf_idx]);

        if(is_ret_tx_fifo != false) {
            s_is_tx_fifo_data = false;
            Serial.printf("[DEBUG] CPU Core 1, TX FIFO[%d]: 0x%08X\n",
                            s_tx_fifo_buf_idx,
                            s_fifo_cpu_core_1.tx_fifo_buf[s_tx_fifo_buf_idx]
                        );
        }
    }
}


// ---------------------------------------------------
// [API]

/**
 * @brief CPU FIFOにデータを送信
 * @param data 送信データ(uint32_t)
 */
bool cpu_fifo_tx_data(uint32_t data)
{
    bool ret = false;
    ret = rp2040.fifo.push_nb(data);
    return ret;
}

/**
 * @brief CPU FIFOからデータを受信
 */
bool cpu_fifo_rx_data(uint32_t *p_data)
{
    bool ret = false;
    uint8_t fifo_data_num;

    fifo_data_num = rp2040.fifo.available();

    if (fifo_data_num > 0) {
        ret = rp2040.fifo.pop_nb(p_data);
    }

    return ret;
}

// ---------------------------------------------------
// ********** [CPU Core 0] ***********
/**
 * @brief CPU Core 0の初期化
 */
void cpu_core_0_init(void)
{
    gpio_init(); // GPIO初期化

#ifdef RGBLED_PIN
    // RGBLED 初期化
    app_neopixel_init(RGBLED_PIN, RGBLED_NUM, RGBLED_MAX_BRIGHTNESS);
#endif

    uart_init(); // UART初期化

    app_main_core_0_init(); // アプリ初期化
}

/**
 * @brief CPU Core 0 メイン
 */
void cpu_core_0_main(void)
{
    _cpu_fifo_proc_cpu_core_0(); // CPU FIFO処理

#ifdef BUTTON_PIN
    btn_polling();
#endif

    app_main_core_0();           // CPU Core 0用アプリ
}

// ---------------------------------------------------
// ********** [CPU Core 1] ***********
/**
 * @brief CPU Core 1の初期化
 */
void cpu_core_1_init(void)
{
    // RGBLED 初期化
#ifdef RGBLED_PIN
    uint8_t i;
    app_neopixel_init(RGBLED_PIN, RGBLED_NUM, RGBLED_MAX_BRIGHTNESS);
    for(i = 0; i < CPU_FIFO_BUF_SIZE; i++)
    {
        s_fifo_cpu_core_1.tx_fifo_buf[i] = (g_led_color_tbl[i].rgb.rgb | (CPU_FIFO_DATA_TYPE_RGBLED << 24));
    }
#endif

    app_main_core_1_init(); // アプリ初期化
}

/**
 * @brief CPU Core 1 メイン
 */
void cpu_core_1_main(void)
{
    // _cpu_fifo_proc_cpu_core_1(); // CPU FIFO処理
    // delay(500);
    app_main_core_1();           // CPU Core 1用アプリ
}

// ---------------------------------------------------