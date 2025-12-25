#include "ADC.h"
void ADC_Init(){
   ADC_CONTR|=_ADC_POWER;
}
void ADC_ShutDown(){
    ADC_CONTR&=(~_ADC_POWER);
}
int16 ADC_Result(int8 CHS,int8 SPD){
   ADC_CONTR&=0XF0;//清空之前的通道设置
   ADC_CONTR=ADC_CONTR|CHS|_ADC_START;
   ADCCFG=ADCCFG|_ADC_FORMAT|SPD;
    asm("nop");//_nop_();                        
    asm("nop");//_nop_();
    asm("nop");//_nop_();
    asm("nop");//_nop_();
    while (!(ADC_CONTR&_ADC_FLAG));
    ADC_CONTR&=(~_ADC_FLAG);
    return ADC_RES*256+ADC_RESL;
}  
	

