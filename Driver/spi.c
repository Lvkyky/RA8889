#include <config.h>
#include <gpio.h>
#include "delay.h"
#include  <spi.h>
#include  <USART.h>



void SPI3_Init(void)//三条线同时拉高
{
	
GPIO_InitTypeDef  IOP05;                 //scl
GPIO_InitTypeDef  IOP06;                // da
GPIO_InitTypeDef  IOP07;                // cs
GPIO_InitTypeDef  IOP40;                //reset
  
IOP05.	Pin=GPIO_Pin_2;
IOP05.	Mode=GPIO_OUT_PP;

IOP06.	Pin=GPIO_Pin_3;	
IOP06.	Mode=GPIO_OUT_PP;
	
IOP07.	Pin=GPIO_Pin_5;
IOP07.	Mode=GPIO_OUT_PP;   //开始的时候都是推免，等到要输入数据时候，在配置IOp2。
	
IOP40.	Pin=GPIO_Pin_0;
IOP40.	Mode=GPIO_OUT_PP;   // //设置p40为复用推挽输出
	

GPIO_Inilize(GPIO_P0,&IOP05);	
GPIO_Inilize(GPIO_P0,&IOP06);	
GPIO_Inilize(GPIO_P0,&IOP07);	                  
GPIO_Inilize(GPIO_P4,&IOP40);	

	
Set_SPI3_SCL;  
Set_SPI3_SDO; 
Set_SPI3_ZCS;  //置于空闲态
}




void SPI3_Write(unsigned char dat)//spi写8位数据的时序模拟
{
	unsigned char t = 8;

	do
	{
	  if  ((dat & 0x80)==0x80) //先送上数据信号
		{
	    Set_SPI3_SDO;		   
		}
		else
	  {
		  Reset_SPI3_SDO;	
		}

		dat <<= 1;//准备下一位数据
		
		Reset_SPI3_SCL;// 时钟拉低
		Set_SPI3_SCL;//	  时钟拉高完成数据写入  
	}while(--t !=0);
	
	Set_SPI3_SCL;		   
	Set_SPI3_SDO;// 再次将信号线置于空闲态
}





void  delay_spi(void)
{
	short int i;
	i = 2;
	while(--i)	;   //14T per loop 
}


unsigned char SPI3_Read()//spi读8位时序模拟
{
	unsigned char temp =0;
	unsigned char dat=0;//读取缓存
	unsigned char t = 8;//要读的字符个数

	do
	{
		Reset_SPI3_SCL;//拉低时钟
		//SPI3_Delay();
		delay_spi();

		temp=Read_SPI3_SDO;//读取数据
		dat <<= 1;
		delay_spi();//SPI3_Delay();
		if(temp==0x01)
		{
	    dat++;
	  }
	  Set_SPI3_SCL;//拉高时钟
		  
	}while(--t !=0 );

	return dat;
}





void LCD_CmdWrite(unsigned char Command)//写命令函数
{	
	unsigned char cmd=Command;
	Set_SPI3_SCL;//			   //SCL 时钟拉为空闲态
	Set_SPI3_SDO;			   //SDO   数据线拉为空闲
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);			       //ZCS            //片选液晶控制芯片
	SPI3_Write(0x00); //发送第一字节（写，命令）
	SPI3_Write(cmd);  //发送第二字节
	Set_SPI3_ZCS;//GPIO_SetBits(GPIOE, GPIO_Pin_7);			       //ZCS	             //释放液晶控制芯片
}




unsigned char LCD_DataRead(void)  //读数据函数
{	     
  unsigned int Data;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	Set_SPI3_SCL;//GPIO_SetBits(GPIOE, GPIO_Pin_10);				  
	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);				       
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);			      
	SPI3_Write(0xc0);//置总线为空闲态，并且发送第一字节（读数据命令）


	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);     //先写1;
	

	GPIO_InitStructure.Mode= GPIO_HighZ ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //数据线
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	 //设置成浮空输入

	
	
	Data = SPI3_Read();                //读数据


  GPIO_InitStructure.Mode= GPIO_OUT_PP ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //数据线
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	     //设置成推免输出
	
	
	Set_SPI3_ZCS;      //GPIO_SetBits(GPIOE, GPIO_Pin_7);	    释放芯片
                                                  

	return Data;
}





void LCD_DataWrite(unsigned char Data) //写数据函数
{   
  unsigned int writedata;

	Set_SPI3_SCL;//GPIO_SetBits(GPIOE, GPIO_Pin_10);				   
	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);				  
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);			 //spi置于空闲态，并且片选上芯片。   

	SPI3_Write(0x80); 
	SPI3_Write(Data);
	Set_SPI3_ZCS;//	GPIO_SetBits(GPIOE, GPIO_Pin_7);			 	 //释放芯片
}




unsigned char LCD_StatusRead(void)						
{
	unsigned char Data=0;
  GPIO_InitTypeDef GPIO_InitStructure;

	Set_SPI3_SCL;//GPIO_SetBits(GPIOE, GPIO_Pin_10);				
	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);				 
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);		  //选中芯片	 

	
	SPI3_Write(0x40);        //置总线为空闲态，并且发送第一字节（读状态命令）
	
	
	/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8  ;
															 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	  
	Data = SPI3_Read();

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //推挽输出
	GPIO_Init(GPIOE, &GPIO_InitStructure);
*/


	GPIO_InitStructure.Mode=GPIO_HighZ ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //数据线
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	     //设置成浮空输入
	
	
 
	Data = SPI3_Read();                //读数据

	
  GPIO_InitStructure.Mode= GPIO_OUT_PP ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //数据线
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	     //设置成推免输出


	Set_SPI3_ZCS;	//GPIO_SetBits(GPIOE, GPIO_Pin_7);			      //释放芯片  	.
	
	return Data;
}





