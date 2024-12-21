/*
 * experiment_time.h
 *
 *  Created on: May 24, 2023
 *      Author: rohit
 */

#ifndef EXPERIMENT_TIME_H_
#define EXPERIMENT_TIME_H_

#define startTimer() MAP_SysTick_setPeriod(30030);    /* 10ms resolution */
                     MAP_SysTick_enableInterrupt();
                     /* Enabling MASTER interrupts */
                     MAP_Interrupt_enableMaster();
                     MAP_SysTick_enableModule();   /* Start timer */

#define getElapsedTime() (ticks - start);     \
        MAP_SysTick_disableModule();         \
        GPIO_setOutputLowOnPin(LED1_PORT,RED_LED1_PIN);  /*SetOutput Low*/

#endif /* EXPERIMENT_TIME_H_ */
