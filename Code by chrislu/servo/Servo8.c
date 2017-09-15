#include "ASA_Lib.h"
 
int main(int argc, char const *argv[]) {
    
    ASA_M128_set();
    char ASA_ID = 1;
    char data[8] = {0,32,64,96,128,160,192,224};
    char chk = 0;
    char char_data=128;
    int input=0;
    printf("Start!\n");
    while (1) {
 
        chk = ASA_PWM01_put(ASA_ID, 0, 1, &char_data);
        printf("put_chk %d\n", chk);
        chk = ASA_PWM01_set(ASA_ID, 200, 0xff, 0, 0x01);
        printf("set_chk %d\n", chk);
        scanf("%d",&input);
        char_data = input;
    }
 
 
 
    return 0;
}