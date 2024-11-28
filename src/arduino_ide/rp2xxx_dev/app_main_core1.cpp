/**
 * @file app_main_core1.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_main_core1.hpp"
#include "app_filesystem.hpp"
#include "app_sensor.hpp"

#ifdef __WIFI_ENABLE__
char g_ssid[16] = {0};
char g_password[32] = {0};
#endif

static uint8_t s_cpu_core = 0;
static xTaskHandle s_xTaskCore1oled;
static xTaskHandle s_xTaskCore1monitor;
static xTaskHandle s_xTaskCore1Main;
static xTaskHandle s_xTaskCore1Sensor;

#ifdef __LCD_ENABLE__
void vTaskCore1oled(void *p_parameter)
{
    app_oled_init();
    // DEBUG_PRINTF("[Core%X] vTaskCore1oled\n", s_cpu_core);

    while (1)
    {
        if (xSemaphoreTake(xI2CMutex, portMAX_DELAY) == pdTRUE) {
            app_oled_test();
            xSemaphoreGive(xI2CMutex);
        }
        WDT_TOGGLE;
        vTaskDelay(1100 / portTICK_PERIOD_MS);
    }
}
#endif /* __LCD_ENABLE__ */

#ifdef __SENSOR_ENABLE__
void vTaskCore1Sensor(void *p_parameter)
{
    app_sensor_init();
    // DEBUG_PRINTF("[Core%X] vTaskCore1Sensor\n", s_cpu_core);

    while (1)
    {
        if (xSemaphoreTake(xI2CMutex, portMAX_DELAY) == pdTRUE) {
            app_sensor_main();
            xSemaphoreGive(xI2CMutex);
        }
        WDT_TOGGLE;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#endif /* __SENSOR_ENABLE__ */

#ifdef __DEBUG_MONITOR_ENABLE__
void vTaskCore1monitor(void *p_parameter)
{
    while (!Serial) {
        WDT_TOGGLE;
    }
    cpm_init();
    // DEBUG_PRINTF("[Core%X] vTaskCore1monitor\n", s_cpu_core);

    while (1)
    {
        cpm_main();
        WDT_TOGGLE;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
#endif /* __DEBUG_MONITOR_ENABLE__ */

#if 0
void vTaskCore1Main(void *p_parameter)
{
    // DEBUG_PRINTF("[Core%X] vTaskCore1Main\n", s_cpu_core);

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
    s_cpu_core = rp2xxx_get_cpu_core_num();
    WDT_TOGGLE;
    // DEBUG_PRINTF("[Core%X] ... Init\n", s_cpu_core);

    // ファイルシステム(SD/SPIFS/FATFS)
    app_fs_init();

#ifdef __WIFI_ENABLE__
    // WiFi 初期化
    memset(&g_ssid[0], 0x00, sizeof(g_ssid));
    memset(&g_password[0], 0x00, sizeof(g_password));
    app_fs_wifi_config_read(&g_ssid[0], &g_password[0]);

    // TODO:WiFi接続処理
#endif /* __WIFI_ENABLE__ */

    // FreeRTOS初期化

#ifdef __LCD_ENABLE__
    xTaskCreate(vTaskCore1oled,         // コールバック関数ポインタ
                "vTaskCore1oled",       // タスク名
                1024,                   // スタック
                nullptr,                // パラメータ
                3,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1oled       // タスクハンドル
                );
#endif /* __LCD_ENABLE__ */

#ifdef __SENSOR_ENABLE__
    xTaskCreate(vTaskCore1Sensor,       // コールバック関数ポインタ
                "vTaskCore1Sensor",     // タスク名
                1024,                   // スタック
                nullptr,                // パラメータ
                2,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1Sensor     // タスクハンドル
                );
#endif /* __SENSOR_ENABLE__ */

#ifdef __DEBUG_MONITOR_ENABLE__
    xTaskCreate(vTaskCore1monitor,      // コールバック関数ポインタ
                "vTaskCore1monitor",    // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                5,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1monitor    // タスクハンドル
                );
#endif /* __DEBUG_MONITOR_ENABLE__ */

#if 0
    xTaskCreate(vTaskCore1Main,         // コールバック関数ポインタ
                "vTaskCore1Main",       // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                7,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1Main       // タスクハンドル
                );
#endif
}

void app_main_core1(void)
{
    // DEBUG_PRINTF("[Core1]Core1 Loop Task\n");
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}