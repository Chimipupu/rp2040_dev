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
#include "dbg_cmd.h"

#ifdef RGBLED_PIN
#include "app_neopixel.h"
#endif

// C Lib
#include <stdio.h>

// Arduino IDE Lib
#include <Arduino.h>

// ---------------------------------------------------
static unsigned int DBG_LOG_PRINT(const char *p_fmt, ...);
static E_DBG_CMD_RESULT _cmd_rgbled(void *p_args);
static const dbg_cmd_tbl_t s_ext_cmd_tbl[] = {
    {"rgbled", "rl", _cmd_rgbled},
};
static uint8_t _serial_read_func(void);

const dbg_cmd_config_t g_dbg_cmd_config = {
    .p_serial_read = _serial_read_func,
    .p_printf = DBG_LOG_PRINT,
    .p_ext_cmd_tbl = (dbg_cmd_tbl_t *)s_ext_cmd_tbl,
    .ext_cmd_num = sizeof(s_ext_cmd_tbl) / sizeof(s_ext_cmd_tbl[0]),
};

// ---------------------------------------------------
// [Static関数]
static unsigned int DBG_LOG_PRINT(const char *p_fmt, ...)
{
    char buf[256];
    va_list args;

    va_start(args, p_fmt);
    unsigned int ret = vsnprintf(buf, sizeof(buf), p_fmt, args);
    Serial.print(buf);
    va_end(args);

    return ret;
}

static uint8_t _serial_read_func(void)
{
    return (uint8_t)Serial.read();
}

static E_DBG_CMD_RESULT _cmd_rgbled(void *p_args)
{
    DBG_LOG_PRINT("rgbled cmd\n");
    return CMD_RESULT_EXEC_OK;
}

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
    // TODO
}

// ---------------------------------------------------
// ********** [CPU Core 1] ***********
/**
 * @brief アプリ初期化 Core 1
 */
void app_main_core_1_init(void)
{
    dbg_cmd_init((dbg_cmd_config_t *) &g_dbg_cmd_config);
}

/**
 * @brief アプリメイン Core 1
 */
void app_main_core_1(void)
{
    dbg_cmd_poll();
    dbg_cmd_main();
    delay(10);
}

// ---------------------------------------------------