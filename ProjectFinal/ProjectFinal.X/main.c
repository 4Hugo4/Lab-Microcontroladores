/*
    Programacion Equipo 4 - Microcontroladores
 */

//// Code V.4
#include "mcc_generated_files/mcc.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>


//unsigned int Input_A0=0;
char temp[5];

    // ADC -> UART
void Send_ADC_to_UART()  
                        {
    
    temp[0]=(Input_A0/10000)+48;
    temp[1]=((Input_A0/1000)%10)+48;
    temp[2]=((Input_A0/100)%10)+48;
    temp[3]=((Input_A0/10)%10)+48;
    temp[4]=(Input_A0%10)+48;
                        
    for(int i=0;i<5;i++)
    {
        while (!(UART1_is_tx_ready()));
        UART1_Write(temp[i]);
    }
                        }

    // Escribir valor voltaje
void UART1_sendString(const char *str)
{
    while(*str)
    {
        while (!(UART1_is_tx_ready()));
        UART1_Write(*str++);
    }
}

void main(void)
{
    // Initialize device
    //UART1_Initialize();
    //ADCC_Initialize();
    SYSTEM_Initialize();

    while (1)
    {
        adc_result_t Input_A0 = ADCC_GetSingleConversion(0);  // Leer canal
        
        UART1_sendString("\r\n ADC VALUE= ");
        Send_ADC_to_UART();
        __delay_ms(1000);
    }
}
/**
 End of File
*/