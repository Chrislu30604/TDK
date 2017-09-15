// last modified by LiYu 2017.05.14
#ifndef __TDK_external_H__
#define __TDK_external_H__

/*=== EXT_INT function ===============================*/
void EXT_INT_set(char INT_num,char mode);
/**
 * 設定外部中斷對應腳位 輸入
 * 並致能外部中斷
 *
 * INT_num : the External Interrupt number (INT 0~7)
 * mode 0:low level trigger
 * mode 1:logic change trigger
 * mode 2:falling edge trigger
 * mode 3:rising edge trigger
 *
 * 目前只有做 INT_num 4~7 (PE 4~7)部分
 * INT_num 0~3 (PD 0~3) 未測、未實作
 * TODO 測試並完成 INT0~3部分
 */
void EXT_INT_cls(char INT_num);
/**
 * 設定外部中斷對應腳位 輸出
 * 並關閉外部中斷
 *
 * 目前只有做 INT_num 4~7 (PE 4~7)部分
 * INT_num 0~3 (PD 0~3) 未測、未實作
 * TODO 測試並完成 INT0~3部分
 */
/*================================================*/

#endif
