#include "ASA_Lib.h"
/*=== INT function ===============================*/
void PORTE_init();
void INT_set(char INT_num,char mode);
/*================================================*/

/*=== INT function ===============================*/
void INT_set(char INT_num, char mode) {
	// mode 0:low level trigger
	// mode 1:logic change trigger
	// mode 2:falling edge trigger
	// mode 3:rising edge trigger
	if (INT_num<4) {
		// EICRA |= (mode)<<(INT_num*2);
		return;
	}else{
		DDRE  &= ~(1<<INT_num);
		PORTE |= (1<<INT_num);
		EICRB |= (mode)<<((INT_num - 4)*2);
	}
	EIMSK |= (1<<INT_num);
}
void INT_cls(char INT_num) {
	if (INT_num<4) {
		return;
	}else{
		DDRE  |=  (1<<INT_num);
		PORTE &= ~(1<<INT_num);
	}
	EIMSK &= ~(1<<INT_num);
}
/*================================================*/
