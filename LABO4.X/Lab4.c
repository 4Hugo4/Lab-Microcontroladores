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


MAIN:
    ; CLOCK CONFIGURATION
    BANKSEL OSCCON	;ACCESS TO OSCCON REGISTER 
    MOVLW   0x5E	   ;4MHZ FREQUENCY OF INTERNAL OSCILLATOR
    MOVWF   OSCCON,1	;LOAD DATA THROUGH BSR

    ; GPIO CONFIGURATION
    CLRF    TRISB,0   ;CONFIGURE PORT B AS OUTPUT
    SETF    LATB,0    ;TURN OFF LEDS CONNECTED TO PORT B

EX1:
    CLRF    LATB,0
    CALL    delay_200ms
    SETF    LATB,0
    CALL    delay_200ms
    GOTO    EX1

EX2:
    MOVLW   6
    MOVWF   COUNT,0
    MOVLW   01111111B
    MOVWF   LATB,0
    CALL    delay_50ms
LOOP_1:
    RRNCF   LATB
    CALL    delay_50ms
    DECFSZ  COUNT,1,0
    GOTO    LOOP_1

    MOVLW   6
    MOVWF   COUNT,0
    MOVLW   11111110B
    MOVWF   LATB,0
    CALL    delay_50ms
LOOP_2:
    RLNCF   LATB
    CALL    delay_50ms
    DECFSZ  COUNT,1,0
    GOTO    LOOP_2
GOTO    EX2

EX4:
    MOVLW	11111111B
    MOVWF	LATB,0
    CALL	delay_200ms
    MOVLW	11100111B
    MOVWF	LATB,0
    CALL	delay_200ms
    MOVLW	11000011B
    MOVWF	LATB,0
    CALL	delay_200ms
    MOVLW	10000001B
    MOVWF	LATB,0
    CALL	delay_200ms
    MOVLW	00000000B
    MOVWF	LATB,0
    CALL	delay_200ms
GOTO	EX4

END resetVec
