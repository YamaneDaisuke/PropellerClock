/* 
 * File:   PWMController.h
 * Author: Yamane
 *
 * Created on 2016/11/01, 18:55
 */

#ifndef PWMCONTROLLER_H
#define	PWMCONTROLLER_H
#include <pic.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    extern bool setDutyCycle(unsigned char);
    extern unsigned char makeDutyCycle_2sj334(unsigned char);

#ifdef	__cplusplus
}
#endif

#endif	/* PWMCONTROLLER_H */

