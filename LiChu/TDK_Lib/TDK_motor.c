// last modified by LiYu 2017.05.14
#include "TDK_motor.h"
#include "ASA_Lib.h"
#include "TDK_external.h"
#include <inttypes.h>

/*=== Motor function==============================*/
uint16_t NEW_COUNTMOTOR_=0;
uint8_t  MOTOR_IS_ENABLE[4]={0};
uint16_t MOTOR_COUNT[4]={0};
uint16_t MOTOR_TARGET_STEPS[4]={0};
uint32_t MOTOR_TIME_ENABLE[4]={0};
uint32_t MOTOR_TIME_COUNT[4]={0};
uint32_t MOTOR_TIME_TARGET[4]={0};
uint32_t Time_Count = 0;
/*================================================*/

/*=== Motor function =============================*/
uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data) {
	uint8_t pwm_asa_id = 0;
	uint8_t pwm_channel = 0;
	uint8_t check = 0;

    pwm_asa_id  = motor_ID/2 + 1;
    pwm_channel = motor_ID%2;

	// mode 0:開關PWM, 1:正轉, 2:反轉
	switch (mode) {
		case 0:
			if (data!=0 && data!=1) { return 3; }
			check = ASA_PWM00_set(pwm_asa_id, 200, (1<<pwm_channel) , (1<<pwm_channel) , data );
			if (check!=0) { return 10+check; }
			break;
		case 1:
			if (data>511) { return 3; }
			data = 511-data;
			check = ASA_PWM00_put(pwm_asa_id, pwm_channel*2-2, 2, &data);
			if (check!=0) { return 10+check; }
			break;
		case 2:
			if (data>=511) { return 3; }
			data = data+512;
			check = ASA_PWM00_put(pwm_asa_id, pwm_channel*2-2, 2, &data);
			if (check!=0) { return 10+check; }
			break;
		default:
			return 2;
	}

	return 0;
	// return 0:沒問題, 1:wrong ID, 2:wrong mode, 3:wrong data, 1x:ASA_PWM錯誤 X為PWM錯誤代碼
}

uint8_t motor_go_steps(uint8_t id, uint16_t steps){
    /* TODO */

	motor_set(id,0,ENABLE);
	MOTOR_IS_ENABLE[id]=1;
	MOTOR_COUNT[id]=0;
	MOTOR_TARGET_STEPS[id]=steps;

	// mode 3:rising edge trigger
	EXT_INT_set(7-id,3);

	return 0;
}

void motor_check_steps(uint8_t id) {
    // 放入外部中斷，
    // 或放入計時中斷，但要保證取樣頻率>訊號頻率*2
	if (MOTOR_IS_ENABLE[id]) {
		if ( MOTOR_COUNT[id] >= MOTOR_TARGET_STEPS[id] ) {
			// 計算步數大於預期步數，則停止馬達，終止計數
			motor_set(id,0,DISABLE);
			MOTOR_IS_ENABLE[id]=0;
			EXT_INT_cls(7-id);
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

/*=== INT_vect ===================================*/
// ISR(INT4_vect){
// 	motor_check_steps(MOTOR_Z);
// }
// ISR(INT5_vect){
// 	motor_check_steps(MOTOR_Y);
// }
// ISR(INT6_vect){
// 	motor_check_steps(MOTOR_LEFT);
// }
// ISR(INT7_vect){
// 	motor_check_steps(MOTOR_RIGHT);
// }
/*================================================*/
