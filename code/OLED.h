//////////////////////////////////////////////////////////////////////////////////	 

/****************************************************************************************************
//=========================================鐢垫簮鎺ョ嚎========================================//
//      5V  鎺C 5V鐢垫簮
//     GND  鎺ュ湴
//======================================OLED灞忔暟鎹嚎鎺ョ嚎=================================//
//鏈ā鍧楁暟鎹€荤嚎绫诲瀷涓篒IC
//     SCL  鎺B13    // IIC鏃堕挓淇″彿
//     SDA  鎺B14    // IIC鏁版嵁淇″彿
//======================================OLED灞忔帶鍒剁嚎鎺ョ嚎======================================//
//鏈ā鍧楁暟鎹€荤嚎绫诲瀷涓篒IC锛屼笉闇€瑕佹帴鎺у埗淇″彿绾�
//=========================================瑙︽懜灞忔帴绾�=========================================//
//鏈ā鍧楁湰韬笉甯﹁Е鎽革紝涓嶉渶瑕佹帴瑙︽懜灞忕嚎
//==================================================================================//
**************************************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "device.h"
#include "F28x_Project.h"
#include "board.h"
#include "stdlib.h"	    	
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC绔彛瀹氫箟----------------

// 浣跨敤HAL搴撳畾涔夛紝鎯充娇鐢ㄥ叾浠栫鍙ｏ紝淇敼绔彛鍊煎嵆鍙�
#define OLED_SCLK_Clr()     GPIO_WritePin(SCL_P37, 0)//CLK
#define OLED_SCLK_Set()     GPIO_WritePin(SCL_P37, 1)

#define OLED_SDIN_Clr()     GPIO_writePin(SDA_P35, 0);//DIN
#define OLED_SDIN_Set()     GPIO_writePin(SDA_P35, 1);
 		     
#define OLED_CMD  0		//鍐欏懡浠�
#define OLED_DATA 1		//鍐欐暟鎹�

#define IIC_SLAVE_ADDR 0x78  //IIC slave device address

//OLED鎺у埗鐢ㄥ嚱鏁�
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(unsigned dat); 
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p,uint8_t Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void Show_Init ();
void IIC_Wait_Ack(void);
void OLED_ShowUnFloat(uint8_t x, uint8_t y, double num, uint8_t precisenum, uint8_t precisefloat, uint8_t size);
#endif
