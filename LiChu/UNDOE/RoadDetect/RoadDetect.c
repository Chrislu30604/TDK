#include "ASA_Lib.h"

uint32_t Time_Count;

int main()
{
    ASA_M128_set();
	printf("RoadDetect test by LiYu 16.12.10\n");


    return 0;
}
/*=== Timer2 Function ====================================*/
ISR(TIMER2_COMP_vect){
	// 1單位為0.001ms , uint32_t 可記錄 2^32/1000/60/60 = 1193.04647hr
	Time_Count++;
	// printf("%d\n", Time_Count);
	motor_check_time();
	// TIMER2_OVF_fun();
}
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
void TIMER2_OVF_reg (void (*function)(void)){
	TIMER2_OVF_fun=function;
}
/*========================================================*/
