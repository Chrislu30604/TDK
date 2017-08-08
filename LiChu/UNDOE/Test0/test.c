/*
 * Last modify at 2016.10.25 2pm bu LiYu
 * Just take care of the HL to the PWM00
 */
#include "ASA_Lib.h"

/*=== Servo Funtion Define ===============================*/
#define SERVO_GRIPPING 0
#define SERVO_ROTATING 1
/*========================================================*/




/*=== Motor Function Define ======================*/
#define PWM_1_ASA_ID 1
#define PWM_2_ASA_ID 2
#define MOTOR_RIGHT 0
#define MOTOR_LEFT  1
#define MOTOR_Y 2 // up and down
#define MOTOR_Z 3 // stretching
/*================================================*/

/*=== Timer3 function ====================================*/
void TIMER3_init();
/*========================================================*/

/*=== Servo funcion ======================================*/
void servo_init();
uint8_t servo_set(uint8_t id,uint8_t target_angle);
// TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值 )
/*========================================================*/
/*=== Timer2 Function ============================*/
void TIMER2_init();
void TIMER2_OVF_reg (void (*function)(void));
void (*TIMER2_OVF_fun)()=0;
/*================================================*/



/*=== Motor function==============================*/
uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data);
uint8_t motor_go_steps(uint8_t id, uint16_t steps);
void motor_check_steps(uint8_t id);
uint8_t motor_go_time(uint8_t id, uint32_t target_micro_secs);
void motor_check_time();
/*================================================*/

void go_ahead(uint32_t target_micro_secs);


uint16_t NEW_COUNT=0;
uint8_t  MOTOR_IS_ENABLE[4]={0};
uint16_t MOTOR_COUNT[4]={0};
uint16_t MOTOR_TARGET_STEPS[4]={0};
uint32_t MOTOR_TIME_ENABLE[4]={0};
uint32_t MOTOR_TIME_COUNT[4]={0};
uint32_t MOTOR_TIME_TARGET[4]={0};
uint32_t Time_Count = 0;

uint32_t Motor_Y_position = 0;

uint8_t S1,S2,S3,S4,S5;

int main(void)
{
	ASA_M128_set();
	printf("Motor test by LiYu 16.10.10\n");

	uint8_t  check = 0;
	uint16_t pwm_data=0;
	// PORTE_init();

	TIMER3_init();
	servo_init();

	check = motor_set(MOTOR_RIGHT,0,ENABLE);
	printf("%d\n", check);
	check = motor_set(MOTOR_LEFT, 0,ENABLE);
	printf("%d\n", check);
	check = motor_set(MOTOR_Y, 0,ENABLE);
	printf("%d\n", check);
	check = motor_set(MOTOR_RIGHT,1,0);
	printf("%d\n", check);
	check = motor_set(MOTOR_LEFT, 1,0);
	printf("%d\n", check);
	check = motor_set(MOTOR_Y,1,0);
	printf("%d\n", check);

	char data=0;

	// int id,mode,data;
	// while (1) {
	// 	printf("\nID:");
	// 	scanf("%d", &id);
	// 	printf("\nMode:");
	// 	scanf("%d", &mode);
	// 	printf("\nData:");
	// 	scanf("%d", &data);
	// 	check = motor_set(id, mode,data);
	// 	printf("\ncheck=%d\n", check);
	// }

	uint16_t target_cycle = 0,way = 0,id=0;
	uint16_t teeth = 1; //原24 減掉鑽孔處偵測為23
	uint32_t target_time = 0;

	PORTE_init();
	TIMER2_init();
	cli();
	// sei();

	check = motor_set(MOTOR_RIGHT,0,ENABLE);
	printf("%d\n", check);
	check = motor_set(MOTOR_LEFT, 0,ENABLE);
	printf("%d\n", check);
	check = motor_set(MOTOR_Y, 0,ENABLE);
	printf("%d\n", check);
	check = motor_set(MOTOR_RIGHT,1,0);
	printf("%d\n", check);
	check = motor_set(MOTOR_LEFT, 1,0);
	printf("%d\n", check);
	check = motor_set(MOTOR_Y,1,0);
	printf("%d\n", check);

	while (1) {

		DIO_fgt(2,0xFF,0,&data);
		S1 = !( (data>>3) & 1);
		S2 = !( (data>>4) & 1);
		S3 = !( (data>>5) & 1);
		S4 = !( (data>>6) & 1);
		S5 = !( (data>>7) & 1);

		printf("%d %d %d\n",S2,S3,S4);

		if ( !S2 && S3 && !S4) {
			// 直走
			check = motor_set(MOTOR_RIGHT,1,500);
			check = motor_set(MOTOR_LEFT ,1,500);
		}
		if ( S2 && S3 && !S4) {
			// 左轉
			check = motor_set(MOTOR_RIGHT,1,0);
			check = motor_set(MOTOR_LEFT ,1,500);
		}
		if ( S2 && !S3 && !S4) {
			// 左轉
			check = motor_set(MOTOR_RIGHT,1,0);
			check = motor_set(MOTOR_LEFT ,1,500);
		}
		if ( !S2 && S3 && S4) {
			// 右轉
			check = motor_set(MOTOR_RIGHT,1,500);
			check = motor_set(MOTOR_LEFT ,1,0);
		}
		if ( !S2 && !S3 && S4) {
			// 右轉
			check = motor_set(MOTOR_RIGHT,1,500);
			check = motor_set(MOTOR_LEFT ,1,0);
		}
		if ( S2 && S3 && S4) {
			// 到T字形
			check = motor_set(MOTOR_RIGHT,1,0);
			check = motor_set(MOTOR_LEFT ,1,0);
			_delay_ms(2000);
			check = motor_set(MOTOR_LEFT ,1,500);
			check = motor_set(MOTOR_RIGHT,1,500);
			_delay_ms(5000);
			check = motor_set(MOTOR_RIGHT,1,0);
			check = motor_set(MOTOR_LEFT ,1,0);
			_delay_ms(500);
			servo_set(SERVO_GRIPPING,180);
			_delay_ms(1000);
			check = motor_set(MOTOR_LEFT ,2,500);
			check = motor_set(MOTOR_RIGHT,2,500);
			_delay_ms(3000);
			break;



		}

	}
}
/*================================================*/

void PORTE_init() { //initialize PORTE 4~7 bits
	DDRE  = 0xF0;
	PORTE = 0xF0;
}




void go_ahead(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,1,500);
	motor_set(MOTOR_LEFT, 1,500);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}
void go_up(uint8_t way,uint32_t target_micro_secs) {
	motor_set(MOTOR_Y,1+way,200);
	motor_go_time(MOTOR_Y,target_micro_secs);
}
void turn_right(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,2,300);
	motor_set(MOTOR_LEFT, 1,300);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
 	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}
void turn_left(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,1,300);
	motor_set(MOTOR_LEFT, 2,300);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
 	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}
//一秒前進約30cm
//2s : 555  mm
//3s : 840  mm
//4s : 1071 mm


/*=== Servo funcion ======================================*/
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
    // printf("%d\n", target_data);
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
/*========================================================*/
