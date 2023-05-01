#include <xc.h>
#include <pic18f4550.h>
#include "config_bits.h"
#define _XTAL_FREQ 8000000

void beep_once (void);

void main(void) {
    TRISAbits.TRISA4	= 0;
    LATAbits.LATA4		= 0;
	TRISAbits.TRISA5	= 0;
    LATAbits.LATA5		= 0;
	
    
	int x = 1;
	
    if(x == 1){
        delay20ms ()();
        LATAbits.LATA4 = 1;	//beep buzzer
        LATAbits.LATA5 = 1;	//on LED
        delay100ms();
        LATAbits.LATA4 = 0;	//off buzzer  
        LATAbits.LATA5 = 0; //off LED
    }   
    return;
}

void delay1s (){
    for (int i=0; i<50; i++){
        __delay_ms(20);

void delay100ms (){
    for (int i=0; i<5; i++){
        __delay_ms(20);
    }
void delay20ms (){
    for (int i=0; i<1; i++){
        __delay_ms(20);
    }
    
}