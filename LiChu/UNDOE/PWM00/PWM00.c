#include "ASA_Lib.h"
#include <inttypes.h>

void AC_init();
int Count = 0;
int Count2 = 0;

int main(void)
{
	int ASA_ID = 1;
	char set_lsbyte = 200;
	char put_lsbyte = 0;
	char mask  = 0xFF;
	char shift = 0;
	char data  = 100;
	char bytes = 2;
	uint16_t vol = 0;
	unsigned int pwm_data = 1000;
	char check = 0;


	ASA_M128_set();
	printf("PWM00 test by LiYu 16.9.16\n");


	check = ASA_PWM00_set(ASA_ID,set_lsbyte,0x03,0,3);
	printf("c1=%d\n",check);
	check = ASA_PWM00_put(ASA_ID,0,2,&pwm_data);
	printf("c2=%d\n",check);
	check = ASA_PWM00_put(ASA_ID,2,2,&pwm_data);
	printf("c2=%d\n",check);
	while (1) {
		printf("\ndata = ");
		scanf("%d",&pwm_data);
		printf("pwm_data = %d", pwm_data);
		asm("nop");
		ASA_PWM00_put(ASA_ID,2,2,&pwm_data);
		ASA_PWM00_put(ASA_ID,0,2,&pwm_data);
		asm("nop");
	}
}
