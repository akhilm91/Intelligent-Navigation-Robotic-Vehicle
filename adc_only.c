
#include <xc.h>
#define _XTAL_FREQ 8000000


#include "config.h"
#include <pic18f87j11.h>

void configureADC (void);

void main()
{
    
    PORTAbits.PORTA5 = 0x00;
    TRISAbits.TRISA5 = 0x00;
    
    
    configureADC();
   
    /*
     * Next part below starts the AD conversion process on channel AN0,
     * waits for conversion to finish
     * calculates the actual analog voltage,
     * displays it on a LCD for verification
   */
 while(1) {              
                        __delay_ms(20);
                        float adc = 0.0;
                        ADCON0bits.GO_DONE = 1; // Start Conversion               
                        while (ADCON0bits.GO_DONE == 1){ 
                                    // wait
                        }                               
                        adc = ADRESH*256 + ADRESL; //ADRESL = lower bits   //ADRESH = higher bits
                        adc = adc*0.00488;
                        if (adc > 3){
                            LATB = 0xFF;
                        } else {
                            LATB = 0x00;
                        }
    }	
}


void configureADC (void){
    //*************************configure port A for ADC
    TRISA=0xFF;  //port A as input
    ADCON0bits.VCFG1 =0;  // use internal voltage VSS and VDD as reference
    ADCON0bits.VCFG0 =0;
    
    
    ADCON0bits.CHS0=0;  //select channel AN0
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS3=0;
    
    ADCON1bits.ADFM=1;  //right justification of result
    
    ADCON1bits.ACQT0=0; //set AD acquisition time of 16TAD
    ADCON1bits.ACQT1=1;
    ADCON1bits.ACQT2=1;
   
    
    ADCON1bits.ADCS0=0; //select AD clock, FOSC/4  // this is needed for PIC18F87J11
    ADCON1bits.ADCS1=0;
    ADCON1bits.ADCS2=1;
 

    ADCON0bits.ADON =1; //turn on ADC
}


