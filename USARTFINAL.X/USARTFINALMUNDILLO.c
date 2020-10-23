//Team Microvid 7B Base en C lectura de USART

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#define _XTAL_FREQ 8000000
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//void __interrupt() usart(void){
//    if(PIR1bits.TXIF==0){
        
 //   }
    
//}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void delay(unsigned int time)
{
    for(int i=0;i<1000;i++){
       asm("nop"); 
    }
                                                             //Delay
    
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void main(void) {
    ////////////////////////////////////////////////////////////////////////////////////////
    OSCCON=0B01110100;             //Trabajamos a 8Mhz para posteriormente mediante el registro SPBRG trabajemos a 57600BPS
    /////////////////////////////////////////////////////////////////////////////////////////
    
    INTCON = 0b11000000;                //activamos las interrupciones globales y por perifericos (opcional)
    PIE1 = 0b00000000;                  //Activamos RECIE para recepcion de datos y TXIE para la transmision de datos (REVISAR)
    
    //////////////////////////////////////////////////////////////////////////////////
    
    PORTC = 0x00;                       //limpiamos el portC
    TRISC = 0b10000000;                 //lo colocamos RX como entrada y los demas como salida incluyendo TX
    /////////////////////////////////////////////////////////////////////////////
    
    TXEN = 1;
    SYNC = 0;                      //Activamos la transmision en modo asincrono mediante la modificacion del registro TXSTA y RCSTA
    SPEN =1;
    BRGH=1;
 
    CREN=1;

    SPBRG=8;                       // GRACIAS A LA CONFIGURACION DE LOS PINES SYNC, BRGH Y BGR16 Y DEBIDO A QUE EL OSILADOR ESTA TRABAJANDO A 8MHZ, TRABAJARA A 57600BPS
    ANSEL=0x00;                   //Desactivamos las entradas analogicas para permitir la transmision(NOTA REVISAR ESTO MAS TARDE)
    ANSELH=0x00;
    
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    char g[11]={32,72,79,76,65,32,77,85,78,68,79}; //aqui dice hola mundo
    
    for(int i=0;i<12;i++){
    while(TXSTAbits.TRMT==1){          //TRANMISION DE HOLA MUNDILLO
        TXREG=g[i];
        } 
   
        while(TXSTAbits.TRMT ==0){
            continue;
         } 
     
    }        
    }                              
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    
unsigned char h;
void __interrupt() usart(void){          //recepticon
if(PIR1bits.RCIF==1){
h=RCREG;
            
            
while(TXSTAbits.TRMT==1){               //transmision de lo recibido
TXREG=h;
delay(10);
        }  
    return;
}}