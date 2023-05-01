/*
 * File:   fwd.c
 * Author: akhilm
 *
 * Created on 15 January, 2018, 7:42 PM
 */
#include <xc.h>
#include <pic18f4550.h>
#include "config_bits.h"
#define _XTAL_FREQ 8000000

void motor_forward(void);
void rm_forward(void);
void forward(void);
void delay1ms();
void reverse(void);
void turnright180(void);
void turnleft180(void);
void turnright90(void);
void turnleft90(void);
void motor_stop(void);
void configureADC_sensor();
float read_sensor_f();
float read_sensor_r();
float read_sensor_l();
int detect_sensor_f();
int detect_sensor_r();
int detect_sensor_l();
int at_black = 0;
int count = 1;
void led_buzzer();
void Seven_Segment(int);

void main(void) {
    int dir=0;
    configureADC_sensor();
    motor_stop();
    TRISD = 0; //set PORTD as Output PORT
    PORTD = 0; //set PORTD value to 0
    TRISAbits.TRISA3 = 1;   //set PORTA3 as input for optical sensor
    //PORTAbits.PORTA3 = 0;   //set PORTA3 value to 0
    
    while (1) {
    // 1. detect black stripe
    // 2. if it is forward, if dir==0
    // 3. count up

    // 4. if it is reverse, if dir==1
    // 5. count down
        
        if (PORTAbits.RA3 == 1){
            Seven_Segment(count);
            led_buzzer();
            if((dir == 0) && (at_black == 0)){
               count++;
                }   
            else if ((dir == 1) && (at_black == 0)){
                count--;
                }
            at_black = 1;
            }
        else{
            at_black = 0;
        }
            
       if(detect_sensor_f()==1){
            if((detect_sensor_r()==0) && (detect_sensor_l()==0)) {
                turnright180();
                dir=1;
            }

            else if((detect_sensor_r()==1) && (detect_sensor_l()==0)) {
                turnleft90();
            }

            else if((detect_sensor_r()==0) && (detect_sensor_l()==1)) {
                turnright90();
            }

            else if((detect_sensor_r()==1) && (detect_sensor_l()==1)) {
                turnright180();
                dir=1;
            }
       }
       else
           forward();
       
    } 
}

int detect_sensor_f(){
    float sensor_f;
    
    for(int i=0;i<3;i++){
        sensor_f += read_sensor_f();
         __delay_ms(1);
    }
    sensor_f /= 3;
    
    if (sensor_f > 1.7)
        return 1;  //obstacle detected
    else
        return 0;  //nothing
}

int detect_sensor_r(){
    float sensor_r;
    for(int i=0;i<10;i++){
        sensor_r += read_sensor_r();
         __delay_ms(1);
    }
    sensor_r /= 10;
    
    if (sensor_r > 1.7)
        return 1;  //obstacle detected
    else
        return 0;  //no obstacles
}

int detect_sensor_l(){
    float sensor_l;
    for(int i=0;i<10;i++){
        sensor_l += read_sensor_l();
        __delay_ms(1);
    }
    sensor_l /= 10;
    
    if (sensor_l > 1.7)
        return 1;  //obstacle detected
    else
        return 0;  //nothing
}
void delaym1s (){
    for (int i=0; i<4; i++){
        __delay_ms(.25);
    }
    
}

void turnleft180(void) {
    //Both Motor Reverse
    for (int y = 0; y < 720; y++) {  //default is 200
        PORTD = 0b00010001;
        __delay_ms(0.3);
        PORTD = 0b00110011;
        __delay_ms(0.3);
        PORTD = 0b00100010;
        __delay_ms(0.3);
        PORTD = 0b01100110;
        __delay_ms(0.3);
        PORTD = 0b01000100;
        __delay_ms(0.3);
        PORTD = 0b11001100;
        __delay_ms(0.3);
        PORTD = 0b10001000;
        __delay_ms(0.3);
        PORTD = 0b10011001;
        __delay_ms(0.3);
    }
}

void turnright180(void) {
    //Both Motor Reverse
    for (int y = 0; y < 720; y++) {
        PORTD = 0b10011001;
        __delay_ms(0.3);
        PORTD = 0b10001000;
        __delay_ms(0.3);
        PORTD = 0b11001100;
        __delay_ms(0.3);
        PORTD = 0b01000100;
        __delay_ms(0.3);
        PORTD = 0b01100110;
        __delay_ms(0.3);
        PORTD = 0b00100010;
        __delay_ms(0.3);
        PORTD = 0b00110011;
        __delay_ms(0.3);
        PORTD = 0b00010001;
        __delay_ms(0.3);
    }
}

void forward(void) {
    for (int y = 0; y < 50; y++) { //original is 510
        PORTD = 0b00011001;
        __delay_ms(0.3);
        PORTD = 0b00111000;
        __delay_ms(0.3);
        PORTD = 0b00101100;
        __delay_ms(0.3);
        PORTD = 0b01100100;
        __delay_ms(0.3);
        PORTD = 0b01000110;
        __delay_ms(0.3);
        PORTD = 0b11000010;
        __delay_ms(0.3);
        PORTD = 0b10000011;
        __delay_ms(0.3);
        PORTD = 0b10010001;
        __delay_ms(0.3);
    }
}

void reverse(void) {
    for (int y = 0; y < 510; y++) {
        PORTD = 0b10010001;
        __delay_ms(0.3);
        PORTD = 0b10000011;
        __delay_ms(0.3);
        PORTD = 0b11000010;
        __delay_ms(0.3);
        PORTD = 0b01000110;
        __delay_ms(0.3);
        PORTD = 0b01100100;
        __delay_ms(0.3);
        PORTD = 0b00101100;
        __delay_ms(0.3);
        PORTD = 0b00111000;
        __delay_ms(0.3);
        PORTD = 0b00011001;
        __delay_ms(0.3);
    }
}

void turnleft90(void) {
    //Both Motor Reverse
    for (int y = 0; y < 360; y++) {  //default is 200
        PORTD = 0b00010001;
        __delay_ms(0.3);
        PORTD = 0b00110011;
        __delay_ms(0.3);
        PORTD = 0b00100010;
        __delay_ms(0.3);
        PORTD = 0b01100110;
        __delay_ms(0.3);
        PORTD = 0b01000100;
        __delay_ms(0.3);
        PORTD = 0b11001100;
        __delay_ms(0.3);
        PORTD = 0b10001000;
        __delay_ms(0.3);
        PORTD = 0b10011001;
        __delay_ms(0.3);
    }
}

void turnright90(void) {
    //Both Motor Reverse
    for (int y = 0; y < 360; y++) {
        PORTD = 0b10011001;
        __delay_ms(0.3);
        PORTD = 0b10001000;
        __delay_ms(0.3);
        PORTD = 0b11001100;
        __delay_ms(0.3);
        PORTD = 0b01000100;
        __delay_ms(0.3);
        PORTD = 0b01100110;
        __delay_ms(0.3);
        PORTD = 0b00100010;
        __delay_ms(0.3);
        PORTD = 0b00110011;
        __delay_ms(0.3);
        PORTD = 0b00010001;
        __delay_ms(0.3);
    }
}

void motor_stop(void) {
    PORTD = 0x00;
}

void led_buzzer(){
        __delay_ms (1);
        LATAbits.LATA4 = 1;	//beep buzzer
        LATAbits.LATA5 = 1;	//on LED
        __delay_ms (100);
        LATAbits.LATA4 = 0;	//off buzzer  
        LATAbits.LATA5 = 0; //off LED
        __delay_ms (1);
}

void Seven_Segment(int x)
{	
    int arra[10] = {0xfd,0x60,0xde,0xfa,0x63,0xbb,0xbf,0xf0,0xff,0xfb}; // Counting from 0 to 9
	PORTB = arra[x];			
}

float read_sensor_f(){
    ADCON0bits.CHS0 = 0; //select channel AN0
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    float sensor_f = 0.0;
    ADCON0bits.GO_DONE = 1; // Start Conversion               
    while (ADCON0bits.GO_DONE == 1) {
        // wait
    }
    sensor_f = ADRESH * 256 + ADRESL; //ADRESL = lower bits   //ADRESH = higher bits
    sensor_f = sensor_f * 0.00488;
   
    return sensor_f;
}

float read_sensor_r(){
    ADCON0bits.CHS0 = 1; //select channel AN0
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    float sensor_r = 0.0;
    ADCON0bits.GO_DONE = 1; // Start Conversion               
    while (ADCON0bits.GO_DONE == 1) {
        // wait
    }
    sensor_r = ADRESH * 256 + ADRESL; //ADRESL = lower bits   //ADRESH = higher bits
    sensor_r = sensor_r * 0.00488;
   
    return sensor_r;
}

float read_sensor_l(){
    ADCON0bits.CHS0 = 0; //select channel AN0
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    float sensor_l = 0.0;
    ADCON0bits.GO_DONE = 1; // Start Conversion               
    while (ADCON0bits.GO_DONE == 1) {
        // wait
    }
    sensor_l = ADRESH * 256 + ADRESL; //ADRESL = lower bits   //ADRESH = higher bits
    sensor_l = sensor_l * 0.00488;
   
    return sensor_l;
}

void configureADC_sensor(void) {
    //*************************configure port A for ADC
    TRISAbits.TRISA0 = 1; //port A0 as input
    TRISAbits.TRISA1 = 1; //port A1 as input
    TRISAbits.TRISA2 = 1; //port A2 as input
    ADCON1bits.VCFG1 = 0; // use internal voltage VSS and VDD as reference
    ADCON1bits.VCFG0 = 0;

    ADCON2bits.ADFM = 1; //right justification of result

    ADCON2bits.ACQT0 = 0; //set AD acquisition time of 16TAD
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT2 = 1;


    ADCON2bits.ADCS0 = 0; //select AD clock, FOSC/4  // this is needed for PIC18F87J11
    ADCON2bits.ADCS1 = 0;
    ADCON2bits.ADCS2 = 1;


    ADCON0bits.ADON = 1; //turn on ADC
}
