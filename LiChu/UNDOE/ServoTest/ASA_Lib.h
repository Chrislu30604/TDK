/*===============ASA Series Library===============*/

/*****ReleaseDate*****/
//2015/12/1

/*****Feature*****/

/*===Supported Module===*/
//ASA M128
//ASA 7S00
//ASA ACC00
//ASA ADC00
//ASA DAC00
//ASA DIO00
//ASA GR00
//ASA KB00
//ASA PWM00
//ASA PWM01
//ASA RF00
//ASA RTC00
//ASA SDC00
//ASA STP00
//ASA THM00
//ASA THM01

/*================================================*/

#ifndef __ASA_H__
#define __ASA_H__

#include <avr\io.h>
#include <avr\interrupt.h>
#include <stdio.h>
#include <util\delay.h>

#define M128_AllINT_enable sei()
#define M128_AllINT_disable cli()

/**M128**/
char ASA_M128_set(void);
char DIO_fpt(char LSByte, char Mask, char shift, char Data);
char DIO_fgt(char LSByte, char Mask, char shift, char *Data_p);
char TIM_set(void);
char TIMISR_reg(void (*function)(void));
char HMI_Transceiver_put(char Bytes, void *Data_p);
char HMI_Transceiver_get(char Bytes, void *Data_p);

/**7S00**/
char ASA_7S00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_7S00_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);
char ASA_7S00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**ACC00**/
char ASA_ACC00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_ACC00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**ADC00**/
char ASA_ADC00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_ADC00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**DAC00**/
char ASA_DAC00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_DAC00_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);
char ASA_DAC00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**DIO00**/
char ASA_DIO00_put(char ASA_ID, char LSByte, char Bytes, void* Data_p);
char ASA_DIO00_get(char ASA_ID, char LSByte, char Bytes, void* Data_p);
char ASA_DIO00_fpt(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_DIO00_fgt(char ASA_ID, char LSByte, char Mask, char shift, void *Data_p);

/**GR00**/
char ASA_GR00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_GR00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**KB00**/
char ASA_KB00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_KB00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**PWM00**/
char ASA_PWM00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_PWM00_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);
char ASA_PWM00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**PWM01**/
char ASA_PWM01_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_PWM01_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);
char ASA_PWM01_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**RF00**/
char ASA_RF00_put(char ASA_ID,char LSByte,char Bytes,void *Data_p);
char ASA_RF00_get(char ASA_ID,char LSByte,char Bytes,void *Data_p);

/**RTC00**/
char ASA_RTC00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_RTC00_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);
char ASA_RTC00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**SDC00**/
char ASA_SDC00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_SDC00_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);
char ASA_SDC00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**STP00**/
char ASA_STP00_put(char ASA_ID, char LSByte,char Bytes,void  *Data_p);

/**THM00**/
char ASA_THM00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_THM00_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

/**THM01**/
char ASA_THM01_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_THM01_get(char ASA_ID, char LSByte, char Bytes, void *Data_p);

#endif
