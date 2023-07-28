/**
 * @file bsp_config.h
 * @author July (Email: JulyCub@163.com)
 * @brief BSP CONFIG FILE
 * @version 0.1
 * @date 2023.07.28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __BSP_CONFIG_H__
#define __BSP_CONFIG_H__

/* BOARD SELECT */
#define __BSP_BOARDUSE_F280049C 1

/* OLED */
#ifndef __BSP_OLED_ENABLED
#define __BSP_OLED_ENABLED 0
#endif

/* LED */
#ifndef __BSP_LED_ENABLED
#define __BSP_LED_ENABLED 1
#endif

/* UART */
#ifndef __BSP_UART_ENABLED
#define __BSP_UART_ENABLED 1
#endif

/* EPWM */
#ifndef __BSP_EPWM_ENABLED
#define __BSP_EPWM_ENABLED 0
#endif

#include "device.h"
#include "board.h"
#include "F28x_Project.h"

#if __BSP_OLED_ENABLED
#include "OLED.h"
#endif /* __BSP_OLED_ENABLED */

#if __BSP_LED_ENABLED
#include "bsp_led.h"
#endif /* __BSP_LED_ENABLED */

#if __BSP_UART_ENABLED
#include "Y_uart.h"
#endif /* __BSP_UART_ENABLED */

#if __BSP_EPWM_ENABLED
#include "Y_epwm.h"
#endif /* __BSP_EPWM_ENABLED */

#endif /* __BSP_CONFIG_H__ */
