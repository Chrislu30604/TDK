// last modified by LiYu 2017.05.14
#ifndef __TDK_servo_H__
#define __TDK_servo_H__
#include <inttypes.h>

/*=== Servo Funtion Define ===============================*/
#define SERVO_GRIPPING 0
#define SERVO_ROTATING 1
/*========================================================*/

/*=== Servo funcion ======================================*/
uint8_t servo_set(uint8_t id,uint8_t target_angle);
/**
 * 設定指定編號之SERVO的角度
 * TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值 )
 *
 * target_angle 範圍 0~180 度
 *
 * return 0:沒問題, 1:wrong ID, 3:wrong target_angle
 */

void servo_init();
/**
 * 以大角度啟動所有SERVO，並復位至0度
 * 若直接以小角度啟動，有機會無法正確運作(原因忘了，知道得請補上)
 */
/*========================================================*/

#endif
