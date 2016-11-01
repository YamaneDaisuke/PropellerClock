/* 
 * File:   init.h
 * Author: Yamane
 *
 * Created on 2016/11/01, 15:02
 */

#ifndef INIT_H
#define	INIT_H
#include "PWMController.h"
#ifdef	__cplusplus
extern "C" {
#endif

    extern void initPWM(void);
    extern void initTMR2(void);
    extern void initISR(void);
    extern void initPORTC(void);
    extern void initADC(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

