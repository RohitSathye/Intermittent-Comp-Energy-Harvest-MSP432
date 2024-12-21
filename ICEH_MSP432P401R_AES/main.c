#include <stdint.h>
#include <string.h>

#include "msp.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#include "driverlib.h"

#include "input.h"

#define AES_BLOCK_SIZE_BITS 128
#define AES_BLOCK_SIZE_BYTES (AES_BLOCK_SIZE_BITS/8)

#define board_init() WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD

#define RED_LED1_PIN GPIO_PIN0
#define LED1_PORT GPIO_PORT_P2

#include "experiment_time.h"

#define UART

#include "tiny_aes/aes.h"

/** Globals (test inputs) **/
uint8_t key[] = {KEY};
uint8_t expected_pt[] = {PT};
uint8_t expected_ct[] = {CT};

uint8_t pt[] = {PT};
uint8_t ct[] = {CT};

/** contexts **/
struct AES_ctx ctx;

long keysize = 256;

/** Call initialization functions for AES implementations **/
void init_aes()
{
    AES_init_ctx(&ctx, key);
}

void LED_FLASH_Init(void){
    GPIO_setAsOutputPin(LED1_PORT,RED_LED1_PIN);
}

void test_encrypt()
{
    /** tiny AES **/
    AES_encrypt(&ctx, key, pt);
}

void test_decrypt()
{
    /** tiny AES **/
    AES_decrypt(&ctx, key, ct, pt);
}

/*******************************
// * Function to verify encryption
// ******************************/
int check_encrypt() {
    return memcmp((char*) expected_ct, (char*) ct, sizeof(expected_ct));
}

///******************************
// * Function to verify decryption
// *******************************/
int check_decrypt() {
     return memcmp((char*) expected_pt, (char*) pt, sizeof(expected_pt));
}

      /*  Function to send a character through UART*/
void UART0_putchar(char c) {
          MAP_UART_transmitData(EUSCI_A0_BASE, c);              /* send a char */

          while(UART_queryStatusFlags(EUSCI_A0_BASE, EUSCI_A_UART_BUSY));  /* wait for transmit buffer empty */
      }

      /*  Function to send a string through UART by sending each character in the string. */
void UART0_puts(char* s) {
          while (*s != 0)             /* if not end of string */
          UART0_putchar(*s++);        /* send the character through UART0 */
      }

void uart_init(void)
      {
          const eUSCI_UART_Config uartConfig =
          {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
            78,                                     // BRDIV = 78
            2,                                       // UCxBRF = 2
            0,                                       // UCxBRS = 0
            EUSCI_A_UART_NO_PARITY,                  // No Parity
            EUSCI_A_UART_LSB_FIRST,                  // LSB First
            EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
            EUSCI_A_UART_MODE,                       // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
          };

          /* Selecting P1.2 and P1.3 in UART mode */
          MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                  GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

          /* Setting DCO to 12MHz */
          CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

          /* Configuring UART Module */
          MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

          /* Enable UART module */
          MAP_UART_enableModule(EUSCI_A0_BASE);
}


int main(void) {

    board_init();

    LED_FLASH_Init();

    uart_init();

    init_aes();      /** initialize AES **/

    /** Choose the function to be called **/
    /** Encrypt or Decrypt possibly many times **/
    /* 1Mbit / 8 = 125000 Bytes
     * PT = 16 Bytes --> This Value of i = 125000/16 = 7812.5
     * Here we are mimicing a 1Mbit input in terms of multiple inputs of smaller memory.
     * We do this since the board has memory limitations
     */

    startTimer();

    for(int i = 0;i < 7813; i++){
    test_encrypt();
    }

    elapsed = getElapsedTime();

     char buf[20];
     sprintf(buf, "Value of AES256 : %lld\n", elapsed);      //Divide by 10 to get ms
     UART0_puts(buf);

    while(1){
        __wfi();
    }
    return 0;
}
