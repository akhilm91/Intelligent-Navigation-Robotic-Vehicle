#include <xc.h>

void main(void) {
    TRISB = 0xFF;
    TRISD = 0x00;
    PORTD = 0x00;
  
    while(1) {
        if(PORTBbits.RB0 == 1) {            
         //LATD = 255;
            LATD = 0xFF;
        } else {
             LATD = 0x00;
        }
    }
    
}