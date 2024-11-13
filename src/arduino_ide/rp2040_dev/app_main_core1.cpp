/**
 * @file app_main_core1.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)）
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)）
 * 
 */
#include "app_main_core1.hpp"

static uint8_t s_cpu_core = 0;
static xTaskHandle s_xTaskCore1oled;
static xTaskHandle s_xTaskCore1monitor;
static xTaskHandle s_xTaskCore1Main;

#ifdef OLED_LCD_USE
void vTaskCore1oled(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore1oled\n", s_cpu_core);

    while (1)
    {
        app_oled_test();
        WDT_TOGGLE;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#endif /* OLED_LCD_USE */

void vTaskCore1monitor(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore1monitor\n", s_cpu_core);

    while (1)
    {
        cpm_main();
        WDT_TOGGLE;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

#if 0
void vTaskCore1Main(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore1Main\n", s_cpu_core);

    while (1)
    {
        // TODO: Core1メイン処理
        NOP;
        WDT_TOGGLE;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
#endif

void app_main_init_core1(void)
{
    s_cpu_core = app_util_get_cpu_core_num();
    WDT_TOGGLE;
    DEBUG_PRINTF("[Core%X] ... Init\n", s_cpu_core);

#ifdef OLED_LCD_USE
    app_oled_init();

    // FreeRTOS初期化
    xTaskCreate(vTaskCore1oled,         // コールバック関数ポインタ
                "vTaskCore1oled",       // タスク名
                1024,                    // スタック
                nullptr,                // パラメータ
                2,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1oled       // タスクハンドル
                );
#endif /* OLED_LCD_USE */

    xTaskCreate(vTaskCore1monitor,      // コールバック関数ポインタ
                "vTaskCore1monitor",    // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                5,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1monitor    // タスクハンドル
                );

#if 0
    xTaskCreate(vTaskCore1Main,         // コールバック関数ポインタ
                "vTaskCore1Main",       // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                7,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1Main       // タスクハンドル
                );
#endif

    g_firmware_info = FW_IDLE;
}

void app_main_core1(void)
{
    // DEBUG_PRINTF("[Core1]Core1 Loop Task\n");
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}