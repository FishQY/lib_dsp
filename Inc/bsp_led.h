/**
 * @file bsp_led.h
 * @author July (Email: JulyCub@163.com)
 * @brief led drober header file
 * @version 0.1
 * @date 2023.07.28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __BSP_LED_H__
#define __BSP_LED_H__
#include "bsp_config.h"

#if __BSP_BOARDUSE_F280049C
#define LED1_GPIO_PORT GPIO_23_GPIO23
#define LED2_GPIO_PORT GPIO_34_GPIO34
#define LED1_GPIO_PIN 23
#define LED2_GPIO_PIN 34

/* TIM-uint ms */
#define __BSP_LED1_FLICKER(__TIM__)    \
    {                                  \
        GPIO_togglePin(LED1_GPIO_PIN); \
        DELAY_US(__TIM__ * 1000);      \
        GPIO_togglePin(LED1_GPIO_PIN); \
        DELAY_US(__TIM__ * 1000);      \
    }

/* TIM-uint ms */
#define __BSP_LED2_FLICKER(__TIM__)    \
    {                                  \
        GPIO_togglePin(LED2_GPIO_PIN); \
        DELAY_US(__TIM__ * 1000);      \
        GPIO_togglePin(LED2_GPIO_PIN); \
        DELAY_US(__TIM__ * 1000);      \
    }
#endif

void BSP_LED_Init(void);

#endif /* __BSP_LED_H__ */
