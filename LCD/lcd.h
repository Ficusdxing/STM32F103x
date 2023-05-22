#include "sys.h"
#include "stdlib.h"
#include "ctype.h"
#define ILI9341
  

//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	LCD_LED PBout(0) //LCD����  PB0 	    
//LCD��ַ�ṹ��
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;

//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ��������������     
#define LCD_BASE    ((u32)(0x6C000000 | 0x000007FE))
#define LCD         ((LCD_TypeDef *) LCD_BASE)
#define LCDData     LCD->LCD_RAM
#define LCDIns      LCD->LCD_REG
//////////////////////////////////////////////////////////////////////////////////
	 	 
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);												//����ʾ
void Clear(u16 colorval);                         //����
void LcdPutchar(u16 size,char ascii,u16 x,u16 y);//��ӡ��ĸ

u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM(u16 RGB_Code);
void LcdScanDir(char type);									//������ɨ�跽��
void SetCursor(u16 x,u16 y,u16 width,u16 height);//���ù��			   						   																			 




