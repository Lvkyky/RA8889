
  /*************** RAIO Technology Inc. ***************
  * product		: RA8889
  * file		: RA8889.h
  * author		: Henry 
  * version		: ver 0.0 
  * date		: 2020/03/30 
  RAIO Technology Inc. copyright all rights reserved.
  ****************************************************/	

#ifndef __RA8889_H
#define __RA8889_H


void RA8889_HW_Reset(void);
void RA8889_Initial(void);
void Check_IC_ready(void);
void RA8889_SW_Reset(void);
void RA8889_PLL(unsigned short DRAM_clock, unsigned short CORE_clock, unsigned short SCAN_clock);
void RA8889_SDRAM_initial(void);
void TFT_24bit(void);
void Host_Bus_8bit(void);
void Data_Format_8b_24bpp(void);
void MemWrite_Left_Right_Top_Down(void);
void Graphic_Mode(void);
void Memory_Select_SDRAM(void);
void Select_Main_Window_24bpp(void);
void Memory_24bpp_Mode(void);
void Select_PIP1_Window_24bpp(void);
void Select_PIP2_Window_24bpp(void);
void BTE_S0_Color_24bpp(void);
void BTE_S1_Color_24bpp(void);
void BTE_Destination_Color_24bpp(void);
void IDEC_Destination_Color_24bpp(void);
void Set_LCD_Panel(void);
void Main_Image_Start_Address(unsigned long Addr);
void Main_Image_Width(unsigned short WX);
void Main_Window_Start_XY(unsigned short WX,unsigned short HY);
void Canvas_Image_Start_address(unsigned long Addr)	;
void Canvas_image_width(unsigned short WX);
void Active_Window_XY(unsigned short WX,unsigned short HY);
void Active_Window_WH(unsigned short WX,unsigned short HY);
void Goto_Pixel_XY(unsigned short WX,unsigned short HY);
unsigned char LCD_RegisterRead(unsigned char Cmd);
void LCD_RegisterWrite(unsigned char Cmd,unsigned char Data);
void Memory_XY_Mode(void);
void Set_Serial_Flash_IF(void);
void Display_ON(void);
void Color_Bar_ON(void);
void Color_Bar_OFF(void);
void Enable_PLL(void);
void Check_SDRAM_Ready(void);
void REG_Switch_to_REG1(void);
void REG_Switch_to_REG0(void);
void Check_2D_Busy(void);
void Enable_SFlash_SPI(void);
void GTFont_Select_GT30L24T3Y(void);
void IDEC_Select_SFI_24bit_Address(void);
void Select_standard_SPI_Mode0_or_Mode3(void);
void Select_SFI_24bit_Address(void);
void Select_SFI_Single_Mode_Dummy_0T_03h(void);
void Set_CPOL(void);
void Set_CPHA(void);
void Reset_CPOL(void);
void Reset_CPHA(void);
void SPI_Clock_Period(unsigned char temp);
void Select_LCD_DE_Mode(void);
void PCLK_Falling(void);
void VSCAN_T_to_B(void);
void PDATA_Set_RGB(void);
void PDATA_Set_BGR(void);
void HSYNC_Low_Active(void);
void DE_High_Active(void);
void LCD_HorizontalWidth_VerticalHeight(unsigned short WX,unsigned short HY);
void VSYNC_Low_Active(void);
void LCD_Horizontal_Non_Display(unsigned short WX);
void LCD_HSYNC_Start_Position(unsigned short WX);
void LCD_HSYNC_Pulse_Width(unsigned short WX);
void LCD_Vertical_Non_Display(unsigned short HY);
void LCD_VSYNC_Start_Position(unsigned short HY);
void LCD_VSYNC_Pulse_Width(unsigned short HY);
void VSCAN_B_to_T(void);
void Select_LCD_Sync_Mode(void);
void HSCAN_R_to_L(void);
void HSCAN_L_to_R(void);
//跟初始化8889相关的函数

void Foreground_color_16M(unsigned long temp);
void BTE_Destination_Memory_Start_Address(unsigned long Addr);
void BTE_Destination_Image_Width(unsigned short WX)	;
void BTE_Destination_Window_Start_XY(unsigned short WX,unsigned short HY);
void BTE_Window_Size(unsigned short WX, unsigned short HY);
void BTE_Operation_Code(unsigned char setx);
void BTE_Enable(void);
void Check_BTE_Busy(void);
void BTE_S0_Memory_Start_Address(unsigned long Addr);
void BTE_S0_Image_Width(unsigned short WX);
void BTE_S0_Window_Start_XY(unsigned short WX,unsigned short HY);
void BTE_S1_Memory_Start_Address(unsigned long Addr);
void BTE_S1_Image_Width(unsigned short WX);
void BTE_S1_Window_Start_XY(unsigned short WX,unsigned short HY);
void BTE_ROP_Code(unsigned char setx);
//跟BTE相关的函数

void SPI_Master_LatchEdge_Select_Falling(void);
void SPIM_Clock_Divided_1(void);
void IDEC_SPI_Clock_Divide(unsigned char IDEC_SPIclock_divide);
void IDEC_Select_Bus_0(void);
void SPIM_Select_Bus_0(void);
void IDEC_Select_Bus_1(void);
void SPIM_Select_Bus_1(void);
void IDEC_Select_SFI_0(void);
void Select_nSS_drive_on_xnsfcs0(void);
void IDEC_Select_SFI_1(void);
void Select_nSS_drive_on_xnsfcs1(void);
void IDEC_Select_SFI_2(void);
void Select_nSS_drive_on_xnsfcs2(void);
void IDEC_Select_SFI_3(void);
void Select_nSS_drive_on_xnsfcs3(void);
void nSS_Active(void);
unsigned char SPI_Master_FIFO_Data_Put(unsigned char Data);
void nSS_Inactive(void);
void IDEC_Select_SFI_32bit_Address(void);
void IDEC_Select_RA8875_SPI_Mode0_and_Mode3(void);
void IDEC_AVI_Decoding_to_PIP1_and_Shadow(void);
void IDEC_Select_SFI_Quad_Mode_Dummy_8T_6Bh(void);
void IDEC_Destination_Image_Width(unsigned short WX);// ,JPG,BMP	// 
void IDEC_Destination_Upper_Left_Corner(unsigned short WX,unsigned short HY);
void IDEC_Source_Start_Address(unsigned long Addr);//AVI,JPG,BMP	// 
void IDEC_Transfer_Number(unsigned long Num);
void IDEC_Starts_Decoding(void);
void Check_Busy_Media_Decode(void);
unsigned char Tx_FIFO_Empty_Flag(void);
unsigned char SPI_Master_FIFO_Data_Get(void);
unsigned char Rx_FIFO_Empty_Flag(void);
//跟jpeg相关的API


void Background_color_16M(unsigned long temp);
void Font_Select_8x16_16x16(void);
void Font_Select_12x24_24x24(void);
void Font_Select_16x32_32x32(void);
void Font_Width_X1(void);
void Font_Width_X2(void);
void Font_Width_X3(void);
void Font_Width_X4(void);
void Font_Height_X1(void);
void Font_Height_X2(void);
void Font_Height_X3(void);
void Font_Height_X4(void);
void Font_Background_select_Color(void);
void Font_Background_select_Original_Canvas(void);
void Disable_Font_Alignment(void);
void Enable_Font_Alignment(void);
void Check_Mem_WR_FIFO_Empty(void);
void Text_Mode(void);
void Check_Mem_WR_FIFO_not_Full(void);
void CGROM_Select_Internal_CGROM(void);
void Goto_Text_XY(unsigned short WX,unsigned short HY);
void Select_SFI_Font_Mode(void);
void CGROM_Select_Genitop_FontROM(void);
void Set_GTFont_Decoder(unsigned char temp);
void Select_RA8875_SPI_Mode0_and_Mode3(void);
void Select_SFI_0(void);
void Select_SFI_1(void);
void Select_SFI_2(void);
void Select_SFI_3(void);
void FONT_DMA_Select_Bus_0(void);
void FONT_DMA_Select_Bus_1(void);
//字体相关





void Square_Start_XY(unsigned short WX,unsigned short HY);
void Square_End_XY(unsigned short WX,unsigned short HY);
void Start_Square(void);
void Start_Square_Fill(void);
//方形相关


void Line_Start_XY(unsigned short WX,unsigned short HY);
void Line_End_XY(unsigned short WX,unsigned short HY);
void Start_Line(void);
//线
