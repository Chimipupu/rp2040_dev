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
}

/**
 * @brief CPU Core 0 メイン
 */
void cpu_core_0_main(void)
{
    app_main_core_0();
}

// ---------------------------------------------------
// ********** [CPU Core 1] ***********
/**
 * @brief CPU Core 1の初期化
 */
void cpu_core_1_init(void)
{
    app_main_core_1_init();
}

/**
 * @brief CPU Core 1 メイン
 */
void cpu_core_1_main(void)
{
    app_main_core_1();
}

// ---------------------------------------------------