
// Global Variables
const unsigned char MSG0[21] = "1 Second Timer     ";    

int P1,P2;
unsigned long int TIME,T1,T2;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// High-priority service
void interrupt IntServe(void)
{
   if (TMR0IF) {
		TIME += 0x10000;
		TMR0IF = 0;
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

// turn on all interrupts
   GIE = 1;

   P1 = 0;
   P2 = 0;

 while(1) {
 	T1 = TIME + TMR0;
 	Wait_ms(1000);
 	T2 = TIME + TMR0;
 	LCD_Move(1,0); LCD_Out(T2 - T1, 10, 7);
 	}	     

 }

