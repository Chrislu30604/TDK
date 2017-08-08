#include "ASA_Lib.h"

/*=== Servo Funtion Define ===============================*/
#define SERVO_GRIPPING 0
#define SERVO_ROTATING 1
/*========================================================*/

/*=== Timer3 function ====================================*/
void TIMER3_init();
/*========================================================*/

/*=== Servo funcion ======================================*/
void servo_init();
uint8_t servo_set(uint8_t id,uint8_t target_angle);
// TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值 )
/*========================================================*/

/*=== Gereral Define =====================================*/
#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

#define DISABLE 0
#define ENABLE  1
/*========================================================*/

/*=== Motor Function Define ==============================*/
#define PWM_1_ASA_ID 1
#define PWM_2_ASA_ID 2
#define MOTOR_RIGHT 0
#define MOTOR_LEFT  1
#define MOTOR_Y 2 // up and down
#define MOTOR_Z 3 // stretching
/*========================================================*/

/*=== Timer2 Function ====================================*/
void TIMER2_init();
void TIMER2_OVF_reg (void (*function)(void));
void (*TIMER2_OVF_fun)()=0;
/*========================================================*/

/*=== INT function =======================================*/
void PORTE_init();
void INT_set(char INT_num,char mode);
/*========================================================*/

/*=== Motor function======================================*/
uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data);
uint8_t motor_go_steps(uint8_t id, uint16_t steps);
void motor_check_steps(uint8_t id);
uint8_t motor_go_time(uint8_t id, uint32_t target_micro_secs);
void motor_check_time();
/*========================================================*/

/*=== Matlab function ====================================*/
void matlab_start_point(uint16_t* data);
void matlab_end();
void matlab_get_coke_info(uint16_t* position,uint16_t* distance);
void matlab_get_rear_road_info(uint16_t* data,uint16_t* x,uint16_t* y);
void matlab_get_front_road_info(uint16_t* data,uint16_t* x,uint16_t* y);
/*========================================================*/

/*=== Robot function =====================================*/
void robot_go_ahead(uint32_t target_micro_secs);
void robot_go_back(uint32_t target_micro_secs);
void robot_turn_right(uint32_t target_micro_secs);
void robot_turn_left(uint32_t target_micro_secs);
void robot_go_up(uint32_t target_micro_secs);
void robot_go_down(uint32_t target_micro_secs);

void robot_go_ahead_feedback(uint16_t front_x,uint16_t rear_x,uint16_t deg);
/*========================================================*/


uint16_t NEW_COUNT=0;
uint8_t  MOTOR_IS_ENABLE[4]={0};
uint16_t MOTOR_COUNT[4]={0};
uint16_t MOTOR_TARGET_STEPS[4]={0};
uint32_t MOTOR_TIME_ENABLE[4]={0};
uint32_t MOTOR_TIME_COUNT[4]={0};
uint32_t MOTOR_TIME_TARGET[4]={0};
uint32_t Time_Count = 0;

uint32_t Motor_Y_position = 0;

/*=== Main ===============================================*/
int main()
{
    ASA_M128_set();

    /*=== init ===========================================*/
    TIMER3_init();
    TIMER2_init();
    servo_init();

	motor_set(MOTOR_RIGHT,0,ENABLE);
	motor_set(MOTOR_LEFT, 0,ENABLE);
	motor_set(MOTOR_Y, 0,ENABLE);
	motor_set(MOTOR_RIGHT,1,0);
	motor_set(MOTOR_LEFT, 1,0);
	motor_set(MOTOR_Y,1,0);
    /*=== init ===========================================*/

    /*=== start ==========================================*/
    uint16_t start_point = 0, deg = 0;
    uint16_t rear_deg=0 , rear_x=0 , rear_y=0;
    uint16_t front_deg=0 , front_x=0 , front_y=0;
    matlab_start_point(&start_point);
    sei();

    switch (start_point) {

        //一秒前進約30cm
        //2s : 555  mm
        //3s : 840  mm
        //4s : 1071 mm

        case 1:{ //走到冰箱
            // 12s 290cm
            robot_turn_left(1700);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(12000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                matlab_get_rear_road_info(&rear_deg,&rear_x,&rear_y);
                matlab_get_front_road_info(&front_deg,&front_x,&front_y);
                deg = (rear_deg + front_deg)/2;

                // robot_go_ahead_feedback(front_x,rear_x,deg);
                // matlab_get_front_deg(&deg_front)
                // printf("---\n" );
                _delay_ms(3000);
            }
            // matlab_end();
        }
        case 2:{ //轉彎
            robot_turn_right(3400);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(2500);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_turn_right(7000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(1950);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            servo_set(SERVO_GRIPPING,180);
            _delay_ms(2000);
            robot_go_back(1500);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            matlab_end();
            break;
        }
        case 3:{
            robot_go_ahead(2500);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_turn_right(3000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_go_ahead(2500);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_turn_right(3800);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }

            matlab_end();
        }

        case 5:{
            servo_set(SERVO_GRIPPING,180);
            _delay_ms(2000);
            robot_go_back(2500);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            matlab_end();
        }
        case 6:{
            robot_turn_right(1750);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(2000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_turn_right(1800);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            matlab_end();
        }
        case 7:{
            robot_go_ahead(10000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_turn_right(1750);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(2000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_turn_right(1800);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(2000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            matlab_end();
        }

        case 8:{
            robot_go_ahead(2800);//145cm/2
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_turn_right(3200);//83deg
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(6100);//177cm
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_turn_left(3200);//
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_up(7241);//210cm
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
        }

        case 9:{
            robot_go_ahead(7241);//210cm
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_turn_left(3200);//83deg
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_ahead(6100);//177cm
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            robot_turn_right(3200);//
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
            robot_go_up(4862);//141cm
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
        }
        case 10:{
            robot_turn_right(3400);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }

            robot_go_ahead(14000); //290cm
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                printf("--\n");
                _delay_ms(400);
            }
        }

        case 21:{
            servo_set(SERVO_GRIPPING,170);
            _delay_ms(2000);
            matlab_end();
            break;
        }
        case 22:{
            servo_set(SERVO_ROTATING,110);
            _delay_ms(2000);
            servo_set(SERVO_ROTATING,0);
            matlab_end();
            break;
        }
        case 23:{
            servo_set(SERVO_ROTATING,130);
            _delay_ms(2000);
            servo_set(SERVO_ROTATING,0);
            matlab_end();
            break;
        }
        case 24:{
            servo_set(SERVO_ROTATING,130);
            _delay_ms(2000);
            servo_set(SERVO_ROTATING,0);
            matlab_end();
            break;
        }

        case 99:{
            robot_go_up(10000);
            while (MOTOR_TIME_ENABLE[MOTOR_LEFT] && MOTOR_TIME_ENABLE[MOTOR_RIGHT]) {
                _delay_ms(400);
            }
            matlab_end();
        }
    }
    /*=== start ==========================================*/


}
/*========================================================*/

/*=== Timer3 functioin ===================================*/
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
/*========================================================*/

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
void PORTE_init() { //initialize PORTE 4~7 bits
	DDRE  = 0xF0;
	PORTE = 0xF0;
}

/*=== INT function =======================================*/
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
/*========================================================*/

/*=== INT_vect ===========================================*/
ISR(INT4_vect){
	motor_check_steps(MOTOR_Z);
}
ISR(INT5_vect){
	motor_check_steps(MOTOR_Y);
}
ISR(INT6_vect){
	motor_check_steps(MOTOR_LEFT);
}
ISR(INT7_vect){
	motor_check_steps(MOTOR_RIGHT);
}
/*========================================================*/

/*=== Timer2 Function ====================================*/
ISR(TIMER2_COMP_vect){
	// 1單位為0.001ms , uint32_t 可記錄 2^32/1000/60/60 = 1193.04647hr
	Time_Count++;
	// printf("%d\n", Time_Count);
	motor_check_time();
	// TIMER2_OVF_fun();
}
void TIMER2_init(){
	TCCR2  = 0;
	TCCR2 |= (1<<WGM21) | (0<<WGM20); // CTC mode
	TCCR2 |= (0<<COM21) | (0<<COM20); // no Compare Output
    TCCR2 |= (0<<CS22)  | (1<<CS21) | (1<<CS20); // set up timer with prescaler = 64
    TCNT2  = 0;	// initialize counter
    TIMSK |= (1<<OCIE2) | (0<<TOIE2); // Output Compare Match Interrupt Enable
	OCR2 = 171; // f = 11059200/64/(1+171) = 1004.65116, see as 1000hz, err = 0.5%
	// printf("TCCR2 = %d, TIMSK = %d\n", TCCR2, TIMSK);
}
void TIMER2_OVF_reg (void (*function)(void)){
	TIMER2_OVF_fun=function;
}
/*========================================================*/

/*=== Motor function =====================================*/
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

uint8_t motor_go_steps(uint8_t id, uint16_t steps){
	motor_set(id,0,ENABLE);
	MOTOR_IS_ENABLE[id]=1;
	MOTOR_COUNT[id]=0;
	MOTOR_TARGET_STEPS[id]=steps;

	INT_set(7-id,3);

	return 0;
}

void motor_check_steps(uint8_t id) {
	// printf("--\n");
	if (MOTOR_IS_ENABLE[id]) {
		if ( MOTOR_COUNT[id] >= MOTOR_TARGET_STEPS[id] ) {
			// 計算步數大於預期步數，則停止馬達，終止計數
			motor_set(id,0,DISABLE);
			MOTOR_IS_ENABLE[id]=0;
			INT_cls(7-id);
		} else if ( MOTOR_IS_ENABLE[id] ) {
			MOTOR_COUNT[id]++;
			// printf("%d\n", MOTOR_COUNT[id]);
		} else {

		}
	}

}
uint8_t motor_go_time(uint8_t id, uint32_t target_micro_secs){
	motor_set(id,0,ENABLE);
	MOTOR_TIME_ENABLE[id]=1;
	MOTOR_TIME_COUNT[id]=0;
	MOTOR_TIME_TARGET[id]=target_micro_secs;

	return 0;
}

void motor_check_time() {
	for (uint8_t id = 0; id < 4; id++) {
		if (MOTOR_TIME_ENABLE[id] == ENABLE) {
			if ( MOTOR_TIME_COUNT[id] >= MOTOR_TIME_TARGET[id] ) {
				motor_set(id,0,DISABLE);
				MOTOR_TIME_ENABLE[id]=0;
				// printf("END----\n");
			}else if ( MOTOR_TIME_ENABLE[id] == ENABLE) {
				MOTOR_TIME_COUNT[id]++;
				// printf("id = %d ----%ld,%ld\n", id, MOTOR_TIME_COUNT[id], MOTOR_TIME_TARGET[id]);
			}
		}
	}
}
/*========================================================*/

/*=== Robot function =====================================*/
void robot_go_ahead(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,1,500);
	motor_set(MOTOR_LEFT, 1,500);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}
void robot_go_back(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,2,500);
	motor_set(MOTOR_LEFT, 2,500);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}
void robot_go_up(uint32_t target_micro_secs) {
	motor_set(MOTOR_Y,1,200);
	motor_go_time(MOTOR_Y,target_micro_secs);
}
void robot_go_down(uint32_t target_micro_secs) {
	motor_set(MOTOR_Y,2,200);
	motor_go_time(MOTOR_Y,target_micro_secs);
}
void robot_turn_right(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,2,300);
	motor_set(MOTOR_LEFT, 1,300);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
 	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}
void robot_turn_left(uint32_t target_micro_secs) {
	motor_set(MOTOR_RIGHT,1,300);
	motor_set(MOTOR_LEFT, 2,300);
	motor_go_time(MOTOR_RIGHT,target_micro_secs);
 	motor_go_time(MOTOR_LEFT ,target_micro_secs);
}

void robot_go_ahead_feedback(uint16_t front_x,uint16_t rear_x,uint16_t deg){
    if ( front_x >0 && rear_x >0) {
        if (deg < -1000) {
            motor_set(MOTOR_RIGHT,1,200);
            motor_set(MOTOR_LEFT, 2,500);
        } else if (deg >= -1000 && deg < -500) {
            motor_set(MOTOR_RIGHT,1,300);
            motor_set(MOTOR_LEFT, 2,500);
        } else if (deg >= -500 && deg < -100) {
            motor_set(MOTOR_RIGHT,1,400);
            motor_set(MOTOR_LEFT, 2,500);
        } else if (deg >= -100 && deg < 100) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 2,500);
            if( front_x >100){
                motor_set(MOTOR_LEFT, 2,500);
                motor_set(MOTOR_RIGHT,1,400);
            }
        } else if (deg >= 100 && deg < 500) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 2,500);
        } else if (deg >= 500 && deg < 1000) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 2,500);
        } else if (deg >= 1000) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 2,400);
        } else {
        }
    }
    else if ( front_x <0 && rear_x <0) {
        if (deg < -1000) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,400);
        } else if (deg >= -1000 && deg < -500) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,500);
        } else if (deg >= -500 && deg < -100) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,500);
        } else if (deg >= -100 && deg < 100) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,500);
            if( front_x <-100){
                motor_set(MOTOR_LEFT, 1,400);
                motor_set(MOTOR_RIGHT,1,500);
            }
        } else if (deg >= 100 && deg < 500) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,400);
        } else if (deg >= 5 && deg < 10) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,300);
        } else if (deg >= 1000) {
            motor_set(MOTOR_RIGHT,1,500);
            motor_set(MOTOR_LEFT, 1,200);
        } else {
            /* code */
        }

    }
}
/*========================================================*/

/*=== Matlab function =====================================*/
void matlab_start_point(uint16_t* data) {
    printf("Start----------\n");
    scanf("%d", data);
}
void matlab_end() {
    printf("End------------\n");
}

void matlab_get_rear_road_info(uint16_t* data,uint16_t* x,uint16_t* y) {
    printf("RareInfo-------\n");
    scanf("%d", data);
    scanf("%d", x);
    scanf("%d", y);
}
void matlab_get_front_road_info(uint16_t* data,uint16_t* x,uint16_t* y) {
    printf("FrontInfo------\n");
    scanf("%d", data);
    scanf("%d", x);
    scanf("%d", y);
}
void matlab_get_micro_sec_1(uint16_t id,uint16_t* data) {
    printf("GetMicroSec----\n");
    printf("%02d-------------\n",id);
    scanf("%d", data);
}
void matlab_get_coke_info(uint16_t* position,uint16_t* distance) {
    /* code */
}
/*========================================================*/

/*=== Robot function =====================================*/
