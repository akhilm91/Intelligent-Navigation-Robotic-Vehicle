/*
 * File:   adc_conv.c
 * Author: akhilm
 *
 * Created on 30 November, 2017, 9:26 PM
 */

#include <xc.h>
#include <pic18f4550.h>
#include "config_bits.h"
#define _XTAL_FREQ 8000000

void configureADC (void);
void main()
{
    
    LATAbits.LATA5 = 0x00;
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
                        if (adc > 2){
                            LATAbits.LATA5 = 1;
                        } else {
                            LATAbits.LATA5 = 0;
                        }
    }	
}


void configureADC (void){
    //*************************configure port A for ADC
	TRISAbits.TRISA0 = 0x00;  //port A5 as input
		TRISAbits.TRISA1 = 0x00;  //port A5 as input
			TRISAbits.TRISA2 = 0x00;  //port A5 as input
			
    VCFG1 =0;  // use internal voltage VSS and VDD as reference
    VCFG0 =0;
    
    
    CHS0=0;  //select channel AN0
    CHS1=0;
    CHS2=0;
    CHS3=0;
    
    ADFM=1;  //right justification of result
    
    ACQT0=0; //set AD acquisition time of 16TAD
    ACQT1=1;
    ACQT2=1;
   
    
    ADCS0=0; //select AD clock, FOSC/4  // this is needed for PIC18F87J11
    ADCS1=0;
    ADCS2=1;
 

    ADCON0bits.ADON =1; //turn on ADC
}