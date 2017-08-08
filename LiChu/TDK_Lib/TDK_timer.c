// last modified by LiYu 2017.05.14
#include "TDK_timer.h"
#include "ASA_Lib.h"

/*=== Timer3 functioin ===================================*/
void TIMER3_init(){
    //Configure TIMER1
	TCCR3A|=(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM31);//NON Inverted PWM (enable OCR1A,OCR1B)
	TCCR3B|=(1<<WGM33)|(1<<WGM32)|(1<<CS31)|(0<<CS30);     //PRESCALER=8 MODE 14(FAST PWM)

	ICR3=27992;  //fPWM=50Hz (Period = 20ms Standard).
    //PRESCALER=8 ICR1=27992
    //PRESCALER=64 ICR1=3499

    DDRE  |=(1<<PE4)|(1<<PE5);   //PWM Pins as Out
    PORTE &=~(1<<PE4);
    PORTE &=~(1<<PE5);
}
/*========================================================*/

/*=== Timer2 Function ============================*/
void TIMER2_init(){
	TCCR2  = 0;
	TCCR2 |= (1<<WGM21) | (0<<WGM20); // CTC mode
	TCCR2 |= (0<<COM21) | (0<<COM20); // no Compare Output
    TCCR2 |= (0<<CS22)  | (1<<CS21) | (1<<CS20); // set up timer with prescaler = 64
    TCNT2  = 0;	// initialize counter
    TIMSK |= (1<<OCIE2) | (0<<TOIE2); // Output Compare Match Interrupt Enable
	OCR2 = 171; // f = 11059200/64/(1+171) = 1004.65116, see as 1000hz, err = 0.5%
	// printf("TCCR2 = %d, TIMSK = %d\n", TCCR2, TIMSK);
}
/*================================================*/
