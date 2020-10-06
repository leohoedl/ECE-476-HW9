// Measure the angle from an optical encoder
// Use INT0 to record channel A
// Use INT1 to record channel B

// Global Variables

const unsigned char MSG0[21] = "INT Demo           "; 
const unsigned char MSG1[21] = "                   ";     

int V0;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// High-priority service
void interrupt IntServe(void)
{
   if (INT0IF) {
      V0 += 1;
      INT0IF = 0;
      }   
   if (INT1IF) {
      V0 -= 1;
      INT1IF = 0;
      }   
   }
   

         
// Main Routine

void main(void)
{
   unsigned char i;
   unsigned int j;
   double sec, inch;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
   LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

// Turn on INT0 interrupt
   INT0IE = 1;
   TRISB0 = 1;
   INTEDG0 = 1;

// Turn on INT1 interrupt
   INT1IE = 1;
   TRISB1 = 1;
   INTEDG1 = 1;

// Turn on INT2 interrupt
   INT2IE = 1;
   TRISB2 = 1;
   INTEDG2 = 1;

// turn on all interrupts
   GIE = 1;

   V0 = 0;

   while(1) {
      LCD_Move(1,0);  
      LCD_Out(V0, 3, 0);
      Wait_ms(20);
      }      


   }