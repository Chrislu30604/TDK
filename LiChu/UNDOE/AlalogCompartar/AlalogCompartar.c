#include "ASA_Lib.h"

void AC_init();
int Count = 0;
int Count2 = 0;

int main(void)
{
	ASA_M128_set();
	printf("AlalogCompartar test by LiYu 16.9.13\n");

	char status = 0, new_status=0;
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
			printf("Status Changed! status = %d , Count = %d , Count2 = %d \n", status, Count, Count2);
		}
	}
}
void AC_init() {
	// SFIOR = 1 << ACME;
	ACSR  = (0<<ACD)  | (0<<ACBG) | (0<<ACO)   | (0<<ACI)
		  | (1<<ACIE) | (0<<ACIC) | (1<<ACIS1) | (0<<ACIS0);
}
ISR(ANALOG_COMP_vect){
	asm("nop");
	Count++;
}
/**
 *STEP1.SFIOR (Special Function IO Register) set
 *enable ACME (Analog Comparator Multiplexer Enable)
 *STEP2. ACSR (Analog Comparator Control and Status Register) set
 *STEP3. set ACI
 *P.59 no.24 $002E ANALOG COMP Analog Comparator
 *P.61 ANA_COMP
 */
