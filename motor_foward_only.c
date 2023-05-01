#include <xc.h>
#include <pic18f4550.h>
#include "config_bits.h"
#define _XTAL_FREQ 8000000
void motor_forward (void);

void main(void) {
    TRISD	= 0;	//set PORTD as Output PORT
	PORTD	= 0;	//set PORTD value to 0
	while (1){
		motor_forward();
	}
	return;
}
void motor_forward (void){
	for(int f=0; f<10; f++)
    PORTD = 0b10001000;
    delay1ms();
    PORTD = 0b01000100;
    delay1ms();
    PORTD = 0b00100010;
    delay1ms();
    PORTD = 0b00010001;
    delay1ms();
	}
}

void delay1ms()
{
    for (int i=0;i<4;i++)
    {
        __delay_ms(0.25);
    }
}


