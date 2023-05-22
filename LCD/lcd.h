#include "sys.h"
#include "stdlib.h"
#include "ctype.h"
#define ILI9341
  

//LCD的画笔颜色和背景色	   
extern u16  COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定义---------------- 
#define	LCD_LED PBout(0) //LCD背光  PB0 	    
//LCD地址结构体
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;

//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线     
#define LCD_BASE    ((u32)(0x6C000000 | 0x000007FE))
#define LCD         ((LCD_TypeDef *) LCD_BASE)
#define LCDData     LCD->LCD_RAM
#define LCDIns      LCD->LCD_REG
//////////////////////////////////////////////////////////////////////////////////
	 	 
//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
	    															  
void LCD_Init(void);													   	//初始化
void LCD_DisplayOn(void);													//开显示
void LCD_DisplayOff(void);												//关显示
void Clear(u16 colorval);                         //清屏
void LcdPutchar(u16 size,char ascii,u16 x,u16 y);//打印字母

u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM(u16 RGB_Code);
void LcdScanDir(char type);									//设置屏扫描方向
void SetCursor(u16 x,u16 y,u16 width,u16 height);//设置光标			   						   																			 




