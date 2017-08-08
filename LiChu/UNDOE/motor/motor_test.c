#include "ASA_Lib.h"

#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

void INT_set(char INT_num,char mode);
void PORTE_init() ;

int COUNT=0;
int NEW_COUNT=0;

int main(void)
{
	ASA_M128_set();
	printf("Motor test by LiYu 16.9.25\n");

	uint8_t PWM_ASA_ID = 1;
	unsigned int pwm_data = 500;
	uint8_t check = 0;
	uint8_t target_cycle = 0;
	uint8_t teeth = 23; //原24 減掉鑽孔處偵測為23

	PORTE_init();
	INT_set(4,3);

	sei();

	check = ASA_PWM00_set(PWM_ASA_ID,SET_START_LSBYTE,0x01,0,1);	//set PWM M1 enable
	printf("c1=%d\n",check);										//check point1
	check = ASA_PWM00_put(PWM_ASA_ID,PUT_START_LSBYTE,2,&pwm_data);	//put PWM M1 STOP
	printf("c2=%d\n",check);										//check point1

	while (1) {
		printf("\ninput target_cycle:");
		scanf("%d",&target_cycle);

		pwm_data = 0;
		ASA_PWM00_put(PWM_ASA_ID,0,2,&pwm_data);

		COUNT = 0;
		while( COUNT <= target_cycle * teeth ){
			//do something here ,otherwise get a bug that no break out while
			printf(" ");
		}

		printf("\nEND-------");
		pwm_data = 500;
		ASA_PWM00_put(PWM_ASA_ID,0,2,&pwm_data);
	}

}
void INT_set(char INT_num,char mode) {
	// mode 0:low level trigger
	// mode 1:logic change trigger
	// mode 2:falling edge
	// mode 3:rising trigger
	if (INT_num<4) {
		// EICRA |= (mode)<<(INT_num*2);
	}else{
		DDRE  &= ~(1<<INT_num);
		PORTE |= (1<<INT_num);
		EICRB |= (mode)<<((INT_num - 4)*2);
	}
	EIMSK |= (1<<INT_num);
}
void PORTE_init() { //initialize PORTE 4~7 bits
	DDRE  = 0xF0;
	PORTE = 0xF0;
}
ISR(INT4_vect){
	COUNT++;
}
