去年腳位、功能規劃：
TIMER 0 ASA佔用
TIMER 1 未測
TIMER 2 計時用，馬達等需要計時功能皆用此計時器
TIMER 3 SERVO使用，使用輸出腳PE4、PE5作為夾爪兩顆SERVO控制

PE6 左輪光遮斷訊號，外部中斷輸入腳
PE7 右輪光遮斷訊號，外部中斷輸入腳

PA0~7 其餘光遮斷器使用輸入腳

## 40 PIN

EXT_INT
INT4(OC3B/PE4)
INT5(OC3C/PE5)
INT6(T3/PE6)
INT7(ICP3/PE7)


PE0 RXD0/(PDI)   鎖死  
PE1 (TXD0/PDO)   鎖死  
PE2 (XCK0/AIN0)  鎖死  
PE3 (OC3A/AIN1)  鎖死  
PE4 (OC3B/INT4)  TIMER 3B輸出腳，外部中斷4輸入腳  
PE5 (OC3C/INT5)  TIMER 3C輸出腳，外部中斷5輸入腳  
PE6 (T3/INT6)    外部中斷6輸入腳  
PE7 (ICP3/INT7)  外部中斷7輸入腳  


PB7 OC2/OC1C(1) ~~TIMER 2B輸出腳、TIMER 1C輸出腳~~，ASA_ID辨識占用  
PB6 OC1B ~~TIMER 1B輸出腳~~，ASA_ID辨識占用  
PB5 OC1A ~~TIMER 1A輸出腳~~，ASA_ID辨識占用  
PB4 OC0   TIMER 0C輸出腳  
PB3 MISO ASA_SPI通訊佔用  
PB2 MOSI ASA_SPI通訊佔用  
PB1 SCK  ASA_SPI通訊佔用  
PB0 SS   ASA_SPI通訊佔用  

PA 可當正常 IO PORT  
PA7 AD7  
PA6 AD6  
PA5 AD5  
PA4 AD4  
PA3 AD3  
PA2 AD2  
PA1 AD1  
PA0 AD0  

PC 可當正常 IO PORT  
PC7 A15  
PC6 A14  
PC5 A13  
PC4 A12  
PC3 A11  
PC2 A10  
PC1 A9  
PC0 A8  

PD 待測
PD7 T2
PD6 T1
PD5 XCK1(1)
PD4 ICP1
PD3 INT3/TXD1(1)
PD2 INT2/RXD1(1)
PD1 INT1/SDA(1)
PD0 INT0/SCL(1)

功能
#### TIMER0  
ASA佔用  

#### TIMER1  
待測  
不可用輸出腳： PB7 (OC2/OC1C)、PB6 (OC1B)、PB5 (OC1A)  

#### TIMER2  
可用  
不可用輸出腳： PB7 (OC2/OC1C)  

#### TIMER3  
可用  
可用輸出腳： PE4 (OC3B/INT4)、PE5 (OC3C/INT5)  
不可用輸出腳： PE3 (OC3A/AIN1)
