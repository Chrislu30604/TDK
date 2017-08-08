#include "ASA_Lib.h"

void main()
{
    ASA_M128_set();
	printf("Timer3 test by LiYu 16.10.05\n");

    TIMER3_init();


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
void TIMER3_init(){
    //Configure TIMER1
	TCCR3A|=(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM31);        //NON Inverted PWM (enable OCR1A,OCR1B)
	TCCR3B|=(1<<WGM33)|(1<<WGM32)|(1<<CS31)|(0<<CS30); //PRESCALER=8 MODE 14(FAST PWM)

	ICR3=27992;  //fPWM=50Hz (Period = 20ms Standard).
    //PRESCALER=8 ICR1=27992
    //PRESCALER=64 ICR1=3499
    DDRE|=(1<<PE4)|(1<<PE5);   //PWM Pins as Out
}
void servo_set(uint8_t id,uint8_t target_angle){
    // 0.00052643 (ms/per_val)
    // min = 700  (? ms) 0 degree
    // max = 3300 (? ms) 180 degree
    // TODO 觀察 OCR-角度 或 ms-角度 是否呈現線性關係 YES
    // TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值

    //(2720-640)/180 = 11.55 (degree/per_arget_data)
    float rate = (3300-700)/180; //(14.44)

    uint16_t target_data = (float)target_angle * rate + 700;
    printf("%d\n", target_data);
    if (id == 0) {
        OCR3C = target_data;
    } else if (id == 1) {
        OCR3B = target_data;
    } else {
        return 1;
    }

    return 0;
    // return 0:沒問題, 1:wrong ID, 2:wrong mode, 3:wrong data
}
