#ifndef		__SPI_H
#define		__SPI_H


//stm32---->51单片机spi接口移植，引脚定义宏。
/**********************************************************/
#define Set_SPI3_SCL P05=1  
#define Set_SPI3_SDO P06=1
#define Set_SPI3_ZCS P07=1

#define Reset_SPI3_SCL P05=0
#define Reset_SPI3_SDO P06=0
#define Reset_SPI3_ZCS P07=0

#define Read_SPI3_SDO  P06


#define GPIO_SetBits(GPIOE, GPIO_Pin_1 ) P40=1;
#define	GPIO_ResetBits(GPIOE, GPIO_Pin_1) P40=0;
/*********************************************************/


//芯片读写底层接口
/**********************************************************/
void SPI3_Init(void);
void SPI3_Write(unsigned char dat);
unsigned char SPI3_Read();
void LCD_CmdWrite(unsigned char Command);
unsigned char LCD_DataRead(void);  
void LCD_DataWrite(unsigned char Data); 
unsigned char LCD_StatusRead(void);	
/*********************************************************/



#endif
