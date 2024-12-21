#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"

/*
Baud Rate = (Clock Source Frequency) / (Prescaler * (Number of Clock Cycles per Bit))

Clock Source Frequency = (DCO Frequency) / 2 = 12 MHz / 2 = 6 MHz

Baud Rate = (6,000,000 Hz) / (78 * (16 samples)) = 9615.38
*/

#define UART_MODULE EUSCI_A0_BASE

/* The eUSCI module is a versatile serial communication module that supports various serial communication protocols,
   including UART,SPI and I2C.*/

void UART_Init(void) {
    // Configure UART pins (P1.2 = RX, P1.3 = TX)
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    // Configure UART settings (9600 baud, 8 data bits, no parity, 1 stop bit)
    const eUSCI_UART_Config uartConfig = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,               // Clock source
        78,                                           // Clock prescaler (UCBRx) [9600 Baud Rate]
        2,                                            // First modulation stage (UCBRSx)
        0,                                            // Second modulation stage (UCBRFx)
        EUSCI_A_UART_NO_PARITY,                       // No parity
        EUSCI_A_UART_LSB_FIRST,                       // Least significant bit first
        EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
        EUSCI_A_UART_MODE,                            // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling
    };

    // Initialize UART with desired settings
    UART_initModule(UART_MODULE, &uartConfig);

    // Enable UART
    UART_enableModule(UART_MODULE);
}

void main(void) {
    // Stop watchdog timer
    WDT_A_holdTimer();

    // Initialize UART
    UART_Init();

    char mssg[] = "Hello World !";
    uint32_t i;

    // Send "Hello, World!" message over UART
    for (i = 0; mssg[i] != '\0';i++ ){
        UART_transmitData(UART_MODULE, mssg[i]);
    }
    UART_transmitData(UART_MODULE,'\n');

    while(1){

        __wfi();
    }
}
