/*
 * Author: Rohit Sathye and Rohit Mehta
 * Course : CS6024 - Intermittent Computing and Energy Harvesting
*******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#define RED_LED1_PIN GPIO_PIN0
#define LED1_PORT GPIO_PORT_P2

static uint32_t LED_state_G;

void LED_FLASH_Init(void);
void TIMER32_Init(void);
void LED_FLASH_Change_State(void);
void DELAY_LOOP_Wait(const unsigned int);

int main(void)
{
    /* Stop Watchdog  */
    //MAP_WDT_A_holdTimer();

    //LED_FLASH_Init();
    //TIMER32_Init();

    while(1)
    {
        //LED_FLASH_Change_State();
        //DELAY_LOOP_Wait(21);    //1 SECOND DELAY
    }
}

void LED_FLASH_Init(void){
    GPIO_setAsOutputPin(LED1_PORT,RED_LED1_PIN);
    LED_state_G = 0;
}

void TIMER32_Init(void){
    TIMER32_1->LOAD = 15000-1;   //50ms Delay    //3000000 / 15000 = 50
    TIMER32_1->CONTROL = 0xC2;
}

void LED_FLASH_Change_State(void){

    if(LED_state_G == 1){
        LED_state_G = 0;
        GPIO_setOutputLowOnPin(LED1_PORT,RED_LED1_PIN);
    }
    else{

        LED_state_G = 1;
        GPIO_setOutputHighOnPin(LED1_PORT,RED_LED1_PIN);
        while(1);

        
    }
}

void DELAY_LOOP_Wait(const unsigned int DELAY){
    uint32_t x;
    for (x=0;x <= DELAY;x++){
        while((TIMER32_1->RIS & 1)== 0);    //RAW_IFG flag is set - waiting for it
        TIMER32_1->INTCLR = 0;
    }
}
