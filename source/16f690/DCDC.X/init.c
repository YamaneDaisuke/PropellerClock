#include <xc.h>
#include <pic.h>
#include "init.h"

/*
 * Initilize PORT and TRIS registor
 */
extern void initPORT(void)
{
    ANSEL = 0x00;   //All ports are Digital pin
    ANSELH = 0x00;
    PORTA = 0x00;   //clear all port
    PORTB = 0x00;
    PORTC = 0x00;
    TRISA = 0x00;  //clear all port tris ( all port set output pin )
    TRISB = 0x00;
    TRISC = 0x00;
    TRISA |= 0x07; // RA0, RA2 and RA3 set the input pin.
    TRISB |= 0x80; // RB7 set the input pin.
    TRISC |= 0xff; // All port set the input pin.
}