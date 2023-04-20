#include "String.h"
#include "Win.h"
#include "api.h"
char* u32_to_str_7(u32 t,char *str)   	//无符号整数转化成字符串,传进来要转换的数以及字符数组。
{
	char c_1;
	char c_2;
	char c_3;
	char c_4;
	char c_5;
	char c_6;
	char c_7;  //最高位

	c_7=t/1000000;	
	c_6=(t%1000000)/100000;
	c_5=(t%100000)/10000;
	c_4=(t%10000)/1000;
	c_3=(t%1000)/100;
	c_2=(t%100)/10;
	c_1=(t%10);

	str[0]=48+c_7;
	str[1]=48+c_6;
	str[2]=48+c_5;
	str[3]='.';
	str[4]=48+c_4;
	str[5]=48+c_3;
	str[6]=48+c_2;
	str[7]=48+c_1;
	str[8]=0;
	return str;
}




char* u16_to_str_3(u16 t,char *str)   	//u16转化成字符串,传进来要转换的数以及字符数组。
{
	char bai;
	char shi;
	char ge;

	bai=t/100;	
	shi=(t%100)/10;
	ge=t%10;

	str[0]=48+bai;
	str[1]=48+shi;
	str[2]=48+ge;
	str[3]=0;
		
	return str;
}



char* u8_to_str_3(u8 t,char *str)   	//u8转化成字符串,传进来要转换的数以及字符数组。
{
	char bai;
	char shi;
	char ge;

	bai=t/100;	
	shi=(t%100)/10;
	ge=t%10;

	str[0]=48+bai;
	str[1]=48+shi;
	str[2]=48+ge;
	str[3]=0;
		
	return str;
	}


	char* u8_to_str_4(int t,char *str)   	//u8转化成字符串,传进来要转换的数以及字符数组。
	{
	char qian;
	char bai;
	char shi;
	char ge;

	qian=t/1000;
	bai=(t%1000)/100;	
	shi=(t%100)/10;
	ge=t%10;

	str[0]=48+qian;
	str[1]=48+bai;
	str[2]=48+shi;
	str[3]=48+ge;
	str[4]=0;
		
	return str;
}


char* u8_to_str_hex(u8 t,char *str)   	//u8转化成字符串,传进来要转换的数以及字符数组。
{
	char high;
	char low;
	high=t/16;
	if(high<10)	
	{
		str[0]=48+high;
	}
	else
	{
		switch(high)
		 {
			case 10: 
			 { 
					str[0]='A';		 
					break;
			 }    
					 
			case 11: 
			 {
					str[0]='B';																										 
					break;
			 }
					 
			case 12: 
			 {
					str[0]='C';																													 
					break;
			 }
				 
			case 13: 
			 {
					str[0]='D';																													 
					break;
			 }
			case 14: 
			 {
					str[0]='E';																													 
					break;
			 }
			case 15: 
			 {
					str[0]='F';																													 
					break;
			 }
			default:
			{ 
						 
			break;
			}
		}
		}

	low=t%16;
	if(low<10)	
	{
	str[1]=48+low;
	}
	else
	{
	switch(low)
		 {
				case 10: 
				 { 	
						str[1]='A';		 
						break;
				 }    
						 
				case 11: 
				 {
						str[1]='B';																										 
						break;
				 }
				 
				case 12: 
				 {
						str[1]='C';																													 
						break;
				 }
						 
				case 13: 
				 {
						str[1]='D';																													 
						break;
				 }
				case 14: 
				 {
					  str[1]='E';																													 
					  break;
				 }
				case 15: 
				 {
					 str[1]='F';																													 
					 break;
				 }
				default:
				{ 
							 
				  break;
				}
		}

		}
	str[2]=0; //结束符
	return str;
}








