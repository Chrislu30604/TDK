#include "ASA_Lib.h"
// #include<avr/interrupt.h>
/* Analog Comparator */
// #define ANALOG_COMP_vect                _VECTOR(28)
// #define ANALOG_COMP_vect_num            28

void AC_init();

int Count = 0;
int Count2 = 0;




int r1=0,r2=0;

int main(void)
{
	char status = 0, new_status=0;
	ASA_M128_set();
	printf("PWM00 test by LiYu 16.9.13\n");
	// printf("%d\n",INT4_vect);
	AC_init();
	printf("%d\n", ACSR);
	sei();
	while (1) {
		asm("nop");
		new_status = (ACSR>>5) && 1;
		if (new_status != status) {
			asm("nop");
			status = new_status;
			Count2++;
			// if(Count2>=44){
			// 	r2++;
			// 	Count2 -= 44;
			// }
			printf("Changed! status = %d , Count = %d , Count2 = %d \n", status, Count, Count2);
		}
		// printf("status = %d\n", status);
		// status = (ACSR>>5) && 1;
		asm("nop");
	}
}
void AC_init() {
	SFIOR = 1 << ACME;
	ACSR  = (0<<ACD)  | (0<<ACBG) | (0<<ACO)   | (0<<ACI)
		  | (1<<ACIE) | (0<<ACIC) | (1<<ACIS1) | (1<<ACIS0);
	// printf("%d\n", ACIE);
	// printf("%d\n", ACIS1);
	// printf("%d\n", ACIS0);
	//
	// ACSR = 8;
}
ISR(ANALOG_COMP_vect){
	// ACSR |= 1<<ACI;
	asm("nop");
	// printf("TEST\n");
	Count++;
	// if(Count>=44){
	// 	r2++;
	// 	Count -= 44;
	// }
}
/**
 *STEP1.SFIOR (Special Function IO Register) set
 *enable ACME (Analog Comparator Multiplexer Enable)
 *STEP2. ACSR (Analog Comparator Control and Status Register) set
 *STEP3. set ACI
 *P.59 no.24 $002E ANALOG COMP Analog Comparator
 *P.61 ANA_COMP
 */
