#include <xc.h>
#include <pic.h>
#include "init.h"
#include "PWMController.h"

extern void initPORTC(void) {
    //TRISC |= 0x20; //TRISC5 = input
    TRISC &= ~0x80; //RC7 is output
}

extern void initISR(void) {

    ;
}

extern void initTMR2(void) {
    T2CON = 0x00; //1:1 postscale
    //Timer2 is off
    //Prescaler is 1
    PR2 = 0x3f; //PWM Frequency = 78.12kHz (Fosc = 20MHz)
}


// Caution!! :input clock is Fosc/4

extern void initPWM(void) {
    CCP1CON = 0x0c; //PWM mode; P1A, P1C active-high; P1B, P1D active-high
    //Single output; P1A modulated; P1B, P1C, P1D assigned as port pins
    setDutyCycle(0x00);
    initTMR2();
    PIR1bits.TMR2IF = 0; //clear interrupt flag
    T2CON |= 0x04; //Timer2 start
    TRISC &= ~0x20; //RC5 is output
    ECCPASbits.ECCPASE = 0; //clear shutdown bit
}

extern void initADC(void) {
    //configure ADC module
    TRISCbits.TRISC0 = 1; //RC0 is input
    ANSEL |= 0x10; //RN4 = Analog input
    ADCON0 = 0x11; //A/D Result Formed is Left justified
    //Voltage Reference is VDD
    //Use Channel 04 (AN4)
    //A/D converter enable
    ADCON1 = 0x20; //ADCS is 32 * Tosc (1.6us)

    //configure AD interrupt
    PIR1bits.ADIF = 0; //clear AD interrupt flag
    PIE1bits.ADIE = 1; //AD innterrupt enable
    INTCON |= 0xc0; //enable PEIE and GIE
}