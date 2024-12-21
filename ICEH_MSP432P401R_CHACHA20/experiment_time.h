#ifndef EXPERIMENT_TIME_H_
#define EXPERIMENT_TIME_H_

unsigned long long ticks = 0;
unsigned long long elapsed = 0;

void SysTick_Handler(void) {
    ticks++;
}

#define startTimer() MAP_SysTick_setPeriod(1200);    /* 0.1ms resolution */ \
                     MAP_SysTick_enableInterrupt();                       \
                     /* Enabling MASTER interrupts */                     \
                     MAP_Interrupt_enableMaster();                        \
                     MAP_SysTick_enableModule();   /* Start timer */      \
                     GPIO_setOutputHighOnPin(LED1_PORT,RED_LED1_PIN);     \
                     unsigned int start = ticks;

#define getElapsedTime() (ticks - start);                   \
        MAP_SysTick_disableModule();                        \
        GPIO_setOutputLowOnPin(LED1_PORT,RED_LED1_PIN);

#endif /* EXPERIMENT_TIME_H_ */
