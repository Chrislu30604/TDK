// test for servo motor by chrislu 17/07/25
// test for PWM01
#include "..\TDK_Lib\ASA_Lib.h"
#include "..\TDK_Lib\TDK_LIB.h"
#include <util\delay.h>


int main(int argc, char const *argv[])
{
	char ASAID = 1, Mask = 0xff, shift = 0, Settings = 0xff;
	char put_LSByte = 0, set_LSByte = 200, get_LSByte = 100, Bytes = 8;   //put_LSByte 對應0~7 port
	int Command = 0;
	int check = 0;
	int Read = 0;

	ASA_M128_set();
	TIM_set();
	sei();
	printf("\ninitial\n");
	while(1){
		printf("\nEnter degree : ");
		scanf("%d",&Command);

		check = ASA_PWM01_put(ASAID, put_LSByte, Bytes, &Command);
		if (check != 0) printf("Error in put %d \n",check);
		check = ASA_PWM01_set(ASAID, set_LSByte, Mask, shift, Settings);
		if (check != 0) printf("Error in set %d \n",check);
		check = ASA_PWM01_get(ASAID, get_LSByte, Bytes, &Read);
		if (check != 0) printf("Error in get %d \n",check);
		_delay_ms(500);

	}



}
