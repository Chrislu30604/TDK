/*
 * Last modify at 2016.10.25 2pm bu LiYu
 * Just take care of the HL to the PWM00
 */
#include "ASA_Lib.h"

/*=== Servo Funtion Define =======================*/
#define SERVO_GRIPPING 0
#define SERVO_ROTATING 1
/*================================================*/

/*=== Timer3 function ============================*/
void TIMER3_init();
/*================================================*/

/*=== Servo funcion ==============================*/
void servo_init();
uint8_t servo_set(uint8_t id,uint8_t target_angle);
// TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值 )
/*================================================*/

/*=== Main =======================================*/
void main()
{
    ASA_M128_set();
	printf("Servo test by LiYu 16.10.02\n");

    TIMER3_init();
    servo_init();

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
/*================================================*/

/*=== Timer3 functioin ===========================*/
void TIMER3_init(){
    //Configure TIMER1
	TCCR3A|=(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM31);        //NON Inverted PWM (enable OCR1A,OCR1B)
	TCCR3B|=(1<<WGM33)|(1<<WGM32)|(1<<CS31)|(0<<CS30); //PRESCALER=8 MODE 14(FAST PWM)

	ICR3=27992;  //fPWM=50Hz (Period = 20ms Standard).
    //PRESCALER=8 ICR1=27992
    //PRESCALER=64 ICR1=3499

    DDRE  |=(1<<PE4)|(1<<PE5);   //PWM Pins as Out
    PORTE &=~(1<<PE4);
    PORTE &=~(1<<PE5);
}
/*================================================*/

/*=== Servo funcion ==============================*/
void servo_init() {
    //以大角度啟動後復位到0度
    servo_set(SERVO_GRIPPING,30);
    servo_set(SERVO_ROTATING,30);
    _delay_ms(500);
    servo_set(SERVO_GRIPPING,0);
    servo_set(SERVO_ROTATING,0);
}
uint8_t servo_set(uint8_t id,uint8_t target_angle){
    // 0.00052643 (ms/per_val)
    // min = 700  (? ms) 0 degree
    // max = 3300 (? ms) 180 degree
    // TODO 觀察 OCR-角度 或 ms-角度 是否呈現線性關係 YES
    // TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值

    //(2720-640)/180 = 11.55 (degree/per_arget_data)
    if (target_angle>180) { return 3;}

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
/*================================================*/
