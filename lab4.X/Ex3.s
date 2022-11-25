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
    SETF    TRISB0,1
    call    delay_50ms
    SETF    TRISB0,0
    SETF    TRISB1,1
    call    delay_50ms
    SETF    TRISB1,0
    GOTO    LOOP
    SETF    TRISB2,1
    call    delay_50ms
    SETF    TRISB2,0
    SETF    TRISB3,1
    call    delay_50ms
    SETF    TRISB3,0
    SETF    TRISB4,1
    call    delay_50ms
    SETF    TRISB4,0
    SETF    TRISB5,1
    call    delay_50ms
    SETF    TRISB5,0
    SETF    TRISB6,1
    call    delay_50ms
    SETF    TRISB6,0
    SETF    TRISB7,1
    call    delay_50ms
    SETF    TRISB7,0
    SETF    TRISB8,1
    call    delay_50ms
    SETF    TRISB8,0
    GOTO    LOOP
END resetVec





