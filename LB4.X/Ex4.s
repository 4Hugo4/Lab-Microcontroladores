PROCESSOR   18F45K50
#include    <xc.inc>
#include    "configuration_bits.inc"
#include    "delays.inc"

PSECT udata_acs
; DECLARE HERE YOUR VARIABLES WITH FORMAT: "VAR_NAME: DS 1"

PSECT	resetVec, class=CODE, reloc=2

PSECT	absdata, abs, ovrld
absdata:
    org	    0x1000

resetVec:
    goto    MAIN

PSECT code
MAIN:
    ; CLOCK CONFIGURATION
    BANKSEL OSCCON	;ACCESS TO OSCCON REGISTER 
    MOVLW   0x5E	   ;4MHZ FREQUENCY OF INTERNAL OSCILLATOR
    MOVWF   OSCCON,1	;LOAD DATA THROUGH BSR

    ; GPIO CONFIGURATION
    CLRF    TRISB,0   ;CONFIGURE PORT B AS OUTPUT
    SETF    LATB,0    ;TURN OFF LEDS CONNECTED TO PORT B
  
LOOP:     
    SETF    LATB0 = 0X00;
    call    delay_50ms
    SETF    LATB0 = 0X18;
    call    delay_50ms
    SETF    LATB0 = 0X3C;
    call    delay_50ms
    SETF    LATB0 = 0X7E;
    call    delay_50ms
    SETF    LATB0 = 0XFF;
    call    delay_50ms
    SETF    LATB0 = 0X00;
    call    delay_50ms  
    GOTO    LOOP
END resetVec





