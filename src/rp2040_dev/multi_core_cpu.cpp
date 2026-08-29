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
bool multi_core_cpu_tx_data(uint32_t data)
{
    bool ret;

    ret = rp2040.fifo.push_nb(data);

#if 0
    // 送信成功
    if (ret != false) {
        Serial.printf("[INFO]CPU FIFO TX Data: 0x%08X\r\n", data);
    }
    // FIFOが満杯で送信失敗
    else {
        Serial.printf("[ERR]CPU FIFO FULL!\r\n");
    }
#endif

    return ret;
}

/**
 * @brief CPU FIFOからデータを受信
 */
bool multi_core_cpu_rx_data(uint32_t *p_data)
{
    bool ret;
    uint8_t fifo_data_num;

    fifo_data_num = rp2040.fifo.available();

    if (fifo_data_num > 0) {
        ret = rp2040.fifo.pop_nb(p_data);

#if 0
        // 受信成功
        if (ret != false) {
            Serial.printf("[INFO]CPU FIFO RX Data: 0x%08X\r\n", *p_data);
        }
        // FIFOが空で受信失敗
        else {
            Serial.printf("[ERR]CPU FIFO EMPTY!\r\n");
        }
#endif
    }

    return ret;
}

// ********** [CPU Core 0] ***********
/**
 * @brief CPU Core 0の初期化
 */
void cpu_core_0_init(void)
{
    // GPIO初期化
    gpio_init();

#ifdef RGBLED_PIN
    app_neopixel_init(RGBLED_PIN, RGBLED_NUM, RGBLED_MAX_BRIGHTNESS);
#endif

    // UART初期化
    uart_init();

#if 0
    uint32_t i, dmmy;
    // (DEBUG)ダミーデータをCPU Core1に送信
    for(i = 0; i < CPU_FIFO_BUF_SIZE; i++) {
        dmmy = (i + 1) * 0x01010101;
        multi_core_cpu_tx_data(dmmy);
    }
#endif
}

// ********** [CPU Core 1] ***********
/**
 * @brief CPU Core 1の初期化
 */
void cpu_core_1_init(void)
{
    app_main_core_1_init();
}