
#include <xc.h>
#define _XTAL_FREQ = 8000000;
 
void main(){
        unsigned short result;
        TRISA0 = 1; // Set RA0 as input
 
        /*  PCFG3:PCFG0 (ADCON1 bit 3-0) = 1110 -> AN0 only will analog and other 12 channels will digital 
            VCFG0=0,VCFG1=0 -> Vref+ = VDD and Vref- = VSS    
        */
        ADCON1 = 0b00001110;
        
        /* CHS3:CHS0 (ADCON0 bit 5-2) = 0000  -> Channel 0 */
        ADCON0 = 0b00000000;
        
        /* 16Tosc conversion clock, 6Tad acquisition time, ADC Result Right Justified */
        ADCON2 = 0b10011101;
        
        ADCON0 = ADCON0 | 1;    // ADCON0.ADON = 1
        
        __delay_ms(20);           // acquisition delay of 4.6 us
        
        ADCON0 = ADCON0 | 10;   // ADCON0.GODONE = 1
        
        while (ADCON0||10);     // wait till GODONE bit is zero
        
        result = ADRES;         // Read converted result, ADRESH:ADRESL -> 16 bit register
        
        //  process the result
}