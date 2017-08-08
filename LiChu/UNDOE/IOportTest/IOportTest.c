/*
 * Last modify at 2016.10.25 3pm bu LiYu
 * Just take care of the HL to the PWM00
 */
#include "ASA_Lib.h"

/*=== Gereral Define ==================================*/
#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

#define DISABLE 0
#define ENABLE  1
/*=====================================================*/

/*=== Motor Function Define ===========================*/
#define PWM_1_ASA_ID 1
#define PWM_2_ASA_ID 2
#define MOTOR_RIGHT 0
#define MOTOR_LEFT  1
#define MOTOR_Y 2 // up and down
#define MOTOR_Z 3 // stretching
/*=====================================================*/

/*=== Servo Funtion Define ============================*/
#define SERVO_GRIPPING 0
#define SERVO_ROTATING 1
/*=====================================================*/

/*=== Timer3 function =================================*/
void TIMER3_init();
/*=====================================================*/

/*=== Servo funcion ===================================*/
void servo_init();
uint8_t servo_set(uint8_t id,uint8_t target_angle);
// TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值 )
/*=====================================================*/

/*=== Timer2 Function =================================*/
void TIMER2_OVF_init();
void TIMER2_OVF_reg (void (*function)(void));
void (*TIMER2_OVF_fun)()=0;
/*=====================================================*/

/*=== INT function ====================================*/
void PORTE_init();
void INT_set(char INT_num,char mode);
/*=====================================================*/

/*=== Motor function===================================*/
uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data);
uint8_t go_step(uint16_t steps); //TODO finish this function
void motor_count_steps(); 		 //TODO finish this function
/*=====================================================*/

uint16_t COUNT=0;
uint16_t NEW_COUNT=0;
uint16_t TARGET_STEPS=0;

/*=== Main ============================================*/
void main()
{
    ASA_M128_set();
	printf("IOportTest test by LiYu 16.10.05\n");
    TIMER3_init();
    servo_init();

    int check = 0;
    check = motor_set(MOTOR_RIGHT,0,ENABLE); printf("-1-%d\n", check);
    check = motor_set(MOTOR_LEFT, 0,ENABLE); printf("-2-%d\n", check);
    check = motor_set(MOTOR_RIGHT,1,0); printf("-3-%d\n", check);
    check = motor_set(MOTOR_LEFT, 1,0); printf("-4-%d\n", check);
    check = motor_set(MOTOR_RIGHT,0,DISABLE); printf("-5-%d\n", check);
    check = motor_set(MOTOR_LEFT, 0,DISABLE); printf("-6-%d\n", check);

    uint8_t data=0;
    uint8_t angel_1=0;
    uint8_t angel_2=0;
    uint8_t motor_status=0;
    while (1) {
        DIO_fgt(0,0xFF,0,&data);
        // printf("%d\n", data);

        if (data & 0x01) {
            if (angel_1>180) {
                angel_1=180;
            }else{
                angel_1++;
                servo_set( SERVO_GRIPPING , angel_1 );
                printf("01-%d\n",angel_1);
            }
        } else if (data & 0x02) {
            if (angel_1==0) {
                angel_1=1;
            }else{
            angel_1--;
            servo_set( SERVO_GRIPPING , angel_1 );
            printf("02-%d\n",angel_1);
            }
        }

        if (data & 0x40) {
            if (angel_2>180) {
                angel_2=180;
            }else{
                angel_2++;
                servo_set( SERVO_ROTATING , angel_2 );
                printf("10-%d\n",angel_2);
            }
        } else if (data & 0x80) {
            if (angel_2==0) {
                angel_2=1;
            }else{
                angel_2--;
                servo_set( SERVO_ROTATING , angel_2 );
                printf("20-%d\n",angel_2);
            }
        }

        if (data & 0x10) {
            motor_set(MOTOR_RIGHT,0,ENABLE);
            motor_set(MOTOR_RIGHT,1,500);
        } else if (data & 0x20) {
            motor_set(MOTOR_RIGHT,0,ENABLE);
            motor_set(MOTOR_RIGHT,2,500);
        }else{
            motor_set(MOTOR_RIGHT,0,DISABLE);
        }

        if (data & 0x04) {
            motor_set(MOTOR_LEFT, 0,ENABLE);
            motor_set(MOTOR_LEFT, 1,500);
        } else if (data & 0x08) {
            motor_set(MOTOR_LEFT, 0,ENABLE);
            motor_set(MOTOR_LEFT, 2,500);
        }else{
            motor_set(MOTOR_LEFT, 0,DISABLE);
        }
    }

}
/*=====================================================*/

/*=== Timer2 Function =================================*/
ISR(TIMER2_OVF_vect){
    TIMER2_OVF_fun();
}
void TIMER2_OVF_init(){
    TCCR2 |= 1;	// set up timer with prescaler = 2
    TCNT2  = 0;	// initialize counter
    TIMSK |=(1 << TOIE2);// enable overflow interrupt
    // sei(); // enable global interrupts
}
void TIMER2_OVF_reg (void (*function)(void)){
    TIMER2_OVF_fun=function;
}
/*=====================================================*/

/*=== Timer3 functioin ================================*/
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
/*=====================================================*/

/*=== INT function ====================================*/
void INT_set(char INT_num, char mode) {
	// mode 0:low level trigger
	// mode 1:logic change trigger
	// mode 2:falling edge
	// mode 3:rising trigger
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
void PORTE_init() { //initialize PORTE 4~7 bits
	DDRE  = 0xF0;
	PORTE = 0xF0;
}

ISR(INT4_vect){
	COUNT++;
}
/*=====================================================*/

/*=== Servo funcion ===================================*/
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
/*=====================================================*/

/*=== Motor function ==================================*/
uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data) {
	uint8_t pwm_asa_id = 0;
	uint8_t pwm_channel = 0;
	uint8_t check = 0;
	static uint8_t enable_status[2]={0};

	if (motor_ID == 0 || motor_ID == 1 ) {
		pwm_asa_id  = PWM_1_ASA_ID;
		pwm_channel = motor_ID+1;
	} else if (motor_ID == 2 || motor_ID == 3) {
		pwm_asa_id  = PWM_2_ASA_ID;
		pwm_channel = motor_ID-1;
	} else {
		return 1;
	}
	// TODO: 測量最低驅動波寬比為多少

	// mode 0:開關PWM, 1:正轉, 2:反轉
	switch (mode) {
		case 0:
			if (data!=0 && data!=1) { return 3; }
			if (data==0) {
				enable_status[pwm_asa_id-1] &= ~(1<<(pwm_channel-1));
			} else if (data==1) {
				enable_status[pwm_asa_id-1] |= 1<<(pwm_channel-1);
			}
			data = enable_status[pwm_asa_id-1];
			check = ASA_PWM00_set(pwm_asa_id, SET_START_LSBYTE,3,0, data);
			// printf("%d\n", enable_status[pwm_asa_id-1]);
			// printf("debug1 = %d,%d,%d,%d,%d\n",pwm_asa_id,SET_START_LSBYTE,(1<<(pwm_channel-1)),pwm_channel-1,data);
			// check = ASA_PWM00_set(pwm_asa_id, SET_START_LSBYTE, (1<<(pwm_channel-1)), pwm_channel-1, data);
			if (check!=0) { return 10+check; }
			break;
		case 1:
			if (data>511) { return 3; }
			data = 511-data;
			check = ASA_PWM00_put(pwm_asa_id, (PUT_START_LSBYTE + pwm_channel*2-2), 2, &data);
			// printf("debug2 = %d,%d,%d,%d\n",pwm_asa_id,(PUT_START_LSBYTE + pwm_channel*2 - 2),2,data);
			if (check!=0) { return 10+check; }
			break;
		case 2:
			if (data>=511) { return 3; }
			data = data+512;
			check = ASA_PWM00_put(pwm_asa_id, (PUT_START_LSBYTE + pwm_channel*2-2), 2, &data);
			// printf("debug3 = %d,%d,%d,%d\n",pwm_asa_id,(PUT_START_LSBYTE + pwm_channel*2 - 2),2,data);
			if (check!=0) { return 10+check; }
			break;
		default:
			return 2;
	}

	return 0;
	// return 0:沒問題, 1:wrong ID, 2:wrong mode, 3:wrong data, 1x:ASA_PWM錯誤 X為PWM錯誤代碼
}

uint8_t go_step(uint16_t steps){
	COUNT = 0;
	INT_set(4,3);
	TARGET_STEPS = steps;
	TIMER2_OVF_reg(motor_count_steps);
	motor_set(MOTOR_RIGHT,0,ENABLE);
	motor_set(MOTOR_LEFT, 0,ENABLE);
	return 0;
}

void motor_count_steps(){
	if (COUNT >= TARGET_STEPS) {
		TIMER2_OVF_reg(NULL);
	}
	motor_set(MOTOR_RIGHT,0,DISABLE);
	motor_set(MOTOR_LEFT, 0,DISABLE);
	return ;
}
/*=====================================================*/
