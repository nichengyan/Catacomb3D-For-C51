#ifndef _ADC_
#define _ADC_
//ADC_CONTR
#define _ADC_POWER   0x80            
#define _ADC_FLAG    0x20            
#define _ADC_START   0x40
#define ADC_CH0 0X00
#define ADC_CH1 0X01
#define ADC_CH2 0X02
#define ADC_CH3 0X03
#define ADC_CH4 0X04
#define ADC_CH5 0X05
//ADC_CFG
#define _ADC_FORMAT  0x20            
#define _ADC_SPEEDLL 0x0F            
#define _ADC_SPEEDL  0x07            
#define _ADC_SPEEDH  0x03           
#define _ADC_SPEEDHH 0x00           


#include "STC8H.h"
#include "TYPE.h"
//#include "intrins.h"

void ADC_Init();
void ADC_ShutDown();
uint ADC_Result(uchar CHS,uchar SPD);

#endif