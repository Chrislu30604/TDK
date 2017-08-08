// last modified by LiYu 2017.05.14
#ifndef __TDK_timer_H__
#define __TDK_timer_H__

/*=== Timer3 function ====================================*/
void TIMER3_init();
/** FAST PWM mode, NON Inverted PWM
 * fPWM=50Hz (Period = 20ms Standard)
 * set PE4, PE5 as output for servo
 */
/*========================================================*/

/*=== Timer2 Function ====================================*/
void TIMER2_init();
/** CTC mode, no output PWM
 * f = 1005 hz
 */
/*========================================================*/

#endif
