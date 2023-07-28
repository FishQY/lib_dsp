/**
 * @file bsp_led.c
 * @author July (Email: JulyCub@163.com)
 * @brief led driver
 * @version 0.1
 * @date 2023.07.28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "bsp_led.h"

/**
 * @brief led init
 */
void BSP_LED_Init(void)
{
    EALLOW;

    GPIO_setPinConfig(LED1_GPIO_PORT);
    GPIO_setPinConfig(LED2_GPIO_PORT);

    GPIO_setPadConfig(LED1_GPIO_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(LED1_GPIO_PIN, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(LED1_GPIO_PIN, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(LED1_GPIO_PIN, GPIO_CORE_CPU1);

    GPIO_setPadConfig(LED2_GPIO_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(LED2_GPIO_PIN, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(LED2_GPIO_PIN, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(LED2_GPIO_PIN, GPIO_CORE_CPU1);

    EDIS;
}

