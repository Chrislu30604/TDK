
void motor_check_steps(uint8_t id) {
	// printf("--\n");
    if ( MOTOR_COUNT[id] >= MOTOR_TARGET_STEPS[id] ) {
        // 計算步數大於預期步數，則停止馬達，終止計數
        motor_set(id,0,DISABLE);
        MOTOR_IS_ENABLE[id] = 0;
    } else if ( MOTOR_IS_ENABLE[id] ) {
        if ( MOTOR_LAST_STATUS==1 && motor_now_status ==0 ) {

        } else if ( MOTOR_LAST_STATUS==0 && motor_now_status ==1 ) {
            MOTOR_COUNT[id]++;
            // printf("%d\n", MOTOR_COUNT[id]);
        }
    } else {

    }
    MOTOR_LAST_STATUS = motor_now_status;
}


// MOTOR_COUNT
// MOTOR_TARGET_STEPS
// MOTOR_LAST_STATUS

// motor_now_status
