#include "ASA_Lib.h"

void INT_set(char INT_num,char mode);

int count=0;

int main(void)
{
	ASA_M128_set();
	printf("START!!\n");
	int new_count=0;
	DDRE = 0xF0;
	PORTE = 0xF0;

	INT_set(4,3);

	sei();


	while (1) {
		asm("nop");
		if (count > new_count) {
			printf("count = %d\n", count);
			new_count = count;
		}
	}

}
void INT_set(char INT_num,char mode) {
	if (INT_num<4) {
		// EICRA |= (mode)<<(INT_num*2);
	}else{
		DDRE  &= ~(1<<INT_num);
		PORTE |= (1<<INT_num);
		EICRB |= (mode)<<((INT_num - 4)*2);
	}
	EIMSK |= (1<<INT_num);
}

ISR(INT4_vect){
	count++;
}
