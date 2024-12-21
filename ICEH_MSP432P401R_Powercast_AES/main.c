#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "msp.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#include "driverlib.h"

#include "input.h"

#define AES_BLOCK_SIZE_BITS 128
#define AES_BLOCK_SIZE_BYTES (AES_BLOCK_SIZE_BITS/8)

#define board_init() WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD

#define GREEN_LED_PIN GPIO_PIN1   //P2.1
#define GREEN_LED_PORT GPIO_PORT_P2

#define RED_LED_PIN GPIO_PIN0     //P1.0
#define RED_LED_PORT GPIO_PORT_P1

#define BUTTON1_PIN GPIO_PIN1    //P1.1
#define BUTTON1_PORT GPIO_PORT_P1

#define SWITCH_NOT_PRESSED (0)
#define SWITCH_PRESSED (1)

//#include "experiment_time.h"

#define UART

#include "tiny_aes/aes.h"

//#define CALIBRATION_START 0x0003F000
#define CALIBRATION_START 0x0001F000

#define FLASH_BANK FLASH_MAIN_MEMORY_SPACE_BANK0
#define FLASH_SECTOR FLASH_SECTOR31

/** Globals (test inputs) **/
uint8_t key[] = {KEY};
uint8_t expected_pt[] = {PT};
uint8_t expected_ct[] = {CT};

uint8_t aesCount[1] = {0};
char buf[20];

static volatile uint16_t curADCResult;
static volatile float normalizedADCRes;

uint8_t pt[] = {PT};
uint8_t ct[] = {CT};

/** contexts **/
struct AES_ctx ctx;

long keysize = 256;

int Sw_state = 0;

/** Call initialization functions for AES implementations **/
void init_aes()
{
    AES_init_ctx(&ctx, key);
}

void LED_Init(void){
    GPIO_setAsOutputPin(RED_LED_PORT,RED_LED_PIN);
    GPIO_setAsOutputPin(GREEN_LED_PORT,GREEN_LED_PIN);
}

void Button1_Init(void){
    //pull up employed
    GPIO_setAsInputPinWithPullUpResistor(BUTTON1_PORT,BUTTON1_PIN);
}

uint8_t Button1_Get_Input(){

    uint8_t Return_value = SWITCH_NOT_PRESSED;

    if(!(GPIO_getInputPinValue(BUTTON1_PORT,BUTTON1_PIN))){
           Return_value = SWITCH_PRESSED;
       }
    return Return_value;
}

void test_encrypt()
{
    /** tiny AES **/
    AES_encrypt(&ctx, key, pt);
}

void ADC_init(void) {

    // Initialize ADC module
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    // Configure ADC GPIO pin
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);

    // Configure ADC memory buffer
    MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A0, false);

    /* Configuring Sample Timer */
    MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

}

void FPU_init(void){

    MAP_FPU_enableModule();
    MAP_FPU_enableLazyStacking();
}

void Checkpoint(void){

    MAP_FlashCtl_unprotectSector(FLASH_BANK, FLASH_SECTOR);

    MAP_FlashCtl_eraseSector(CALIBRATION_START);

    MAP_FlashCtl_programMemory(aesCount,(void*) CALIBRATION_START, sizeof(uint8_t));

    MAP_FlashCtl_protectSector(FLASH_BANK, FLASH_SECTOR);

}

int main(void) {

    board_init();

    LED_Init();

    init_aes();

    uint8_t value = 0;
    uint8_t flashed = 0;

    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    FPU_init();

    ADC_init();

    //Read from Flash
    value = *((uint8_t *)CALIBRATION_START);

    while(1){

     /* Enabling/Toggling Conversion */
     MAP_ADC14_enableConversion();
     MAP_ADC14_toggleConversionTrigger();

     while (MAP_ADC14_isBusy());

     /* Read ADC result */
     curADCResult = MAP_ADC14_getResult(ADC_MEM0);
     normalizedADCRes = (curADCResult * 3.3) / 16384;

     while(value <= 250){

     GPIO_setOutputHighOnPin(RED_LED_PORT,RED_LED_PIN);

     test_encrypt();

     GPIO_setOutputLowOnPin(RED_LED_PORT,RED_LED_PIN);

     ++value;

     if (value == 250){
         break;
     }

     if  ((normalizedADCRes > 1.6) && (flashed == 0)){

         flashed = 1;
         memset(aesCount, value, sizeof(uint8_t));
         GPIO_setOutputHighOnPin(GREEN_LED_PORT,GREEN_LED_PIN);
         Checkpoint();
         GPIO_setOutputLowOnPin(GREEN_LED_PORT,GREEN_LED_PIN);
     }
   }

     GPIO_setOutputLowOnPin(RED_LED_PORT,RED_LED_PIN);

     Sw_state = Button1_Get_Input();

     if (Sw_state == SWITCH_PRESSED){

     value = 0;

     }
   }
}

