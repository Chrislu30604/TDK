// last modified by LiYu 2017.05.14
#include "TDK_servo.h"
#include "ASA_Lib.h"
#include <inttypes.h>

/*=== Servo funcion ======================================*/

uint8_t servo_set(uint8_t id,uint8_t target_angle){
    // 0.00052643 (ms/per_val)
	// MG995
    // min pwmdata = 700  (? ms) 0 degree
    // max pwmdata = 3300 (? ms) 180 degree
    // 觀察 OCR-角度 或 ms-角度 是否呈現線性關係 YES
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
    // return 0:沒問題, 1:wrong ID, 3:wrong target_angle
}


void servo_init() {
    //以大角度啟動後復位到0度
    servo_set(SERVO_GRIPPING,30);
    servo_set(SERVO_ROTATING,30);
    _delay_ms(500);
    servo_set(SERVO_GRIPPING,0);
    servo_set(SERVO_ROTATING,0);
}

/*========================================================*/
