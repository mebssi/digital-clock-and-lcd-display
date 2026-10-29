#include<reg51.h>
#define LCD P2
sbit RS = P1^0;
sbit E = P1^1;
void delay(unsigned int ms)
{ unsigned int i,j;
for(i=0;i<ms;i++)
{ for(j=0;j<120;j++)
{
}}
}
void lcd_cmd(unsigned char cmd)
{
LCD=cmd;
RS=0;
E=1;
delay(1);
E=0;
delay(1);
}
void lcd_data(unsigned char dat)
{ LCD=dat;
RS=1;
E=1;
delay(1);
E=0;
delay(1);
}
void lcd_init()
{ lcd_cmd(0x38);
delay(1);
lcd_cmd(0x01); //clear display screen 
delay(1);
lcd_cmd(0x0C); 
// delay(1);
lcd_cmd(0x80); // force cursor to begin from first 
}
void lcd_string(unsigned char *str)
{ while(*str!='\0')
{
lcd_data(*str);
str+=1;
} }
void main()
{ lcd_init();
lcd_data('2');
lcd_data('0');
lcd_data('1');
lcd_data('9');
lcd_data();
lcd_data('E');
lcd_data('t');
lcd_data('h');
lcd_data('i');
lcd_data('o');
lcd_data('p');
lcd_data('i');
lcd_data('a');
lcd_data('n');
lcd_data();
lcd_data('Y');
lcd_data('e');
lcd_data('a');
lcd_data('r');
while(1)
{ lcd_cmd(0x1C); // display right 
delay(1000);
} }