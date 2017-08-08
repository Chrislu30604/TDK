/*
 * Last modify at 2016.10.25 2pm bu LiYu
 * Just take care of the HL to the PWM00
 */
#include "ASA_Lib.h"

/*=== Gereral Define =============================*/
#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

#define DISABLE 0
#define ENABLE  1
/*================================================*/

/*=== Motor Function Define ======================*/
#define PWM_1_ASA_ID 1
#define PWM_2_ASA_ID 2
#define MOTOR_RIGHT 0
#define MOTOR_LEFT  1
#define MOTOR_Y 2 // up and down
#define MOTOR_Z 3 // stretching
/*================================================*/

/*=== Timer2 Function ============================*/
void TIMER2_init();
void TIMER2_OVF_reg (void (*function)(void));
void (*TIMER2_OVF_fun)()=0;
/*================================================*/

/*=== INT function ===============================*/
void PORTE_init();
void INT_set(char INT_num,char mode);
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

int main(void)
{
	ASA_M128_set();
	printf("Motor test by LiYu 16.10.10\n");

	uint8_t  check = 0;
	uint16_t pwm_data=0;
	// PORTE_init();

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

	while (1) {
		printf("\ninput target_steps:");
		scanf("%d",&target_time);
		// printf("\ninput way:");
		// scanf("%d",&way);
		// printf("\ninput way:");
		// scanf("%d",&way);
		// printf("\ninput id:");
		// scanf("%d",&id);
		sei();
		go_ahead(target_time);

		printf("\ninput target_steps:");
		scanf("%d",&target_time);
		turn_left(target_time);

		printf("\ninput target_steps:");
		scanf("%d",&target_time);
		turn_left(target_time);


		// go_up(way,target_time);

		// check = motor_set(id,way,500);
		// printf("%d\n", check);
		//
		// motor_go_steps(id,target_cycle);
		// motor_go_time(id,target_cycle);
	}
}
/*================================================*/

void PORTE_init() { //initialize PORTE 4~7 bits
	DDRE  = 0xF0;
	PORTE = 0xF0;
}

/*=== INT function ===============================*/
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
/*================================================*/

/*=== INT_vect ===================================*/
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
/*================================================*/

/*=== Timer2 Function ============================*/
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
	printf("TCCR2 = %d, TIMSK = %d\n", TCCR2, TIMSK);
}
void TIMER2_OVF_reg (void (*function)(void)){
	TIMER2_OVF_fun=function;
}
/*================================================*/

/*=== Motor function =============================*/
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
	printf("--\n");
	if (MOTOR_IS_ENABLE[id]) {
		if ( MOTOR_COUNT[id] >= MOTOR_TARGET_STEPS[id] ) {
			// 計算步數大於預期步數，則停止馬達，終止計數
			motor_set(id,0,DISABLE);
			MOTOR_IS_ENABLE[id]=0;
			INT_cls(7-id);
		} else if ( MOTOR_IS_ENABLE[id] ) {
			MOTOR_COUNT[id]++;
			printf("%d\n", MOTOR_COUNT[id]);
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
/*================================================*/

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
