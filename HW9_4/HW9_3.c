
// Global Variables

const unsigned char MSG0[21] = "Hungry Hippos      "; 
const unsigned char MSG1[21] = "RB1 to start       ";
const unsigned char MSG2[21] = "P1 Wins!           "; 
const unsigned char MSG3[21] = "P2 Wins!           ";    
const unsigned char MSG4[21] = "Game Start         ";
const unsigned char MSG5[21] = "Tie!               ";    

int P1,P2;
unsigned long int TIME;

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
   if (INT0IF) {
      P1+=1;
      INT0IF = 0;
      }      
   if (INT2IF) {
      P2+=1;
      INT2IF = 0;
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
   LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);
   Wait_ms(2000);
   LCD_Inst(1);

// Turn on INT0 interrupt
   INT0IE = 1;
   TRISB0 = 1;
   INTEDG0 = 1;

// Turn on INT2 interrupt
   INT2IE = 1;
   TRISB2 = 1;
   INTEDG2 = 1;

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
		P1 = 0;
   		P2 = 0;
		if(RB1){
			LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG4[i]);
			Wait_ms(10000);
			LCD_Move(0,0);  
      		LCD_Out(P1, 3, 0);
      		LCD_Out(P2, 3, 0);
			if(P1>P2){
				LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG2[i]);
			}
			else if(P2>P1){ 
				LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG3[i]);
			}
			else{
				LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG5[i]);
			}
			Wait_ms(10000);
			LCD_Inst(1);
		}
	}	     

   }

