# STM32F103x
My MCU library for C

从RAM启动STM32
cpuRAM.ini 该文件为从RAM启动的MDK启动配置文件，配合全局定义VECT_TAB_SRAM使用。
步骤 
  添加全局定义
  修改程序段储存地址和大小
  修改数据段存储地址和大小
  Debug选项卡添加初始化文件：cpuRAM.ini
  取消勾选Update Target before Debugging
  调试Flash Download选项卡，选择不擦除，取消勾选Reset and Run
END

LCD_ILI9341 ILI9341的驱动代码
