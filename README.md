## 功能说明
1. 通过`stm32h743iit6`的`FMC`外扩一个`32MBytes`的`SDRAM`;
2. 添加`DMA2D`用于将`FrameBuffer`的图像数据传输到`LTD`;
3. 添加`LTDC`用于驱动显示屏;
4. 添加触摸屏驱动(通过`I2C`协议交互);
5. 更多配置细节，可以通过`stm32cubeMx`打开配置工程文件查看;

## 注意
1. 如果开启了`MPU(内存保护单元)`，一定要为外扩的`SDRAM`开启可访问的功能，不然访问时会出现`MemManage_Handler`错误;

