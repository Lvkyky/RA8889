#ifndef		__STRING_H
#define		__STRING_H
#include	"STC15Fxxxx.H"


char* u8_to_str_3(u8 t,char *str);
char* u8_to_str_hex(u8 t,char *str);
char* u8_to_str_4(int t,char *str); 
char* u16_to_str_3(u16 t,char *str);
char* u32_to_str_7(u32 t,char *str);
u32 Str_to_hex(u8 str[9],u8 dian_flag);//×Ö·û×ª»»º¯Êý	
#endif
