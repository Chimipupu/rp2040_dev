/**
 * @file multi_core_cpu.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief マルチコアCPU関連のヘッダー
 * @version 0.1
 * @date 2026-08-29
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */
#ifndef MULTI_CORE_CPU_HPP
#define MULTI_CORE_CPU_HPP

#include <stdint.h>

// ---------------------------------------------------
// CPU FIFO関連
#define CPU_FIFO_DATA_SIZE           4 // CPU FIFOのデータ長
#define CPU_FIFO_BUF_SIZE            8 // CPU FIFOのバッファサイズ
#define CPU_FIFO_DATA_INIT_MSG       0xFFFFFFFF
#define CPU_FIFO_DATA_NONE           0

#define CPU_FIFO_DATA_BIT            0x00FFFFFF

#define CPU_FIFO_DATA_TYPE_BIT       0xFF000000
typedef enum {
    CPU_FIFO_DATA_TYPE_CONFIG = 0,
    CPU_FIFO_DATA_TYPE_REQUEST,
    CPU_FIFO_DATA_TYPE_RESULT,
    CPU_FIFO_DATA_TYPE_MSG_ASCII,
    CPU_FIFO_DATA_TYPE_RGBLED,
    CPU_FIFO_DATA_TYPE_DEBUG = 0xFF,
} E_CPU_FIFO_DATA;


typedef struct {
    uint32_t tx_fifo_buf[CPU_FIFO_BUF_SIZE];
    uint32_t rx_fifo_buf[CPU_FIFO_BUF_SIZE];
} cpu_fifo_t;

// ---------------------------------------------------
bool cpu_fifo_tx_data(uint32_t data);
bool cpu_fifo_rx_data(uint32_t *p_data);
void cpu_core_0_init(void);
void cpu_core_1_init(void);
void cpu_core_0_main(void);
void cpu_core_1_main(void);

// ---------------------------------------------------

#endif // MULTI_CORE_CPU_HPP