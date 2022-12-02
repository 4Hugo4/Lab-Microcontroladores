#include "mcc_generated_files/mcc.h"

#define COMMAND_MODE    LCD_RS_SetLow()
#define DATA_MODE       LCD_RS_SetHigh() 

void LCD_initialize(void);
void LCD_display_character(char);
void LCD_send_command(char);
/*
                         Main application
 */
void main(void)
{
    SYSTEM_Initialize();
    while (1)
    {
        // Add your application code
        __delay_ms(2000);
        char i = 0;
        char line_1[16] = {'T', 'E', '2', '0', '1', '5', ' ', '-', ' ', 'L', 'a', 'b', ' ', 'd', 'e', ' '};
        char line_2[16] = {'M', 'i', 'c', 'r', 'o', 's', ' ', 'A', 'D', '2', '0', '2', '2', ' ', ' ', ' '};
        
        LCD_initialize();
        
        for (i = 0; i < sizeof line_1; i++){
            LCD_display_character(line_1[i]);
        }

        LCD_send_command(0xC0); // Move to position 1 of line 2
        
        for (i = 0; i < sizeof line_2; i++){
            LCD_display_character(line_2[i]);
        }
        while(1);
    }
}

void LCD_send_command(char command){
    COMMAND_MODE;
    LATD = command;        
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch
}

void LCD_display_character(char c){
    DATA_MODE;
    LATD = c;           // Set display address
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch  
}

void LCD_initialize(void){
        // LCD Initialization
    COMMAND_MODE;
    LATD = 0x38;        // 8-bit mode
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch

    LATD = 0x02;        // Display home
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch
            
    LATD = 0x0C;        // Display ON
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch        

    LATD = 0x01;        // Clear display
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch

    LATD = 0x80;        // Set display address
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();     // Enable the data latch
    
    DATA_MODE;
}
/**
 End of File
*/