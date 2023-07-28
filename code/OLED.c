/*********************************************************************************************
// yfyfyf
//============================================================================================//
  * @attention
  * blank
**************************************************************************************************/
//=========================================鐢垫簮鎺ョ嚎================================================//
//      5V  鎺C 5V鐢垫簮
//     GND  鎺ュ湴
//======================================OLED灞忔暟鎹嚎鎺ョ嚎==========================================//
//鏈ā鍧楁暟鎹€荤嚎绫诲瀷涓篒IC
//     SCL  鎺B13    // IIC鏃堕挓淇″彿
//     SDA  鎺B14    // IIC鏁版嵁淇″彿
//======================================OLED灞忔帶鍒剁嚎鎺ョ嚎==========================================//
//鏈ā鍧楁暟鎹€荤嚎绫诲瀷涓篒IC锛屼笉闇€瑕佹帴鎺у埗淇″彿绾�
//=========================================瑙︽懜灞忔帴绾�=========================================//
//鏈ā鍧楁湰韬笉甯﹁Е鎽革紝涓嶉渶瑕佹帴瑙︽懜灞忕嚎
//============================================================================================//


#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"

void Show_Init ()
{
	OLED_Init();			//鍒濆鍖朞LED
    OLED_Clear(0); 
	OLED_ShowString(0,0,(uint8_t *)"Temp:",16);
	OLED_ShowString(0,2,(uint8_t *)"Humi:",16);
	OLED_ShowString(0,4,(uint8_t *)"Volt:",16);
}

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	OLED_SCLK_Set();
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//璁剧疆PB12涓轰笂鎷夎緭鍏ユā寮�
	//GPIOB->CRH |= 0x00080000;
//	OLED_SDA = 1;
//	delay_us(1);
	//OLED_SCL = 1;
	//delay_us(50000);
/*	while(1)
	{
		if(!OLED_SDA)				//鍒ゆ柇鏄惁鎺ユ敹鍒癘LED 搴旂瓟淇″彿
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//璁剧疆PB12涓洪€氱敤鎺ㄥ厤杈撳嚭妯″紡
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(IIC_SLAVE_ADDR);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(IIC_SLAVE_ADDR);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//鍧愭爣璁剧疆
void OLED_Set_Pos(unsigned char x, unsigned char y)
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//寮€鍚疧LED鏄剧ず
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC锟斤拷锟斤拷
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//鍏抽棴OLED鏄剧ず
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC锟斤拷锟斤拷
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//娓呭睆鍑芥暟,娓呭畬灞�,鏁翠釜灞忓箷鏄粦鑹茬殑,鍜屾病鐐逛寒涓€鏍�
void OLED_Clear(unsigned dat)  
{  
	uint8_t i,n;
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //璁剧疆椤靛湴鍧€锛�0~7锛�
		OLED_WR_Byte (0x00,OLED_CMD);      //璁剧疆鏄剧ず浣嶇疆鈥斿垪浣庡湴鍧€址
		OLED_WR_Byte (0x10,OLED_CMD);      //璁剧疆鏄剧ず浣嶇疆鈥斿垪楂樺湴鍧€
		for(n=0;n<128;n++)OLED_WR_Byte(dat,OLED_DATA); 
	} //鏇存柊鏄剧ず
}

void OLED_On(void)  
{  
	uint8_t i,n;
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //璁剧疆椤靛湴鍧€锛�0~7锛�
		OLED_WR_Byte (0x00,OLED_CMD);      //璁剧疆鏄剧ず浣嶇疆鈥斿垪浣庡湴鍧€址
		OLED_WR_Byte (0x10,OLED_CMD);      //璁剧疆鏄剧ず浣嶇疆鈥斿垪楂樺湴鍧€
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	}
}
//鍦ㄦ寚瀹氫綅缃樉绀轰竴涓瓧绗�,鍖呮嫭閮ㄥ垎瀛楃
//x:0~127
//y:0~63
//mode:0,鍙嶇櫧鏄剧ず;1,姝ｅ父鏄剧ず
//size:閫夋嫨瀛椾綋 16/12
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';		//寰楀埌鍋忕Щ鍚庣殑鍊�
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n鍑芥暟
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)result*=m;    
	return result;
}				  
//鏄剧ず2涓暟瀛�
//x,y :璧风偣鍧愭爣
//len :鏁板瓧鐨勪綅鏁�
//size:瀛椾綋澶у皬
//mode:妯″紡	0,濉厖妯″紡;1,鍙犲姞妯″紡
//num:鏁板€�(0~4294967295);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//鏄剧ず涓€涓瓧绗﹀彿涓�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//鏄剧ず姹夊瓧
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********鍔熻兘鎻忚堪锛氭樉绀烘樉绀築MP鍥剧墖128脳64璧峰鐐瑰潗鏍�(x,y),x鐨勮寖鍥�0锝�127锛寉涓洪〉鐨勮寖鍥�0锝�7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//鍒濆鍖�
void OLED_Init(void)
{ 	
 
	
    DEVICE_DELAY_US(20000);

	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  

/*
鍑芥暟鍔熻兘锛氭樉绀烘棤绗﹀彿float鏁板瓧
鍙傛暟锛歺y鍧愭爣锛宯um鏄剧ず鏁板瓧锛宲recise鏄剧ず鏁板瓧鐨勭簿搴︼紝size鏁板瓧澶у皬妯″紡
杩斿洖鍊硷細鏃�
*/
void OLED_ShowUnFloat(uint8_t x, uint8_t y, double num, uint8_t precisenum, uint8_t precisefloat, uint8_t size)
{
	uint8_t i = 0, j;

	uint16_t integer;
	double decimal;
	
	for(j = precisefloat;j > 0; j--)
	{
		num*=10;
	}
	if((int)(num*10)%10 >= 5)
	{
		num+=1;
	}
	for(j = precisefloat;j > 0; j--)
	{
		num/=10;
	}
	integer = (int)num;//鏁存暟閮ㄥ垎
	decimal = (double)(num - integer);//灏忔暟閮ㄥ垎
	
	OLED_ShowNum(x,y,integer,precisenum,size);//鏄剧ず鏁存暟閮ㄥ垎
	OLED_ShowChar(x+(size/2)*(precisenum),y,'.',size);//鏄剧ず灏忔暟鐐�
	
	x = x+(size/2)*(precisenum+2);
	while (precisefloat)//鏄剧ず鍑犱綅灏忔暟
	{
		decimal = decimal * 10;
		integer = (int)decimal;//鍙栧嚭涓€浣嶅皬鏁�
		decimal = (double)(decimal - integer);
		OLED_ShowChar(x+(size/2)*(i - 1), y, integer + '0', size);//寰幆鏄剧ず姣忎綅鏁板瓧瀛楃锛屼粠楂樹綅鏄剧ず
		i++;
		precisefloat--;
	}
}
