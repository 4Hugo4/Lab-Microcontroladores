#include "config_header.h"
#define _XTAL_FREQ 1000000


#define LCD_DATA_R PORTD 
#define LCD_DATA_W LATD  
#define LCD_DATA_DIR TRISD  
#define LCD_RS LATCbits.LATC2 
#define LCD_RS_DIR TRISCbits.TRISC2  
#define LCD_RW LATCbits.LATC1  
#define LCD_RW_DIR TRISCbits.TRISC1
#define LCD_E LATCbits.LATC0
#define LCD_E_DIR TRISCbits.TRISC0


enum port_dir{ output , input};
enum port_DCAC{ digital, analog};
enum buton_state{ pushed , no_pushed};


//ISR for high priority
__interrupt( high_priority ) void high_isr( void ){
    Nop( );
}


//ISR for low priority
__interrupt( low_priority) void low_isr( void ){
    Nop( );
}


void portsInit(void); //Function definition to initialize ports
char getTeclado(void); //Function definition to get key
void send2LCD(char xy);
void LCD_init(void);
void LCD_cmd(char cx);
void LCD_rdy(void);


char sweepout=0b11101111; //Ground first pin for High nibble (RB4-RB7)
char one_pos=1; //Declaration of first variable
char four_pos=4; //Declaration of four positions for left shift operation
char mask=0; //Declare mask with 0
char shift=0; //Declare shift with 0
char key=0; //Declare key with 0
int i=0; //Declare i with 0 for loop
int j=0; //Declare j with 0 for loop
    
char teclado[ 4 ][ 4 ] = { { 7, 8,  9, 10 }, //Matrix with keypad values 
                               { 4, 5,  6, 11 },
                               { 1, 2,  3, 12 },
                               { 15, 0, 14, 13 } };
    
void main(void) {
    
    portsInit(); //Calls for initialization function for the ports
    LCD_init();
    
    char num1=' ';
    char num2=' ';
    char op=' ';
    char res=' ';
    char res1=' ';
    char res2=' ';
    char print=' ';
    char cursor=0x8F;
    
 while( 1 ) { 
     
        key=0;
        key = getTeclado( ); //Get keypad value
        __delay_ms( 300 ); //300ms debounce delay
                
        if(num1==' '){
            num1=key;
        }
        else if(op==' '){
            op=key;
        }
        else if(num2==' '){
            num2=key;
        }
        
        LCD_cmd(0x07); 
        
        switch(key){
                case 0:
                    send2LCD('0');
                    break;
                case 1:      
                    send2LCD('1');
                    break;
                case 2: 
                    send2LCD('2');
                    break;
                case 3:
                    send2LCD('3');
                    break;
                case 4: 
                    send2LCD('4');
                    break;
                case 5:
                    send2LCD('5');
                    break;
                case 6: 
                    send2LCD('6');
                    break;
                case 7:
                    send2LCD('7');
                    break;
                case 8:
                    send2LCD('8');
                    break;
                case 9: 
                    send2LCD('9');
                    break;
                case 10: 
                    send2LCD('/');
                    break;
                case 11: 
                    send2LCD('x');
                    break;
                case 12: 
                    send2LCD('-');
                    break;
                case 13: 
                    send2LCD('+');
                    break;
                case 14: 
                    
                    
                    switch (op)
                    {
                        case 10:
                        res=num1/num2;
                            break;
                            
                        case 11:
                        res=num1*num2;
                            break;  
                            
                        case 12:
                        res=num1-num2;
                            break; 
                            
                        case 13:
                        res=num1+num2;
                            break;
                    }
                    
                    res1=res%10;
                    res1=res1+'0';
                    
                    res2=res/10;
                    res2=res2+'0';      
                    
                    LCD_cmd(0x06);
                    if(res2!='0'){
                    LCD_cmd( 0xD1 ); //
                    send2LCD(res2);
                    }
                    LCD_cmd( 0xD2 ); //
                    send2LCD(res1);


                    num1=' ';
                    num2=' ';
                    op=' ';
                    
                    break;
                    
                case 15: // CLEAR DISPLAY EVENT
                    LCD_cmd( 0x01 ); //clear display and move cursor to home
                    LCD_cmd( 0x90 ); //start writing from right to left
                    num1=' ';
                    num2=' ';
                    op=' ';
                    
                    break;                    
        }    
        
        
      
 }
}






char getTeclado( void ) {
    while( 1 ) { //Loop using nested for´s through the keypad until one key is returned
        LATB = sweepout; //Ground RB4 to be shifted later in the MSN
        for( i = 0; i < 4; i++ ) { //Loop through the most significant nibble (MSN)
            mask = 0b00000001; //The mask serves to check first bit of LSN but is then shifted within the nested loop          
            for( j = 0; j < 4; j++ ){ //Loop through the least significant nibble (LSN)   
                if( !( PORTB & mask ) ) //Verify if this combination is pressed
                    return teclado[ j ][ i ]; //Look up combination in matrix and return key
                mask = mask << one_pos; //Shift to the left to check next key (e.g. RB0 next RB1)
            }     
            LATB = LATB << one_pos; //After LSM is looped, the next pin is grounded (e.g. RB4 next RB5)
        }
    }
}


void portsInit(void){
    //PORT B port initialization
    ANSELB = digital; //Sets ANSELA to digital
    TRISB = 0x0F; //Sets MSN to output and LSN to input
    WPUB=0x0F; //Enables weak pull-ups to LSN which are defined as input
    INTCON2bits.RBPU=0; //Enables weak pull ups
    
    //PORT D port initialization
    ANSELD = digital; //Sets ANSELB to digital
    TRISD = output; //Sets TRISD as output (to 0)
    LATD = 0x00; //Initializes Port D to low level
    
    //PORT C port initialization
    ANSELC = digital; //Sets ANSELB to digital
    TRISC = output; //Sets TRISD as output (to 0)
    LATC = 0x00; //Initializes Port D to low level
}


/* The following function waits until the LCD is not busy */
void LCD_rdy( void ) {
    char test;
    //configure LCD data bus for input
    LCD_DATA_DIR = 0b11111111;                    
    test = 0x80;
    while( test ) {
        LCD_RS = 0; //select IR register
        LCD_RW = 1; //set read mode
        LCD_E = 1; //setup to clock data          
        test = LCD_DATA_R;
        Nop();
        LCD_E = 0; //complete a read cycle
        test &= 0x80; //check flag busy bit     
    }
    LCD_DATA_DIR = 0b00000000;
}


/* The following function sends a command to the LCD */
void LCD_cmd( char cx ) {
    LCD_rdy(); //wait until LCD is ready
    LCD_RS = 0; //select IR register
    LCD_RW = 0; //set write mode
    LCD_E = 1; //setup to clock data
    Nop();
    LCD_DATA_W = cx; //send out the command
    Nop(); //small delay to lengthen E pulse
    LCD_E = 0; //complete an external write cycle
}


/* The following function initializes the LCD properly*/
void LCD_init( void ) {
    LATC = 0; //make sure LCD control port is low
    LCD_E_DIR = 0; //config LCD enable pin for output
    LCD_RS_DIR = 0; //config LCD RS pin for output
    LCD_RW_DIR = 0; //config LCD R/W pin for output
    LCD_cmd( 0x38 ); //configure display to 2x40
    LCD_cmd( 0x0F ); //turn on display, cursor and blinking
    LCD_cmd( 0x01 ); //clear display and move cursor to home
    LCD_cmd( 0x90 ); //start writing from right to left
}


void send2LCD( char xy ) {
    LCD_RS = 1;          
    LCD_RW = 0;          
    LCD_E = 1;
    LCD_DATA_W = xy;
    Nop();
    Nop();
    LCD_E = 0;
}