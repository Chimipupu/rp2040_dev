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
// ********** [CPU Core 0] ***********
/**
 * @brief アプリ初期化 Core 1
 */
void app_main_core_0_init(void)
{
    // TODO
}

/**
 * @brief アプリメイン Core 0
 */
void app_main_core_0(void)
{
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
    // TODO
}

/**
 * @brief アプリメイン Core 1
 */
void app_main_core_1(void)
{
    delay(100);
}

// ---------------------------------------------------