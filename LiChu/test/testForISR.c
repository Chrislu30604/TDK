#include "..\TDK_Lib\ASA_Lib.h"
#include "..\TDK_Lib\TDK_LIB.h"
#include "..\TDK_Lib\TDK_timer.h"

#define ASA_PWM_ID 5
#define PWM_set_LSByte 200
#define PWM_put_PWM1_LSByte 0
#define PWM_put_PWM2_LSByte 2
#define PWM_Byte 2
#define PWM1Mask 0x01
#define PWM1Shift 0
#define Enable 1
#define disable 0

void INT_set(char INT_num,char mode);
void PORTA_init();
void timer2_init(void);

int COUNT=0;
int NEW_COUNT=0;
int tmp=0,last=0;

int main(int argc, char const *argv[])
{
    ASA_M128_set();
    printf("Start Test\n");
    unsigned int data = 800;
    int target_cycle = 0;
    int teeth = 23; 
    PORTA_init();
    timer2_init();
    ASA_PWM00_set(ASA_PWM_ID, PWM_set_LSByte, PWM1Mask, PWM1Shift, Enable);; //set PWM M1 enable
    M128_AllINT_enable;



    while (1) {
        printf("\ninput target_cycle:");
        scanf("%d",&target_cycle);
        data = 0;
        ASA_PWM00_put(ASA_PWM_ID, PWM_put_PWM1_LSByte, PWM_Byte, &data);
        COUNT = 0;
        while( COUNT <= target_cycle * teeth ){
            //do something here ,otherwise get a bug that no break out while
           printf("%d",COUNT);
           printf(" ");
        }
        printf("\nEND-------");
        data = 500;
        ASA_PWM00_put(ASA_PWM_ID, PWM_put_PWM1_LSByte, PWM_Byte, &data);
    }
}

void timer2_init(void){
   TCCR2 = 0x0A; //FOC2 WGM20 COM21 COM20 WGM21 CS22 CS21 CS20 = 0110 0001   N = 128

   //initialize counter
   OCR2  = 127;
   TIMSK = 0x40;  //0100 0000
   //TIMSK = 0x40;
   //TIFR = 0x40;

}


ISR(TIMER2_COMP_vect){
  tmp=(PINA&1);
  if(tmp!=last)
  COUNT++;

  last=tmp;
}