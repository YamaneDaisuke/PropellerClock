
// MY HEADER
#include "PWMController.h"

extern bool setDutyCycle(unsigned char duty) {
    /*if(duty > 0x7F){
        return false;
    }*/
    unsigned char duty1 = CCP1CON & ~0x30; //clear duty cycle
    unsigned char duty2 = duty >> 2;
    duty1 |= (duty & 0x03) << 4;
    CCP1CON = duty1;
    CCPR1L = duty2;
    return true;
}

extern unsigned char makeDutyCycle_2sj334(unsigned char duty) {
    if (duty == 0x00) {
        return 0;
    }
    if (duty <= 0x02) {
        return 1;
    }
    return duty - 2;
}