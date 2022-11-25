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
    SETF    LATB,1
    call    delay_200ms
    SETF    LATB,0 
    GOTO    LOOP
    
END resetVec


