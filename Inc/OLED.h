/**
 * @file OLED.h
 * @author yyy
 * @brief OELD DRIVER
 * @version 0.1
 * @date 2023.07.25
 * @protype IIC
 * @pinset
 *    5V  - DC-Source
 *    GND - GND
 *    SCL - PB13
 *    SDA - PB14
 *
 * @attention This module does not support the touch function
 *            and can be disconnected from related cables
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __OLED_H
#define __OLED_H

#include "bsp_config.h"

#define OLED_MODE 0
#define SIZE 8
#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64

/* Using the HAL library definition,if you want to
 * use other ports, you can change the port value
 */
#define OLED_SCLK_Clr() GPIO_WritePin(GPIO_PIN_I2CA_SCL, 0) // CLK
#define OLED_SCLK_Set() GPIO_WritePin(GPIO_PIN_I2CA_SCL, 1)

#define OLED_SDIN_Clr() GPIO_writePin(GPIO_PIN_I2CA_SDA, 0); // DIN
#define OLED_SDIN_Set() GPIO_writePin(GPIO_PIN_I2CA_SDA, 1);

/* write command */
#define OLED_CMD 0
/* write data */
#define OLED_DATA 1

#define IIC_SLAVE_ADDR 0x78 // IIC slave device address

// oled control functions
void OLED_WR_Byte(unsigned dat, unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(unsigned dat);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_Fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *p, uint8_t Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void Show_Init();
void IIC_Wait_Ack(void);
void OLED_ShowUnFloat(uint8_t x, uint8_t y, double num, uint8_t precisenum, uint8_t precisefloat, uint8_t size);

#endif /* !__OLED_H */
