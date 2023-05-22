#include "lcd.h"
#include "font.h"
#include "delay.h"	

#ifdef ILI9341
	#define WIDTH 240
	#define HEIGHT 320
#endif

u16 COLOR = 0x00;
u16 BACK_COLOR = 0x00;

//LCDָ��洢�ṹ��
struct LCDDataStruct
{
	u8 InsMemWR;
	u8 InsMemRD;
}LCDds;

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��
void LCD_Init(void)
{ 					
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//ʹ��FSMCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTB,D,E,G�Լ�AFIO���ù���ʱ��

 
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PB0 ������� ����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
 	//PORTD�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12����������� A0	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure); 

	readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
  readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

	writeTiming.FSMC_AddressSetupTime = 0x00;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A		
  writeTiming.FSMC_DataSetupTime = 0x03;		 ////���ݱ���ʱ��Ϊ4��HCLK	
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x00;
  writeTiming.FSMC_DataLatency = 0x00;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 

 
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK1 
		
 
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
	
	LCDIns = 0x36;//Ĭ��Ϊ����
	LCDData = 0x08;
	LCDds.InsMemWR = 0x2C;
	LCDds.InsMemRD = 0x2E;
	#endif
	LCD_LED=1;				//��������
  Clear(WHITE);
}

//����
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

//LCD��ʾ��ĸ
//�ú��������Ļ��ʾ����ı�
void LcdPutchar(u16 size,char ascii,u16 x,u16 y)
{
	if(isprint(ascii))
		{
		//�ô�Сһ�е���Ĵ�С
		unsigned char VolumeColum = size/8+((size%8)?1:0);
	////�ô�С�ַ���ռ�ֽ�
	//unsigned char volume = VolumeColum*(size/2);
		
		//�ֿ�ƫ����
		char offset = ascii - ' ';

		//ת��Ϊ�����ӡ��ʾ����
		//�����ַ�����ָ��
		const unsigned char* p = NULL;
		//ָ��ָ���Ӧ�ַ�����
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
		//���ù��
		SetCursor(y,x,size,size/2);
		//ɨ�����
		LCDIns = LCDds.InsMemWR;
		
		//ɨ��һ���ַ�
		//����ɨ��ָ��
		const unsigned char * pScan = p;
		for(int k = 0;k < size/2;k++)
		{
			//ɨ��һ��
			for(int j = 0;j < VolumeColum;j++)
			{
				//ɨ��һ�ֽ�
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
	
//LCD��ӡ�ַ�������
void LCDPrint(u16 size,char* str,u16 x,u16 y)
{
	
}
	void LcdScanDir(char type)
	{
		switch(type)
		{
			//�����ң����ϵ���
			case 0:
				LCDIns = 0x36;
				LCDData = 0x08;
				break;
			//���ϵ��£�������
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






