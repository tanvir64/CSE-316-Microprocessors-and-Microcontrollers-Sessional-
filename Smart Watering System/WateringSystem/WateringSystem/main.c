#ifndef F_CPU
#define F_CPU 16000000UL  // 1MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include<stdio.h>
#include<math.h>


int main(void)
{
	DDRD=0xFF;
	DDRC=0xFF;
	DDRB=0xFF;
	ADMUX=0b01100000;//00->external ref. 1->leftleft,00000->ADC0
	ADCSRA=0b10000001;//101->32->division factor
	float voltage=0;
	float step_size=5.0/1024.0;
	uint16_t adc = 0;
	Lcd4_Init();
	PORTB=0x00;
    /* Replace with your application code */
    while (1) 
    {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC)) ;
		adc=(ADCL>>6) | (ADCH<<2);
		voltage=step_size*adc;
		//voltage/=32;
		if(voltage>=2.5) PORTB=0x01;
		if(voltage<2.0) PORTB=0x00;
		char res[4];
		int tem=(int)voltage;
		voltage-=tem;
		voltage*=10;
		char ctem='0'+tem;
		res[0]=ctem;
		
		res[1]='.';
		
		tem=(int)voltage;
		voltage-=tem;
		voltage*=10;
		ctem='0'+tem;
		res[2]=ctem;
		
		tem=(int)voltage;
		ctem='0'+tem;
		res[3]=ctem;
		
		res[4]='\0';
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Voltage: ");
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String(res);
		_delay_ms(500);
		
    }
}

