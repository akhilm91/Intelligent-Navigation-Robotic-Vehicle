#include <xc.h>
#define _XTAL_FREQ 8000000

void delay1s (void);

void main(void) {
    TRISD=0;
    PORTD=255;
    
    while (1){
        delay1s();
        PORTD=255;
        delay1s();
        PORTD=0;      
    }   
    return;
}


void delay1s (){
    for (int i=0; i<25; i++){
        __delay_ms(20);
    }
    
}