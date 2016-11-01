/*
 * File:   main.c
 * Author: Yamane
 *
 * Created on 2016/10/28, 16:33
 */


#include <pic.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// MY HEADER
#include "init.h"
#include "PWMController.h"

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#define _XTAL_FREQ 20000000
static void interrupt isr(void);

extern void startADC(void);

static char flip = 0;
short Vcom = 255;
short Vref = 0;
short Van = 0;

void main(void) {
    //initPORT();
    unsigned char tmp = 0x7f;

    initPWM();
    initADC();
    initPORTC();
    startADC();
    while (1) {
        //setDutyCycle(makeDutyCycle_2sj334(tmp));
        Vref = tmp;
        tmp--;
        if (tmp <= 0x00) {
            tmp = 0xff;
        }
        __delay_ms(1);
    }
    return;
}

static void interrupt isr(void) {

    if (PIR1bits.ADIF) {
        Van = ADRESH;
        Vcom -= (Vref - Van) >> 2;
        if (Vcom <= 0) {
            Vcom = 0;
        }
        if (Vcom >= 0xff) {
            Vcom = 0xff;
        }
        PIR1bits.ADIF = 0; //clear interrupt flag
        startADC(); //ADC start
        setDutyCycle(Vcom & 0x00FF);
        //flip = !flip;
        //PORTCbits.RC7 = flip;
        //PORTCbits.RC7 = (tmp & 0x80)?1:0;
    }

}

extern void startADC(void) {
    ADCON0bits.GO = 1;
}

