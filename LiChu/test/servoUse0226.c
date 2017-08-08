#include "..\TDK_Lib\ASA_Lib.h"
#include "..\TDK_Lib\TDK_LIB.h"
#include "..\TDK_Lib\TDK_servo.h"
#include "..\TDK_Lib\TDK_timer.h"


int main(int argc, char const *argv[])
{
	ASA_M128_set();
    TIMER3_init();
	printf("servo test by chrislu 2017/06/26 \n");
	int id = 0;
    int deg = 0;
	while(1)
	{
        printf("\nInput ID:");
        scanf("%d", &id);
        printf("\nInput deg:");
        scanf("%d", &deg);
        servo_set(id,deg);
	}
}
