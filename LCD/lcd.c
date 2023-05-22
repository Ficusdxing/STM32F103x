#include "lcd.h"
#include "font.h"
#include "delay.h"	

#ifdef ILI9341
	#define WIDTH 240
	#define HEIGHT 320
#endif

u16 COLOR = 0x00;
u16 BACK_COLOR = 0x00;

//LCD指令存储结构体
struct LCDDataStruct
{
	u8 InsMemWR;
	u8 InsMemRD;
}LCDds;

//初始化lcd
//该初始化函数可以初始化各种ILI93XX液晶
void LCD_Init(void)
{ 					
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//使能FSMC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//使能PORTB,D,E,G以及AFIO复用功能时钟

 
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PB0 推挽输出 背光
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
 	//PORTD复用推挽输出  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE复用推挽输出  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12复用推挽输出 A0	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure); 

	readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //地址建立时间（ADDSET）为2个HCLK 1/36M=27ns
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
  readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // 数据保存时间为16个HCLK,因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

	writeTiming.FSMC_AddressSetupTime = 0x00;	 //地址建立时间（ADDSET）为1个HCLK  
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
  writeTiming.FSMC_DataSetupTime = 0x03;		 ////数据保存时间为4个HCLK	
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x00;
  writeTiming.FSMC_DataLatency = 0x00;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

 
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
		
 
	delay_ms(50); 					// delay 50 ms 
  	
	#ifdef ILI9341	
	LCDIns = 0xCF;  
	LCDData = 0x00; 
	LCDData = 0xC1; 
	LCDData = 0X30; 
	LCDIns = 0xED;  
	LCDData= 0x64; 
	LCDData = 0x03; 
	LCDData = 0X12; 
	LCDData = 0X81; 
	LCDIns = 0xE8;  
	LCDData = 0x85; 
	LCDData = 0x10; 
	LCDData = 0x7A; 
	LCDIns = 0xCB;  
	LCDData = 0x39; 
	LCDData = 0x2C; 
	LCDData = 0x00; 
	LCDData = 0x34; 
	LCDData = 0x02; 
	LCDIns = 0xF7;  
	LCDData = 0x20; 
	LCDIns = 0xEA;  
	LCDData = 0x00; 
	LCDData = 0x00; 
	LCDIns = 0xC0;    //Power control 
	LCDData = 0x1B;   //VRH[5:0] 
	LCDIns = 0xC1;    //Power control 
	LCDData = 0x01;   //SAP[2:0];BT[3:0] 
	LCDIns = 0xC5;    //VCM control 
	LCDData = 0x30; 	 //3F
	LCDData = 0x30; 	 //3C
	LCDIns = 0xC7;    //VCM control2 
	LCDData = 0XB7; 
	LCDIns = 0x36;    // Memory Access Control 
	LCDData = 0x08; 
	LCDIns = 0x3A;   
	LCDData = 0x55; 
	LCDIns = 0xB1;   
	LCDData = 0x00;   
	LCDData = 0x1A; 
	LCDIns = 0xB6;    // Display Function Control 
	LCDData = 0x0A; 
	LCDData = 0xA2; 
	LCDIns = 0xF2;    // 3Gamma Function Disable 
	LCDData = 0x00; 
	LCDIns = 0x26;    //Gamma curve selected 
	LCDData = 0x01; 
	LCDIns = 0xE0;    //Set Gamma 
	LCDData = 0x0F; 
	LCDData = 0x2A; 
	LCDData = 0x28; 
	LCDData = 0x08; 
	LCDData = 0x0E; 
	LCDData = 0x08; 
	LCDData = 0x54; 
	LCDData = 0XA9; 
	LCDData = 0x43; 
	LCDData = 0x0A; 
	LCDData = 0x0F; 
	LCDData = 0x00; 
	LCDData = 0x00; 
	LCDData = 0x00; 
	LCDData = 0x00; 		 
	LCDIns = 0XE1;    //Set Gamma 
	LCDData = 0x00; 
	LCDData = 0x15; 
	LCDData = 0x17; 
	LCDData = 0x07; 
	LCDData = 0x11; 
	LCDData = 0x06; 
	LCDData = 0x2B; 
	LCDData = 0x56; 
	LCDData = 0x3C; 
	LCDData = 0x05; 
	LCDData = 0x10; 
	LCDData = 0x0F; 
	LCDData = 0x3F; 
	LCDData = 0x3F; 
	LCDData = 0x0F; 
	LCDIns = 0x2B; 
	LCDData = 0x00;
	LCDData = 0x00;
	LCDData = 0x01;
	LCDData = 0x3f;
	LCDIns = 0x2A; 
	LCDData = 0x00;
	LCDData = 0x00;
	LCDData = 0x00;
	LCDData = 0xef;	 
	LCDIns = 0x11; //Exit Sleep
	delay_ms(120);
	LCDIns = 0x29; //display on
	
	LCDIns = 0x36;//默认为竖屏
	LCDData = 0x08;
	LCDds.InsMemWR = 0x2C;
	LCDds.InsMemRD = 0x2E;
	#endif
	LCD_LED=1;				//点亮背光
  Clear(WHITE);
}

//画点
//9341
//Memory Write(2Ch)
void Drawdot(u16 x,u16 y)
{
	
	//set Start Column 
	LCDIns = 0x2A;
	LCDData = x>>8;
	LCDData = x;
	LCDData = 0;
	LCDData = 0xF0;
	//set Start Page
	LCDIns = 0x2B;
	LCDData = y>>8;
	LCDData = y;
	LCDData = 0x01;
	LCDData = 0x40;
	//Write
	LCDIns = 0x2C;
	LCDData = COLOR;
}

void Clear(u16 colorval)
{
	//set Start Column 
	LCDIns = 0x2A;
	LCDData = 0;
	LCDData = 0;
	LCDData = 0;
	LCDData = 0xF0;
	//set Start Page
	LCDIns = 0x2B;
	LCDData = 0;
	LCDData = 0;
	LCDData = 0x01;
	LCDData = 0x40;
	//Write
	LCDIns = 0x2C;
	for(int i = 0;i<86400;i++)
		{
			LCDData = colorval;
		}
	BACK_COLOR = colorval;
		return;
}

//LCD显示字母
//该函数会把屏幕显示方向改变
void LcdPutchar(u16 size,char ascii,u16 x,u16 y)
{
	if(isprint(ascii))
		{
		//该大小一列点阵的大小
		unsigned char VolumeColum = size/8+((size%8)?1:0);
	////该大小字符所占字节
	//unsigned char volume = VolumeColum*(size/2);
		
		//字库偏移量
		char offset = ascii - ' ';

		//转换为点阵打印显示方向
		//点阵字符捕获指针
		const unsigned char* p = NULL;
		//指针指向对应字符点阵
		switch (size)
		{
			case 12: 
				p = &asc2_1206[offset][0];
				break;
			case 16: 
				p = &asc2_1608[offset][0];
				break;
			case 24: 
				p = &asc2_2412[offset][0];
				break;
			default:
				return;
		}
		LcdScanDir(1);
		//设置光标
		SetCursor(y,x,size,size/2);
		//扫描点阵
		LCDIns = LCDds.InsMemWR;
		
		//扫描一个字符
		//点阵扫描指针
		const unsigned char * pScan = p;
		for(int k = 0;k < size/2;k++)
		{
			//扫描一列
			for(int j = 0;j < VolumeColum;j++)
			{
				//扫描一字节
				for(int i=0;i < 8 && i < size - 8*j;i++)
				{
					if(0x80&(*(pScan)<<i))
						LCDData = COLOR;
					else 	
						LCDData = BACK_COLOR;
				}
				pScan++;
			}
		}
	}
		return ; 
}
	
//LCD打印字符串“”
void LCDPrint(u16 size,char* str,u16 x,u16 y)
{
	
}
	void LcdScanDir(char type)
	{
		switch(type)
		{
			//从左到右，从上到下
			case 0:
				LCDIns = 0x36;
				LCDData = 0x08;
				break;
			//从上到下，从左到右
			case 1:
				LCDIns = 0x36;
				LCDData = 0x28;
				break;
			default:
				return;
		}
}

void SetCursor(u16 x,u16 y,u16 width,u16 height)
{
	//set Start Column 
	LCDIns = 0x2A;
	LCDData = x>>8;
	LCDData = x;
	LCDData = (x+width-1)>>8;
	LCDData = x+width-1;
	//set Start Page
	LCDIns = 0x2B;
	LCDData = y>>8;
	LCDData = y;
	LCDData = (y+height)>>8;
	LCDData = y+height;
	return;
}






