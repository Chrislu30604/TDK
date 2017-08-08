// last modified by LiYu 2017.05.14
#ifndef __TDK_motor_H__
#define __TDK_motor_H__
#include <inttypes.h>

/*=== Motor Function Define ======================*/
#define PWM00_1_ASA_ID 1
#define PWM00_2_ASA_ID 2
#define PWM_2_ASA_ID 2
#define PWM_2_ASA_ID 2
#define PWM_2_ASA_ID 2
#define MOTOR_RIGHT 0
#define MOTOR_LEFT  1
#define MOTOR_Y 2 // up and down
#define MOTOR_Z 3 // stretching
/*================================================*/

/*=== Gereral Define =============================*/
#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

#define DISABLE 0
#define ENABLE  1
/*================================================*/

/*=== Motor Function Define ======================*/
#define ENA 1
#define PWM00_2_ASA_ID 2
#define PWM_2_ASA_ID 2
#define PWM_2_ASA_ID 2
#define PWM_2_ASA_ID 2
#define MOTOR_RIGHT 0
#define MOTOR_LEFT  1
#define MOTOR_Y 2 // up and down
#define MOTOR_Z 3 // stretching
/*================================================*/

/*================================================*/
// ID:1 channel 1  motor_ID 0
// ID:1 channel 2  motor_ID 1
// ID:2 channel 1  motor_ID 2
// ID:2 channel 2  motor_ID 3
// ID:3 channel 1  motor_ID 4
// ID:3 channel 2  motor_ID 5
// ID:4 channel 1  motor_ID 6
// ID:4 channel 2  motor_ID 7
// ID:5 channel 1  motor_ID 8
// ID:5 channel 2  motor_ID 9
// ID:6 channel 1  motor_ID 10
// ID:6 channel 2  motor_ID 11
// ID:7 channel 1  motor_ID 12
// ID:7 channel 2  motor_ID 13
/*================================================*/

/*=== Motor function==============================*/
uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data);
//
uint8_t motor_go_steps(uint8_t id, uint16_t steps);
void motor_check_steps(uint8_t id);
uint8_t motor_go_time(uint8_t id, uint32_t target_micro_secs);
void motor_check_time();
/*================================================*/



#endif
