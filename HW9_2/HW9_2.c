
// Global Variables

const unsigned char MSG0[21] = "4 Chord            ";    
const unsigned int A3 = 21451;
const unsigned int G3 = 24078;
const unsigned int F3 = 27027;
const unsigned int D3 = 32142;

unsigned int N0,N1,N3;
unsigned long int TIME,T1,T2;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// High-priority service
void interrupt IntServe(void)
{
 if (TMR0IF) {
 	TMR0 = -N0;
 	RC0 = !RC0;
 	TMR0IF = 0;
 }
 if (TMR1IF) {
 	TMR1 = -N1;
 	RC1 = !RC1;
 	TMR1IF = 0;
 }
 if (TMR2IF) {
 	if(RB0) {N0 = D3; N1 = F3; N3 = A3;}
 	TMR2IF = 0;
 }
 if (TMR3IF) {
 	TMR3 = -N3;
 	RC3 = !RC3;
 	TMR3IF = 0;
 }
}
   

         
// Main Routine

void main(void)
{
   unsigned char i;
   unsigned int j;
   double sec, inch;
   unsigned long int TIME0,TIME1;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD
   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);

// set up Timer0 for PS = 1
 	T0CS = 0;
 	T0CON = 0x88;
 	TMR0ON = 1;
 	TMR0IE = 1;
 	TMR0IP = 1;
 	PEIE = 1;
// set up Timer1 for PS = 1
 	TMR1CS = 0;
 	T1CON = 0x81;
 	TMR1ON = 1;
 	TMR1IE = 1;
 	TMR1IP = 1;
 	PEIE = 1;
// set up Timer2 for A = 10, B = 239, C = 16
 	T2CON = 0x4F;
 	PR2 = 238;
 	TMR2ON = 1;
 	TMR2IE = 1;
 	TMR2IP = 1;
 	PEIE = 1;
// set up Timer3 for PS = 1
 	TMR3CS = 0;
 	T3CON = 0x81;
 	TMR3ON = 1;
 	TMR3IE = 1;
 	TMR3IP = 1;
 	PEIE = 1;
// turn on all interrupts
 	GIE = 1;

 while(1) {
 	}	     

 }

