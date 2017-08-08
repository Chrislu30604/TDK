/*===Detect_Road===== Create by ChrisLu 2017.08.01=====*/
#include <inttypes.h>
#define ENABLE 1
#define DISABLE 0
/*==========Function Define===============*/
uint8_t motor_set(uint8_t motorPin, uint8_t mode, uint16_t speeds)
void Road_Detect();
void interruptDetect0();
void interruptDetect1();
void interruptDetect2();
void interruptDetect3();
uint8_t transMotorToId(uint8_t motorPin);
uint8_t motor_go_steps(uint8_t motorPin, uint16_t steps);
void motor_check_steps(uint8_t motorPin);

unsigned char sensor1 = 2;
unsigned char sensor2 = 3;
unsigned char sensor3 = 20;
unsigned char sensor4 = 21;
unsigned char sensor5 = 19;

unsigned char LeftWheelPwmPin  = 10; 
unsigned char RightWheelPwmPin = 11; 
unsigned char ZwheelPin = 4;
unsigned char YwheelPin = 5;
unsigned char LeftInterrupt = 2;
unsigned char RightInterrupt = 3; 

uint16_t target_mm = 0;
boolean sensor[5] = {0};           //五個循軌光遮斷
uint8_t  MOTOR_IS_ENABLE[4]={0};   //四顆馬達
uint16_t MOTOR_COUNT[4]={0};
uint16_t MOTOR_TARGET_STEPS[4]={0};
void setup()
{
  Serial.begin(9600);
  Serial.println("==Begin detect Road=== \n");
  /*===Initialize===*/
  //呼叫PINMODE = OUT_PUT
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  motor_set(LeftWheelPwmPin, 0, ENABLE); 
  motor_set(RightWheelPwmPin,0, ENABLE);
}
/************************************************/
void loop()
{
  Road_Detect();
}
/************************************************/


void Road_Detect(){
  sensor[0] = digitalRead(sensor1);
  sensor[1] = digitalRead(sensor2);
  sensor[2] = digitalRead(sensor3);
  sensor[3] = digitalRead(sensor4);
  sensor[4] = digitalRead(sensor5);
  if(sensor[1] && sensor[2] && sensor[3] && 1){
    motor_set(LeftWheelPwmPin, 1, 255);
    motor_set(RightWheelPwmPin,1 ,255);
  } //直走
  if (!sensor[1]&&  sensor[2] && !sensor[3] &&1){
    motor_set(LeftWheelPwmPin, 1, 255);
    motor_set(RightWheelPwmPin,1 ,255);
  } //直走
  if (!sensor[1] &&  sensor[2]&&  sensor[3] &&1){
    motor_set(LeftWheelPwmPin, 1, 255);
    motor_set(RightWheelPwmPin,2 ,255);
  } //右轉
  if (!sensor[1] && !sensor[2] &&  sensor[3]&&1){
    motor_set(LeftWheelPwmPin, 1, 255);
    motor_set(RightWheelPwmPin,2 ,255);
  } //右轉
  if ( sensor[1] &&  sensor[2] && !sensor[3]&&1){
    motor_set(LeftWheelPwmPin, 2, 255);
    motor_set(RightWheelPwmPin,1 ,255);
  } //左轉
  if ( sensor[1] && !sensor[2] && !sensor[3]&&1){
    motor_set(LeftWheelPwmPin, 2, 255);
    motor_set(RightWheelPwmPin,1 ,255);
  } //左轉
  if (sensor[0] && sensor[1] && sensor[2] && sensor[3]&& sensor[4]&&1){
    motor_set(LeftWheelPwmPin, 1, 0);
    motor_set(RightWheelPwmPin,1 ,0);
  } //停止
}
uint8_t motor_set(uint8_t motorPin, uint8_t mode, uint16_t speeds){
  // mode 0:開關PWM, 1:正轉, 2:反轉
  // speed 0~255
  switch(mode){
    case 0:
      if(speeds!=0 && speeds!=1) {return 3;}
      pinMode((motorPin + 2), speeds);    //開關
      break;
    case 1:
        digitalWrite((motorPin + 2),  1);
        analogWrite(motorPin, speeds);
        break;
    case 2:
        digitalWrite((motorPin + 2),  0);
        analogWrite(motorPin, speeds);
        break;
    default:
        return 2;
    } 
    return 0;
    // return 0:沒問題, 1:wrong ID, 2:wrong mode, 3:wrong data,

}

/*============================================目標步數函示庫=========================*/
void interruptDetect0(){
  motor_check_steps(LeftWheelPwmPin);
}
void interruptDetect1(){
  motor_check_steps(RightWheelPwmPin);
}
void interruptDetect2(){
  motor_check_steps(ZwheelPin);
}
void interruptDetect3(){
  motor_check_steps(YwheelPin);
}

uint8_t transMotorToId(uint8_t motorPin){
  switch(motorPin){
    case 10:
        attachInterrupt(0, interruptDetect0, CHANGE); //PWM開關
      return 0;
      break;
    case 11:
        attachInterrupt(1, interruptDetect1, CHANGE);
        return 1;
        break;
    case 4 :
        attachInterrupt(2, interruptDetect2, CHANGE);
        return 2;
        break;
    case 5 :
        attachInterrupt(3, interruptDetect3, CHANGE);
        return 3;
        break;
    default :
        break;
  }
  return 0;
}

uint8_t motor_go_steps(uint8_t motorPin, uint16_t steps){
    /* Steps : 目標步數*/
    uint8_t id = transMotorToId(motorPin);
  motor_set(motorPin, 0, 1);
  MOTOR_IS_ENABLE[id] = 1;
  MOTOR_COUNT[id] = 0;
  MOTOR_TARGET_STEPS[id]=steps;

  return 0;
}

void motor_check_steps(uint8_t motorPin) {
  // 放入外部中斷
  uint8_t id = transMotorToId(motorPin);
  if (MOTOR_IS_ENABLE[id]) {
    if ( MOTOR_COUNT[id] >= MOTOR_TARGET_STEPS[id] ) {
      // 計算步數大於預期步數，則停止馬達，終止計數
      motor_set(motorPin, 0, 0);
      MOTOR_IS_ENABLE[id] = 0;
      detachInterrupt(id);
    } else if ( MOTOR_IS_ENABLE[id] ) {
      MOTOR_COUNT[id]++;
    } else {

    }
  }
}
