/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include "experiment_time.h"

#define portable8439

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define UART

#include "msp432.h"
#include "rom_map.h"
#include "rom.h"
#include "systick.h"
#include "driverlib.h"

#define board_init() WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD

#define RED_LED1_PIN GPIO_PIN0
#define LED1_PORT GPIO_PORT_P2

#ifdef portable8439
#include "portable8439/chacha-portable/chacha-portable.h"
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#endif

#ifdef portable8439
#define MAX_TEST_SIZE (512)

struct chacha_test_vector {
    char* title;
    uint8_t key[CHACHA20_KEY_SIZE];
    uint8_t nonce[CHACHA20_NONCE_SIZE];
    uint32_t counter;
    uint8_t plain_text[MAX_TEST_SIZE];
    uint8_t cipher_text[MAX_TEST_SIZE];
    size_t size;
};

uint8_t buffer[MAX_TEST_SIZE] = {0};

static struct chacha_test_vector e = {
    "RFC8439 2.4.2",
    {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f},
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4a,0x00,0x00,0x00,0x00},
    1,
    {
      0x4c,0x61,0x64,0x69,0x65,0x73,0x20,0x61,0x6e,0x64,0x20,0x47,0x65,0x6e,0x74,0x6c,
      0x65,0x6d,0x65,0x6e,0x20,0x6f,0x66,0x20,0x74,0x68,0x65,0x20,0x63,0x6c,0x61,0x73,
      0x73,0x20,0x6f,0x66,0x20,0x27,0x39,0x39,0x3a,0x20,0x49,0x66,0x20,0x49,0x20,0x63,
      0x6f,0x75,0x6c,0x64,0x20,0x6f,0x66,0x66,0x65,0x72,0x20,0x79,0x6f,0x75,0x20,0x6f,
      0x6e,0x6c,0x79,0x20,0x6f,0x6e,0x65,0x20,0x74,0x69,0x70,0x20,0x66,0x6f,0x72,0x20,
      0x74,0x68,0x65,0x20,0x66,0x75,0x74,0x75,0x72,0x65,0x2c,0x20,0x73,0x75,0x6e,0x73,
      0x63,0x72,0x65,0x65,0x6e,0x20,0x77,0x6f,0x75,0x6c,0x64,0x20,0x62,0x65,0x20,0x69,
      0x74,0x2e
    },
    {
      0x6e,0x2e,0x35,0x9a,0x25,0x68,0xf9,0x80,0x41,0xba,0x07,0x28,0xdd,0x0d,0x69,0x81,
      0xe9,0x7e,0x7a,0xec,0x1d,0x43,0x60,0xc2,0x0a,0x27,0xaf,0xcc,0xfd,0x9f,0xae,0x0b,
      0xf9,0x1b,0x65,0xc5,0x52,0x47,0x33,0xab,0x8f,0x59,0x3d,0xab,0xcd,0x62,0xb3,0x57,
      0x16,0x39,0xd6,0x24,0xe6,0x51,0x52,0xab,0x8f,0x53,0x0c,0x35,0x9f,0x08,0x61,0xd8,
      0x07,0xca,0x0d,0xbf,0x50,0x0d,0x6a,0x61,0x56,0xa3,0x8e,0x08,0x8a,0x22,0xb6,0x5e,
      0x52,0xbc,0x51,0x4d,0x16,0xcc,0xf8,0x06,0x81,0x8c,0xe9,0x1a,0xb7,0x79,0x37,0x36,
      0x5a,0xf9,0x0b,0xbf,0x74,0xa3,0x5b,0xe6,0xb4,0x0b,0x8e,0xed,0xf2,0x78,0x5e,0x42,
      0x87,0x4d
    },
    114
};

#endif

void LED_FLASH_Init(void){
    GPIO_setAsOutputPin(LED1_PORT,RED_LED1_PIN);
}

void test_enc()
{
  chacha20_xor_stream(buffer, e.plain_text, e.size, e.key, e.nonce, e.counter);
}

void test_dec()
{
  chacha20_xor_stream(buffer, e.cipher_text, e.size, e.key, e.nonce, e.counter);
}

///******************************
// *
// * Function to verify encryption
// *
// ******************************/
int check_encrypt() {
#ifdef portable8439
    if (memcmp(buffer, e.cipher_text, e.size) != 0) {
        return -1;
    }
    else {
        return 1;
    }
    #endif

    return 0;
}
//
///******************************
// *
// * Function to verify decryption
// *
// ******************************/
int check_decrypt() {
#ifdef portable8439
    if (memcmp(buffer, e.plain_text, e.size) != 0) {
        //            printf("failed\n");
        return -1;
    }
    else {
        //            printf("success\n");
        return 1;
    }
    #endif

    return 0;
}

#ifdef UART
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
    #endif

//Use void loop instead of int main for arduino
// void loop()
int main (void)
{

board_init();

#ifdef UART
    uart_init();
#endif

    LED_FLASH_Init();

  /** test CHACHA **/
    /* Now the input we have is 114 Bytes.
     * Again we have 1Mbit / 8 = 125000 Bytes
     * Value of i = 125000/114 = 1096.50*/

    startTimer();

    for (int i = 0; i < 1097; i++){
        test_enc();
    }
    elapsed = getElapsedTime();

     //check_encrypt();
//       test_dec();

    #ifdef UART
        char buf[20];
        sprintf(buf, "Value ChaCha20: %lld\n", elapsed);        //Divide by 10 to get ms
        UART0_puts(buf);
    #endif


        while(1){
           __wfi();
        }
      return 0;
}
