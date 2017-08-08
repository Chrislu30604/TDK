#include "ASA_Lib.h"

void main()
{
    ASA_M128_set();
	printf("SerialPort test by LiYu 16.10.11\n");
    uint16_t data=0;
    ASA_get(&data);
    printf("Road\n");
    ASA_get(&data);
    ASA_put(data*5);


    printf("END\n");
    return 0;
}

void ASA_put(uint16_t data) {
    printf("%d\n", data);
}
void ASA_get(uint16_t* data) {
    scanf("%d", data);
}
void ASA_put_f(float data) {
    printf("%f\n", data);
}
void ASA_get_f(float* data) {
    scanf("%f\n", data);
}
