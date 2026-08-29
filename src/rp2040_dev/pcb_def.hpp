/**
 * @file pcb_def.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief 基板定義
 * @version 0.1
 * @date 2026-08-29
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */
#ifndef PCB_DEF_HPP
#define PCB_DEF_HPP

#include <stdint.h>
#include <string.h>

// #define PCB_RPI_PICO
// #define PCB_RPI_PICO_W
#define PCB_RP2040_ZERO
// #define PCB_YD_RP2040
// #define PCB_MAKERPI_RP2040

// RP2040 Zero
#ifdef PCB_RP2040_ZERO
    #define RGBLED_PIN               16  // Neopixel (GPIO 16)
    #define RGBLED_NUM               1   // RGBLEDの数
    #define RGBLED_MAX_BRIGHTNESS    32  // RGBLEDの最大輝度
    #define RGBLED_COLOR_ON_TIMER    100 // RGBLEDの1色の表示時間
#endif // PCB_RP2040_ZERO

// VCC-GND RP2040
#ifdef PCB_YD_RP2040
    #define RGBLED_PIN               23  // Neopixel (GPIO 23)
    #define OB_LED_PIN               25  // 青色LED (GPIO 25)
    #define BUTTON_PIN               24  // ボタン (GPIO 24)
    // I2C
    #define I2C_SDA                  4   // I2C0 SDA
    #define I2C_SCL                  5   // I2C0 SCL
    #define I2C_1_SDA                6   // I2C1 SDA
    #define I2C_1_SCL                7   // I2C1 SCL
    // SPI
    #define SPI_CS_PIN               1   // SPI0 CS
    #define SPI_SCK_PIN              2   // SPI0 CLK
    #define SPI_MISO_PIN             0   // SPI0 MISO
    #define SPI_MOSI_PIN             3   // SPI0 MOSI
    // UART
    #define UART_TX_PIN              12  // UART0 TX
    #define UART_RX_PIN              13  // UART0 RX
#endif // PCB_YD_RP2040

// Maker Pi RP2040
#ifdef PCB_MAKERPI_RP2040
    // ボタン
    #define OB_BTN_0            20 // 基板ボタン0(GPIO20)
    #define OB_BTN_1            21 // 基板ボタン1(GPIO21)

    // ブザー
    #define OB_BUZZER_PIN       22 // 基板 ブザー(GPIO22)

    // NeoPixel(RGBLED)
    #define OB_NEOPIXEL_PIN     18 // 基板 NeoPixel(GPIO18)
    #define OB_NEOPIXEL_NUM     2  // 基板 NeoPixelの数

    // LED
    #define OB_LED_BIT_NUM      13 // 基板 青LED 13bit分
    #define OB_LED_BIT_13       0  // 基板 青LED 13bit(GPIO0)
    #define OB_LED_BIT_12       1  // 基板 青LED 12bit(GPIO1)
    #define OB_LED_BIT_11       2  // 基板 青LED 11bit(GPIO2)
    #define OB_LED_BIT_10       3  // 基板 青LED 10bit(GPIO3)
    #define OB_LED_BIT_9        4  // 基板 青LED 9bit(GPIO4)
    #define OB_LED_BIT_8        5  // 基板 青LED 8bit(GPIO5)
    #define OB_LED_BIT_7        6  // 基板 青LED 7bit(GPIO6)
    #define OB_LED_BIT_6        7  // 基板 青LED 6bit(GPIO7)
    #define OB_LED_BIT_5        16 // 基板 青LED 5bit(GPIO16)
    #define OB_LED_BIT_4        17 // 基板 青LED 4bit(GPIO17)
    #define OB_LED_BIT_3        26 // 基板 青LED 3bit(GPIO26)
    #define OB_LED_BIT_2        27 // 基板 青LED 2bit(GPIO27)
    #define OB_LED_BIT_1        28 // 基板 青LED 1bit(GPIO28)

    #define OB_LED_SEQ_MS       20 // LEDを左右に行き来するLED1つあたりの点灯時間(ms)
    #define OB_LED_BIT_MS       20 // LEDを13bitで点灯させる1つあたりの点灯時間(ms)
    #define LED_LOOP_CNT        3  // LED処理のループ回数

    void led_sequential_blink(uint32_t loop_cnt);
    void led_bit_blink(uint32_t loop_cnt);
#endif // PCB_MAKERPI_RP2040

void gpio_init(void);
void uart_init(void);
void btn_polling(void);

#endif // PCB_DEF_HPP