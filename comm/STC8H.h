/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

#ifndef IOSTC8H_H
#define IOSTC8H_H

/* ------------------------------------------------------------------------------------------------
 *                                      编译器抽象
 * ------------------------------------------------------------------------------------------------
 */
#ifdef __IAR_SYSTEMS_ICC__  /*IAR平台 C语言 编译器*/

#pragma language=extended  /*支持语言扩展*/
#define SFR(name,addr)   __sfr   __no_init  volatile  unsigned char  name @ addr;
#define SFRBIT(name, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0) \
__sfr __no_init volatile union \
{                               \
  unsigned char name;         \
  struct {                     \
    unsigned char bit0 : 1;    \
    unsigned char bit1 : 1;    \
    unsigned char bit2 : 1;    \
    unsigned char bit3 : 1;    \
    unsigned char bit4 : 1;    \
    unsigned char bit5 : 1;    \
    unsigned char bit6 : 1;    \
    unsigned char bit7 : 1;    \
  };                           \
} @ addr;

#define XDATABIT(name, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0) \
__xdata __no_init volatile union \
{                                 \
  unsigned char name;           \
  struct {                       \
    unsigned char bit0 : 1;    \
    unsigned char bit1 : 1;    \
    unsigned char bit2 : 1;    \
    unsigned char bit3 : 1;    \
    unsigned char bit4 : 1;    \
    unsigned char bit5 : 1;    \
    unsigned char bit6 : 1;    \
    unsigned char bit7 : 1;    \
  } ;                           \
} @ addr;
#define SBIT(name,addr) /* 未在IAR C语言编译器中使用 */
#define XREG(addr)       ((unsigned char volatile __xdata *) 0)[addr]
#define XREG_INT(addr)   ((unsigned int volatile __xdata *) 0)[addr]
#define PXREG(addr)      (*(unsigned char volatile __xdata *) addr)
#define VECT(num,addr)   addr

#elif defined __IAR_SYSTEMS_ASM__  /*IAR平台 8051汇编 编译器*/

#define SFR(name,addr)   name  DEFINE  addr
SFRBITMACRO MACRO t, addr, bit7 , bit6, bit5, bit4, bit3, bit2, bit1, bit0
t    DEFINE addr
bit7 DEFINE addr.7
bit6 DEFINE addr.6
bit5 DEFINE addr.5
bit4 DEFINE addr.4    
bit3 DEFINE addr.3
bit2 DEFINE addr.2
bit1 DEFINE addr.1
bit0 DEFINE addr.0
ENDM

#define SFRBIT(name, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0) \
    SFRBITMACRO <name>, <addr>, <bit7>, <bit6>, <bit5>, <bit4>, <bit3>, <bit2>, <bit1>, <bit0>
#define XDATABIT(name, addr, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0) \
    SFRBITMACRO <name>, <addr>, <bit7>, <bit6>, <bit5>, <bit4>, <bit3>, <bit2>, <bit1>, <bit0>
#define SBIT(name,addr)  name  DEFINE  addr
#define XREG(addr)       addr
#define PXREG(addr)      addr
#define VECT(num,addr)   addr

#else
#error "Unrecognized compiler."
#endif


/*****************************SFR寄存器定义**************************/                    
SFRBIT( P0         ,  0x80, P07, P06, P05, P04, P03, P02, P01, P00 )
SFR(  SP             ,  0x81  )  
SFR(  DPL           ,  0x82  )   
SFR(  DPH          ,  0x83  )  
SFRBIT( S4CON  , 0x84, S4SM0, S4ST4, S4SM2, S4REN, S4TB8, S4RB8, S4TI, S4RI )
SFR(  S4BUF       ,  0x85  )  
SFRBIT( PCON  , 0x87, SMOD, SMOD0, LVDF, POF, GF1, GF0, PD, IDL )
SFRBIT( TCON    ,  0x88, TF1, TR1, TF0, TR0, IE1, IT1, IE0, IT0 )
SFRBIT( TMOD  , 0x89, T1_GATE, T1_CT, T1_M1, T1_M0, T0_GATE, T0_CT, T0_M1, T0_M0 )
SFR(  TL0            ,  0x8a  )  
SFR(  TL1            ,  0x8b  )  
SFR(  TH0           ,  0x8c  )  
SFR(  TH1           ,  0x8d  )  
SFRBIT( AUXR  , 0x8e, T0x12, T1x12, UART_M0x6, T2R, T2_CT, T2x12, EXTRAM, S1ST2 )
SFRBIT( INTCLKO  , 0x8f, , EX4, EX3, EX2, , T2CLKO, T1CLKO, T0CLKO )
SFRBIT( P1         ,  0x90, P17, P16, P15, P14, P13, P12, P11, P10 )
SFR(  P1M1        ,  0x91  )
SFR(  P1M0        ,  0x92  )
SFR(  P0M1        ,  0x93  )
SFR(  P0M0        ,  0x94  )
SFR(  P2M1        ,  0x95  )
SFR(  P2M0        ,  0x96  )
SFRBIT( SCON    ,  0x98, SM0, SM1, SM2, REN, TB8, RB8, TI, RI )  
SFR(  SBUF         ,  0x99  )
SFRBIT( S2CON  , 0x9a, S2SM0, , S2SM2, S2REN, S2TB8, S2RB8, S2TI, S2RI )
SFR(  S2BUF       ,  0x9b  )
SFR(  IRCBAND  ,  0x9d  )
SFR(  LIRTRIM    ,  0x9e  )
SFR(  IRTRIM      ,  0x9f  )
SFRBIT( P2          ,  0xa0, P27, P26, P25, P24, P23, P22, P21, P20 )
SFR(  P_SW1       ,  0xa2  )
SFRBIT( IE           ,  0xa8, EA, ELVD, EADC, ES, ET1, EX1, ET0, EX0 )
SFR(  SADDR      ,  0xa9  )
SFR(  WKTCL      ,  0xaa  )
SFRBIT( WKTCH  , 0xab, WKTEN, , , , , , ,  )
SFRBIT( S3CON  , 0xac, S3SM0, S3ST3, S3SM2, S3REN, S3TB8, S3RB8, S3TI, S3RI )
SFR(  S3BUF       ,  0xad  )
SFR(  TA             ,  0xae  )
SFRBIT( IE2         ,  0xaf, EUSB, ET4, ET3, ES4, ES3, ET2, ESPI, ES2 )
SFRBIT( P3         ,  0xb0, P37, P36, P35, P34, P33, P32, P31, P30 )
SFR(  P3M1        ,  0xb1  )
SFR(  P3M0        ,  0xb2  )
SFR(  P4M1        ,  0xb3  )
SFR(  P4M0        ,  0xb4  )
SFRBIT( IP2  , 0xb5, PUSB, PI2C, PCMP, PX4, PPWMB, PPWMA, PSPI, PS2)
SFRBIT( IP2H  , 0xb6, PUSBH, PI2CH, PCMPH, PX4H, PPWMBH, PPWMAH, PSPIH, PS2H )
SFRBIT( IPH  , 0xb7, , PLVDH, PADCH, PSH, PT1H, PX1H, PT0H, PX0H )
SFRBIT( IP     , 0xb8, , PLVD, PADC, PS, PT1, PX1, PT0, PX0 )
SFR(  SADEN      ,  0xb9  )
SFRBIT( P_SW2  , 0xba, EAXFR, , I2C_S1, I2C_S0, CMPO_S, S4_S, S3_S, S2_S)
SFRBIT( ADC_CONTR  , 0xbc, ADC_POWER, ADC_START, ADC_FLAG, ADC_EPWMT, , , ,  )
SFR(  ADC_RES  ,  0xbd  )
SFR(  ADC_RESL ,  0xbe  )
SFRBIT( P4         ,  0xc0, P47, P46, P45, P44, P43, P42, P41, P40 )
SFRBIT( WDT_CONTR  , 0xc1, WDT_FLAG, , EN_WDT, CLR_WDT, IDL_WDT, , ,  )
SFR(  IAP_DATA      ,  0xc2  )
SFR(  IAP_ADDRH   ,  0xc3  )
SFR(  IAP_ADDRL    ,  0xc4  )
SFR(  IAP_CMD       ,  0xc5  )
SFR(  IAP_TRIG       ,  0xc6  )
SFRBIT( IAP_CONTR  , 0xc7, IAPEN, SWBS, SWRST, CMD_FAIL, , , ,  )
SFRBIT( P5         ,  0xc8, P57, P56, P55, P54, P53, P52, P51, P50 )
SFR(  P5M1        ,  0xc9  )
SFR(  P5M0        ,  0xca  )
SFR(  P6M1        ,  0xcb  )
SFR(  P6M0        ,  0xcc  )
SFRBIT( SPSTAT  , 0xcd, SPIF, WCOL, , , , , ,  )
SFRBIT( SPCTL  , 0xce, SSIG, SPEN, DORD, MSTR, CPOL, CPHA, ,  )
SFR(  SPDAT      ,  0xcf  )
SFRBIT( PSW     ,  0xd0, CY, AC, F0, RS1, RS0, OV, F1, P )  
SFRBIT( T4T3M  , 0xd1, T4R, T4_CT, T4x12, T4CLKO, T3R, T3_CT, T3x12, T3CLKO )
SFR(  T4H          ,  0xd2  )
SFR(  T4L           ,  0xd3  )
SFR(  T3H          ,  0xd4  )
SFR(  T3L           ,  0xd5  )
SFR(  T2H          ,  0xd6  )
SFR(  T2L           ,  0xd7  )
SFR(  USBCLK    ,  0xdc  )
SFRBIT( ADCCFG  , 0xde, , , RESFMT, , , , ,  )

SFRBIT( IP3  , 0xdf, , , , , , PRTC, PS4, PS3)
SFR(  ACC         ,  0xe0  )
SFR(  P7M1      ,  0xe1  )
SFR(  P7M0      ,  0xe2  )
SFRBIT( DPS  , 0xe3, ID1, ID0, TSL, AU1, AU0, , , SEL)
SFR(  DPL1       ,  0xe4  )
SFR(  DPH1      ,  0xe5  )
SFRBIT( CMPCR1  , 0xe6, CMPEN, CMPIF, PIE, NIE, PIS, NIS, CMPOE, CMPRES )
SFRBIT( CMPCR2  , 0xe7, INVCMPO, DISFLT, , , , , ,  )
SFRBIT( P6      ,  0xe8, P67, P66, P65, P64, P63, P62, P61, P60 )
SFR(  USBDAT  ,  0xec  )
SFRBIT( IP3H  , 0xee, , , , , , PRTCH, PS4H, PS3H)
SFRBIT( AUXINTIF  , 0xef, , INT4IF, INT3IF, INT2IF, , T4IF, T3IF, T2IF )
SFR(  B           ,  0xf0  )
SFRBIT( USBCON  , 0xf4, ENUSB, USBRST, PS2M, PUEN, PDEN, DFREC, DP, DM)
SFR(  IAP_TPS     ,  0xf5  )
SFRBIT( P7      ,  0xf8, P77, P76, P75, P74, P73, P72, P71, P70 )
SFR(  USBADR    ,  0xfc  )
SFRBIT( RSTCFG  , 0xff, , ENLVR, , P54RST, , , , )

/**********************************说明*************************************
//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
****************************************************************************/
XDATABIT( CLKSEL          , 0xfe00, , , , , , , , )
XDATABIT( CLKDIV          , 0xfe01, , , , , , , , )
XDATABIT( HIRCCR         , 0xfe02, ENHIRC, , , , , , , HIRCST)
XDATABIT( XOSCCR         , 0xfe03, ENXOSC, XITYPE, , , , , , XOSCST)
XDATABIT( IRC32KCR      , 0xfe04, ENIRC32K, , , , , , , IRC32KST)
XDATABIT( MCLKOCR     , 0xfe05, MCLKO_S, , , , , , , )
XDATABIT( IRCDB            , 0xfe06, , , , , , , , )
XDATABIT( IRC48MCR     , 0xfe07, ENIRC48M, , , , , , , IRC48MST)
XDATABIT( X32KCR          , 0xfe08, ENX32K, GAIN32K, , , , , , X32KST)

/*****************************I/O端口特殊功能寄存器*************************/
XDATABIT( P0PU  , 0xfe10, , , , , , , , )
XDATABIT( P1PU  , 0xfe11, , , , , , , , )
XDATABIT( P2PU  , 0xfe12, , , , , , , , )
XDATABIT( P3PU  , 0xfe13, , , , , , , , )
XDATABIT( P4PU  , 0xfe14, , , , , , , , )
XDATABIT( P5PU  , 0xfe15, , , , , , , , )
XDATABIT( P6PU  , 0xfe16, , , , , , , , )
XDATABIT( P7PU  , 0xfe17, , , , , , , , )
XDATABIT( P0NCS , 0xfe18, , , , , , , , )
XDATABIT( P1NCS , 0xfe19, , , , , , , , )
XDATABIT( P2NCS , 0xfe1a, , , , , , , , )
XDATABIT( P3NCS , 0xfe1b, , , , , , , , )
XDATABIT( P4NCS , 0xfe1c, , , , , , , , )
XDATABIT( P5NCS , 0xfe1d, , , , , , , , )
XDATABIT( P6NCS , 0xfe1e, , , , , , , , )
XDATABIT( P7NCS , 0xfe1f, , , , , , , , )

XDATABIT( P0SR   , 0xfe20, , , , , , , , )
XDATABIT( P1SR   , 0xfe21, , , , , , , , )
XDATABIT( P2SR   , 0xfe22, , , , , , , , )
XDATABIT( P3SR   , 0xfe23, , , , , , , , )
XDATABIT( P4SR   , 0xfe24, , , , , , , , )
XDATABIT( P5SR   , 0xfe25, , , , , , , , )
XDATABIT( P6SR   , 0xfe26, , , , , , , , )
XDATABIT( P7SR   , 0xfe27, , , , , , , , )
XDATABIT( P0DR   , 0xfe28, , , , , , , , )
XDATABIT( P1DR   , 0xfe29, , , , , , , , )
XDATABIT( P2DR   , 0xfe2a, , , , , , , , )
XDATABIT( P3DR   , 0xfe2b, , , , , , , , )
XDATABIT( P4DR   , 0xfe2c, , , , , , , , )
XDATABIT( P5DR   , 0xfe2d, , , , , , , , )
XDATABIT( P6DR   , 0xfe2e, , , , , , , , )
XDATABIT( P7DR   , 0xfe2f, , , , , , , , )
XDATABIT( P0IE   , 0xfe30, , , , , , , , )
XDATABIT( P1IE   , 0xfe31, , , , , , , , )
XDATABIT( P2IE   , 0xfe32, , , , , , , , )
XDATABIT( P3IE   , 0xfe33, , , , , , , , )
XDATABIT( P4IE   , 0xfe34, , , , , , , , )
XDATABIT( P5IE   , 0xfe35, , , , , , , , )
XDATABIT( P6IE   , 0xfe36, , , , , , , , )
XDATABIT( P7IE   , 0xfe37, , , , , , , , )

XDATABIT( LCMIFCFG          , 0xfe50, , , , , , , , )
XDATABIT( LCMIFCFG2         , 0xfe51, , , , , , , , )
XDATABIT( LCMIFCR           , 0xfe52, , , , , , , , )
XDATABIT( LCMIFSTA          , 0xfe53, , , , , , , , )
XDATABIT( LCMIFDATL         , 0xfe54, , , , , , , , )
XDATABIT( LCMIFDATH         , 0xfe55, , , , , , , , )

XDATABIT( RTCCR             , 0xfe60, , , , , , , , RUNRTC)
XDATABIT( RTCCFG            , 0xfe61, , , , , , , RTCCKS, SETRTC)
XDATABIT( RTCIEN            , 0xfe62, EALAI, EDAYI, EHOURI, EMINI, ESECI, ESEC2I, ESEC8I, ESEC32I)
XDATABIT( RTCIF             , 0xfe63, ALAIF, DAYIF, HOURIF, MINIF, SECIF, SEC2IF, SEC8IF, SEC32IF)
XDATABIT( ALAHOUR           , 0xfe64, , , , , , , , )
XDATABIT( ALAMIN            , 0xfe65, , , , , , , , )
XDATABIT( ALASEC            , 0xfe66, , , , , , , , )
XDATABIT( ALASSEC           , 0xfe67, , , , , , , , )
XDATABIT( INIYEAR           , 0xfe68, , , , , , , , )
XDATABIT( INIMONTH          , 0xfe69, , , , , , , , )
XDATABIT( INIDAY            , 0xfe6a, , , , , , , , )
XDATABIT( INIHOUR           , 0xfe6b, , , , , , , , )
XDATABIT( INIMIN            , 0xfe6c, , , , , , , , )
XDATABIT( INISEC            , 0xfe6d, , , , , , , , )
XDATABIT( INISSEC           , 0xfe6e, , , , , , , , )
XDATABIT( YEAR              , 0xfe70, , , , , , , , )
XDATABIT( MONTH             , 0xfe71, , , , , , , , )
XDATABIT( DAY               , 0xfe72, , , , , , , , )
XDATABIT( HOUR              , 0xfe73, , , , , , , , )
XDATABIT( MIN               , 0xfe74, , , , , , , , )
XDATABIT( SEC               , 0xfe75, , , , , , , , )
XDATABIT( SSEC              , 0xfe76, , , , , , , , )

XDATABIT( I2CCFG  , 0xfe80, ENI2C, MSSL, , , , , ,  )
XDATABIT( I2CMSCR  , 0xfe81, EMSI, , , , , , , )
XDATABIT( I2CMSST  , 0xfe82, MSBUSY, MSIF, , , , , MSACKI, MSACKO)
XDATABIT( I2CSLCR  , 0xfe83, , ESTAI, ERXI, ETXI, ESTOI, , , SLRST)
XDATABIT( I2CSLST  , 0xfe84, SLBUSY, STAIF, RXIF, TXIF, STOIF, , SLACKI, SLACKO)
XDATABIT( I2CSLADR  , 0xfe85, , , , , , , , MA)
XDATABIT( I2CTXD  , 0xfe86, , , , , , , , )
XDATABIT( I2CRXD  , 0xfe87, , , , , , , , )
XDATABIT( I2CMSAUX  , 0xfe88, , , , , , , , WDTA)

XDATABIT( SPFUNC  , 0xfe98, , , , , , , , BKSWR)
XDATABIT( RSTFLAG  , 0xfe99, , , , LVDRSTF, WDTRSTF, SWRSTF, ROMOVF, EXRSTF)

XDATABIT( TM2PS             , 0xfea2, , , , , , , , )
XDATABIT( TM3PS             , 0xfea3, , , , , , , , )
XDATABIT( TM4PS             , 0xfea4, , , , , , , , )
XDATABIT( ADCTIM            , 0xfea8, , , , , , , , )
XDATABIT( T3T4PIN           , 0xfeac, , , , , , , , T3T4SEL)
XDATABIT( ADCEXCFG          , 0xfead, , , , , , , , )
XDATABIT( CMPEXCFG          , 0xfeae, , , , , , , , )

XDATABIT( PWMA_ETRPS        , 0xfeb0, , , , , , , , )
XDATABIT( PWMA_ENO          , 0xfeb1, ENO4N, ENO4P, ENO3N, ENO3P, ENO2N, ENO2P, ENO1N, ENO1P)
XDATABIT( PWMA_PS           , 0xfeb2, , , , , , , , )
XDATABIT( PWMA_IOAUX        , 0xfeb3, AUX4N, AUX4P, AUX3N, AUX3P, AUX2N, AUX2P, AUX1N, AUX1P)
XDATABIT( PWMB_ETRPS        , 0xfeb4, , , , , , , , )
XDATABIT( PWMB_ENO          , 0xfeb5, , ENO8P, , ENO7P, , ENO6P, , ENO5P)
XDATABIT( PWMB_PS           , 0xfeb6, , , , , , , , )
XDATABIT( PWMB_IOAUX        , 0xfeb7, , AUX8P, , AUX7P, , AUX6P, , AUX5P)
XDATABIT( PWMA_CR1          , 0xfec0, , , , , , , , CENA)
XDATABIT( PWMA_CR2          , 0xfec1, , , , , , , , )
XDATABIT( PWMA_SMCR         , 0xfec2, , , , , , , , )
XDATABIT( PWMA_ETR          , 0xfec3, , , , , , , , )
XDATABIT( PWMA_IER          , 0xfec4, , , , , , , , )
XDATABIT( PWMA_SR1          , 0xfec5, , , , , , , , )
XDATABIT( PWMA_SR2          , 0xfec6, , , , , , , , )
XDATABIT( PWMA_EGR          , 0xfec7, , , , , , , , )
XDATABIT( PWMA_CCMR1        , 0xfec8, , , , , , , , )
XDATABIT( PWMA_CCMR2        , 0xfec9, , , , , , , , )
XDATABIT( PWMA_CCMR3        , 0xfeca, , , , , , , , )
XDATABIT( PWMA_CCMR4        , 0xfecb, , , , , , , , )
XDATABIT( PWMA_CCER1        , 0xfecc, , , , , , , , )
XDATABIT( PWMA_CCER2        , 0xfecd, , , , , , , , )
XDATABIT( PWMA_CNTRH        , 0xfece, , , , , , , , )
XDATABIT( PWMA_CNTRL        , 0xfecf, , , , , , , , )
XDATABIT( PWMA_PSCRH        , 0xfed0, , , , , , , , )
XDATABIT( PWMA_PSCRL        , 0xfed1, , , , , , , , )
XDATABIT( PWMA_ARRH         , 0xfed2, , , , , , , , )
XDATABIT( PWMA_ARRL         , 0xfed3, , , , , , , , )
XDATABIT( PWMA_RCR          , 0xfed4, , , , , , , , )
XDATABIT( PWMA_CCR1H        , 0xfed5, , , , , , , , )
XDATABIT( PWMA_CCR1L        , 0xfed6, , , , , , , , )
XDATABIT( PWMA_CCR2H        , 0xfed7, , , , , , , , )
XDATABIT( PWMA_CCR2L        , 0xfed8, , , , , , , , )
XDATABIT( PWMA_CCR3H        , 0xfed9, , , , , , , , )
XDATABIT( PWMA_CCR3L        , 0xfeda, , , , , , , , )
XDATABIT( PWMA_CCR4H        , 0xfedb, , , , , , , , )
XDATABIT( PWMA_CCR4L        , 0xfedc, , , , , , , , )
XDATABIT( PWMA_BKR          , 0xfedd, MOEA, AOEA, BKPA, BKEA, OSSRA, OSSIA, , )
XDATABIT( PWMA_DTR          , 0xfede, , , , , , , , )
XDATABIT( PWMA_OISR         , 0xfedf, , , , , , , , )
XDATABIT( PWMB_CR1          , 0xfee0, , , , , , , , CENB)
XDATABIT( PWMB_CR2          , 0xfee1, , , , , , , , )
XDATABIT( PWMB_SMCR         , 0xfee2, , , , , , , , )
XDATABIT( PWMB_ETR          , 0xfee3, , , , , , , , )
XDATABIT( PWMB_IER          , 0xfee4, , , , , , , , )
XDATABIT( PWMB_SR1          , 0xfee5, , , , , , , , )
XDATABIT( PWMB_SR2          , 0xfee6, , , , , , , , )
XDATABIT( PWMB_EGR          , 0xfee7, , , , , , , , )
XDATABIT( PWMB_CCMR1        , 0xfee8, , , , , , , , )
XDATABIT( PWMB_CCMR2        , 0xfee9, , , , , , , , )
XDATABIT( PWMB_CCMR3        , 0xfeea, , , , , , , , )
XDATABIT( PWMB_CCMR4        , 0xfeeb, , , , , , , , )
XDATABIT( PWMB_CCER1        , 0xfeec, , , , , , , , )
XDATABIT( PWMB_CCER2        , 0xfeed, , , , , , , , )
XDATABIT( PWMB_CNTRH        , 0xfeee, , , , , , , , )
XDATABIT( PWMB_CNTRL        , 0xfeef, , , , , , , , )
XDATABIT( PWMB_PSCRH        , 0xfef0, , , , , , , , )
XDATABIT( PWMB_PSCRL        , 0xfef1, , , , , , , , )
XDATABIT( PWMB_ARRH         , 0xfef2, , , , , , , , )
XDATABIT( PWMB_ARRL         , 0xfef3, , , , , , , , )
XDATABIT( PWMB_RCR          , 0xfef4, , , , , , , , )
XDATABIT( PWMB_CCR5H        , 0xfef5, , , , , , , , )
XDATABIT( PWMB_CCR5L        , 0xfef6, , , , , , , , )
XDATABIT( PWMB_CCR6H        , 0xfef7, , , , , , , , )
XDATABIT( PWMB_CCR6L        , 0xfef8, , , , , , , , )
XDATABIT( PWMB_CCR7H        , 0xfef9, , , , , , , , )
XDATABIT( PWMB_CCR7L        , 0xfefa, , , , , , , , )
XDATABIT( PWMB_CCR8H        , 0xfefb, , , , , , , , )
XDATABIT( PWMB_CCR8L        , 0xfefc, , , , , , , , )
XDATABIT( PWMB_BKR          , 0xfefd, MOEB, AOEB, BKPB, BKEB, OSSRB, OSSIB, , )
XDATABIT( PWMB_DTR          , 0xfefe, , , , , , , , )
XDATABIT( PWMB_OISR         , 0xfeff, , , , , , , , )

/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

XDATABIT( P0INTE            , 0xfd00, , , , , , , , )
XDATABIT( P1INTE            , 0xfd01, , , , , , , , )
XDATABIT( P2INTE            , 0xfd02, , , , , , , , )
XDATABIT( P3INTE            , 0xfd03, , , , , , , , )
XDATABIT( P4INTE            , 0xfd04, , , , , , , , )
XDATABIT( P5INTE            , 0xfd05, , , , , , , , )
XDATABIT( P6INTE            , 0xfd06, , , , , , , , )
XDATABIT( P7INTE            , 0xfd07, , , , , , , , )
XDATABIT( P0INTF            , 0xfd10, , , , , , , , )
XDATABIT( P1INTF            , 0xfd11, , , , , , , , )
XDATABIT( P2INTF            , 0xfd12, , , , , , , , )
XDATABIT( P3INTF            , 0xfd13, , , , , , , , )
XDATABIT( P4INTF            , 0xfd14, , , , , , , , )
XDATABIT( P5INTF            , 0xfd15, , , , , , , , )
XDATABIT( P6INTF            , 0xfd16, , , , , , , , )
XDATABIT( P7INTF            , 0xfd17, , , , , , , , )
XDATABIT( P0IM0             , 0xfd20, , , , , , , , )
XDATABIT( P1IM0             , 0xfd21, , , , , , , , )
XDATABIT( P2IM0             , 0xfd22, , , , , , , , )
XDATABIT( P3IM0             , 0xfd23, , , , , , , , )
XDATABIT( P4IM0             , 0xfd24, , , , , , , , )
XDATABIT( P5IM0             , 0xfd25, , , , , , , , )
XDATABIT( P6IM0             , 0xfd26, , , , , , , , )
XDATABIT( P7IM0             , 0xfd27, , , , , , , , )
XDATABIT( P0IM1             , 0xfd30, , , , , , , , )
XDATABIT( P1IM1             , 0xfd31, , , , , , , , )
XDATABIT( P2IM1             , 0xfd32, , , , , , , , )
XDATABIT( P3IM1             , 0xfd33, , , , , , , , )
XDATABIT( P4IM1             , 0xfd34, , , , , , , , )
XDATABIT( P5IM1             , 0xfd35, , , , , , , , )
XDATABIT( P6IM1             , 0xfd36, , , , , , , , )
XDATABIT( P7IM1             , 0xfd37, , , , , , , , )
XDATABIT( P0WKUE            , 0xfd40, , , , , , , , )
XDATABIT( P1WKUE            , 0xfd41, , , , , , , , )
XDATABIT( P2WKUE            , 0xfd42, , , , , , , , )
XDATABIT( P3WKUE            , 0xfd43, , , , , , , , )
XDATABIT( P4WKUE            , 0xfd44, , , , , , , , )
XDATABIT( P5WKUE            , 0xfd45, , , , , , , , )
XDATABIT( P6WKUE            , 0xfd46, , , , , , , , )
XDATABIT( P7WKUE            , 0xfd47, , , , , , , , )

XDATABIT( PIN_IP            , 0xfd60, , , , , , , , )
XDATABIT( PIN_IPH           , 0xfd61, , , , , , , , )

XDATABIT( CHIPID0           , 0xfde0, , , , , , , , )
XDATABIT( CHIPID1           , 0xfde1, , , , , , , , )
XDATABIT( CHIPID2           , 0xfde2, , , , , , , , )
XDATABIT( CHIPID3           , 0xfde3, , , , , , , , )
XDATABIT( CHIPID4           , 0xfde4, , , , , , , , )
XDATABIT( CHIPID5           , 0xfde5, , , , , , , , )
XDATABIT( CHIPID6           , 0xfde6, , , , , , , , )
XDATABIT( CHIPID7           , 0xfde7, , , , , , , , )
XDATABIT( CHIPID8           , 0xfde8, , , , , , , , )
XDATABIT( CHIPID9           , 0xfde9, , , , , , , , )
XDATABIT( CHIPID10          , 0xfdea, , , , , , , , )
XDATABIT( CHIPID11          , 0xfdeb, , , , , , , , )
XDATABIT( CHIPID12          , 0xfdec, , , , , , , , )
XDATABIT( CHIPID13          , 0xfded, , , , , , , , )
XDATABIT( CHIPID14          , 0xfdee, , , , , , , , )
XDATABIT( CHIPID15          , 0xfdef, , , , , , , , )
XDATABIT( CHIPID16          , 0xfdf0, , , , , , , , )
XDATABIT( CHIPID17          , 0xfdf1, , , , , , , , )
XDATABIT( CHIPID18          , 0xfdf2, , , , , , , , )
XDATABIT( CHIPID19          , 0xfdf3, , , , , , , , )
XDATABIT( CHIPID20          , 0xfdf4, , , , , , , , )
XDATABIT( CHIPID21          , 0xfdf5, , , , , , , , )
XDATABIT( CHIPID22          , 0xfdf6, , , , , , , , )
XDATABIT( CHIPID23          , 0xfdf7, , , , , , , , )
XDATABIT( CHIPID24          , 0xfdf8, , , , , , , , )
XDATABIT( CHIPID25          , 0xfdf9, , , , , , , , )
XDATABIT( CHIPID26          , 0xfdfa, , , , , , , , )
XDATABIT( CHIPID27          , 0xfdfb, , , , , , , , )
XDATABIT( CHIPID28          , 0xfdfc, , , , , , , , )
XDATABIT( CHIPID29          , 0xfdfd, , , , , , , , )
XDATABIT( CHIPID30          , 0xfdfe, , , , , , , , )
XDATABIT( CHIPID31          , 0xfdff, , , , , , , , )

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

XDATABIT( MD3               , 0xfcf0, , , , , , , , )
XDATABIT( MD2               , 0xfcf1, , , , , , , , )
XDATABIT( MD1               , 0xfcf2, , , , , , , , )
XDATABIT( MD0               , 0xfcf3, , , , , , , , )
XDATABIT( MD5               , 0xfcf4, , , , , , , , )
XDATABIT( MD4               , 0xfcf5, , , , , , , , )
XDATABIT( ARCON             , 0xfcf6, , , , , , , , )
XDATABIT( OPCON             , 0xfcf7, , , , , , , , )

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////

XDATABIT( COMEN             , 0xfb00, , , , , , , , )
XDATABIT( SEGENL            , 0xfb01, , , , , , , , )
XDATABIT( SEGENH            , 0xfb02, , , , , , , , )
XDATABIT( LEDCTRL           , 0xfb03, , , , , , , , )
XDATABIT( LEDCKS            , 0xfb04, , , , , , , , )
XDATABIT( COM0_DA_L         , 0xfb10, , , , , , , , )
XDATABIT( COM1_DA_L         , 0xfb11, , , , , , , , )
XDATABIT( COM2_DA_L         , 0xfb12, , , , , , , , )
XDATABIT( COM3_DA_L         , 0xfb13, , , , , , , , )
XDATABIT( COM4_DA_L         , 0xfb14, , , , , , , , )
XDATABIT( COM5_DA_L         , 0xfb15, , , , , , , , )
XDATABIT( COM6_DA_L         , 0xfb16, , , , , , , , )
XDATABIT( COM7_DA_L         , 0xfb17, , , , , , , , )
XDATABIT( COM0_DA_H         , 0xfb18, , , , , , , , )
XDATABIT( COM1_DA_H         , 0xfb19, , , , , , , , )
XDATABIT( COM2_DA_H         , 0xfb1a, , , , , , , , )
XDATABIT( COM3_DA_H         , 0xfb1b, , , , , , , , )
XDATABIT( COM4_DA_H         , 0xfb1c, , , , , , , , )
XDATABIT( COM5_DA_H         , 0xfb1d, , , , , , , , )
XDATABIT( COM6_DA_H         , 0xfb1e, , , , , , , , )
XDATABIT( COM7_DA_H         , 0xfb1f, , , , , , , , )
XDATABIT( COM0_DC_L         , 0xfb20, , , , , , , , )
XDATABIT( COM1_DC_L         , 0xfb21, , , , , , , , )
XDATABIT( COM2_DC_L         , 0xfb22, , , , , , , , )
XDATABIT( COM3_DC_L         , 0xfb23, , , , , , , , )
XDATABIT( COM4_DC_L         , 0xfb24, , , , , , , , )
XDATABIT( COM5_DC_L         , 0xfb25, , , , , , , , )
XDATABIT( COM6_DC_L         , 0xfb26, , , , , , , , )
XDATABIT( COM7_DC_L         , 0xfb27, , , , , , , , )
XDATABIT( COM0_DC_H         , 0xfb28, , , , , , , , )
XDATABIT( COM1_DC_H         , 0xfb29, , , , , , , , )
XDATABIT( COM2_DC_H         , 0xfb2a, , , , , , , , )
XDATABIT( COM3_DC_H         , 0xfb2b, , , , , , , , )
XDATABIT( COM4_DC_H         , 0xfb2c, , , , , , , , )
XDATABIT( COM5_DC_H         , 0xfb2d, , , , , , , , )
XDATABIT( COM6_DC_H         , 0xfb2e, , , , , , , , )
XDATABIT( COM7_DC_H         , 0xfb2f, , , , , , , , )

XDATABIT( TSCHEN1           , 0xfb40, , , , , , , , )
XDATABIT( TSCHEN2           , 0xfb41, , , , , , , , )
XDATABIT( TSCFG1            , 0xfb42, , , , , , , , )
XDATABIT( TSCFG2            , 0xfb43, , , , , , , , )
XDATABIT( TSWUTC            , 0xfb44, , , , , , , , )
XDATABIT( TSCTRL            , 0xfb45, , , , , , , , )
XDATABIT( TSSTA1            , 0xfb46, , , , , , , , )
XDATABIT( TSSTA2            , 0xfb47, , , , , , , , )
XDATABIT( TSRT              , 0xfb48, , , , , , , , )
XDATABIT( TSDATH            , 0xfb49, , , , , , , , )
XDATABIT( TSDATL            , 0xfb4A, , , , , , , , )
XDATABIT( TSTH00H           , 0xfb50, , , , , , , , )
XDATABIT( TSTH00L           , 0xfb51, , , , , , , , )
XDATABIT( TSTH01H           , 0xfb52, , , , , , , , )
XDATABIT( TSTH01L           , 0xfb53, , , , , , , , )
XDATABIT( TSTH02H           , 0xfb54, , , , , , , , )
XDATABIT( TSTH02L           , 0xfb55, , , , , , , , )
XDATABIT( TSTH03H           , 0xfb56, , , , , , , , )
XDATABIT( TSTH03L           , 0xfb57, , , , , , , , )
XDATABIT( TSTH04H           , 0xfb58, , , , , , , , )
XDATABIT( TSTH04L           , 0xfb59, , , , , , , , )
XDATABIT( TSTH05H           , 0xfb5a, , , , , , , , )
XDATABIT( TSTH05L           , 0xfb5b, , , , , , , , )
XDATABIT( TSTH06H           , 0xfb5c, , , , , , , , )
XDATABIT( TSTH06L           , 0xfb5d, , , , , , , , )
XDATABIT( TSTH07H           , 0xfb5e, , , , , , , , )
XDATABIT( TSTH07L           , 0xfb5f, , , , , , , , )
XDATABIT( TSTH08H           , 0xfb60, , , , , , , , )
XDATABIT( TSTH08L           , 0xfb61, , , , , , , , )
XDATABIT( TSTH09H           , 0xfb62, , , , , , , , )
XDATABIT( TSTH09L           , 0xfb63, , , , , , , , )
XDATABIT( TSTH10H           , 0xfb64, , , , , , , , )
XDATABIT( TSTH10L           , 0xfb65, , , , , , , , )
XDATABIT( TSTH11H           , 0xfb66, , , , , , , , )
XDATABIT( TSTH11L           , 0xfb67, , , , , , , , )
XDATABIT( TSTH12H           , 0xfb68, , , , , , , , )
XDATABIT( TSTH12L           , 0xfb69, , , , , , , , )
XDATABIT( TSTH13H           , 0xfb6a, , , , , , , , )
XDATABIT( TSTH13L           , 0xfb6b, , , , , , , , )
XDATABIT( TSTH14H           , 0xfb6c, , , , , , , , )
XDATABIT( TSTH14L           , 0xfb6d, , , , , , , , )
XDATABIT( TSTH15H           , 0xfb6e, , , , , , , , )
XDATABIT( TSTH15L           , 0xfb6f, , , , , , , , )

XDATABIT( LCDCFG            , 0xfb80, , , , , , , , )
XDATABIT( LCDCFG2           , 0xfb81, , , , , , , , )
XDATABIT( DBLNTH            , 0xfb82, , , , , , , , )
XDATABIT( COMLNTHL          , 0xfb83, , , , , , , , )
XDATABIT( COMLNTHM          , 0xfb84, , , , , , , , )
XDATABIT( COMLNTHH          , 0xfb85, , , , , , , , )
XDATABIT( BLINKFRPS         , 0xfb86, , , , , , , , )
XDATABIT( LCDCR             , 0xfb87, , , , , , , , )
XDATABIT( COM_ON_A          , 0xfb88, , , , , , , , )
XDATABIT( COM_ON_B          , 0xfb89, , , , , , , , )
XDATABIT( SEG_ON_A          , 0xfb8a, , , , , , , , )
XDATABIT( SEG_ON_B          , 0xfb8b, , , , , , , , )
XDATABIT( SEG_ON_C          , 0xfb8c, , , , , , , , )
XDATABIT( SEG_ON_D          , 0xfb8d, , , , , , , , )
XDATABIT( SEG_ON_E          , 0xfb8e, , , , , , , , )
XDATABIT( C0SEGV0           , 0xfb90, , , , , , , , )
XDATABIT( C0SEGV1           , 0xfb91, , , , , , , , )
XDATABIT( C0SEGV2           , 0xfb92, , , , , , , , )
XDATABIT( C0SEGV3           , 0xfb93, , , , , , , , )
XDATABIT( C0SEGV4           , 0xfb94, , , , , , , , )
XDATABIT( C1SEGV0           , 0xfb98, , , , , , , , )
XDATABIT( C1SEGV1           , 0xfb99, , , , , , , , )
XDATABIT( C1SEGV2           , 0xfb9a, , , , , , , , )
XDATABIT( C1SEGV3           , 0xfb9b, , , , , , , , )
XDATABIT( C1SEGV4           , 0xfb9c, , , , , , , , )
XDATABIT( C2SEGV0           , 0xfba0, , , , , , , , )
XDATABIT( C2SEGV1           , 0xfba1, , , , , , , , )
XDATABIT( C2SEGV2           , 0xfba2, , , , , , , , )
XDATABIT( C2SEGV3           , 0xfba3, , , , , , , , )
XDATABIT( C2SEGV4           , 0xfba4, , , , , , , , )
XDATABIT( C3SEGV0           , 0xfba8, , , , , , , , )
XDATABIT( C3SEGV1           , 0xfba9, , , , , , , , )
XDATABIT( C3SEGV2           , 0xfbaa, , , , , , , , )
XDATABIT( C3SEGV3           , 0xfbab, , , , , , , , )
XDATABIT( C3SEGV4           , 0xfbac, , , , , , , , )

/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////

XDATABIT( DMA_M2M_CFG       , 0xfa00, , , , , , , , )
XDATABIT( DMA_M2M_CR        , 0xfa01, , , , , , , , )
XDATABIT( DMA_M2M_STA       , 0xfa02, , , , , , , , )
XDATABIT( DMA_M2M_AMT       , 0xfa03, , , , , , , , )
XDATABIT( DMA_M2M_DONE      , 0xfa04, , , , , , , , )
XDATABIT( DMA_M2M_TXAH      , 0xfa05, , , , , , , , )
XDATABIT( DMA_M2M_TXAL      , 0xfa06, , , , , , , , )
XDATABIT( DMA_M2M_RXAH      , 0xfa07, , , , , , , , )
XDATABIT( DMA_M2M_RXAL      , 0xfa08, , , , , , , , )

XDATABIT( DMA_ADC_CFG       , 0xfa10, , , , , , , , )
XDATABIT( DMA_ADC_CR        , 0xfa11, , , , , , , , )
XDATABIT( DMA_ADC_STA       , 0xfa12, , , , , , , , )
XDATABIT( DMA_ADC_RXAH      , 0xfa17, , , , , , , , )
XDATABIT( DMA_ADC_RXAL      , 0xfa18, , , , , , , , )
XDATABIT( DMA_ADC_CFG2      , 0xfa19, , , , , , , , )
XDATABIT( DMA_ADC_CHSW0     , 0xfa1a, , , , , , , , )
XDATABIT( DMA_ADC_CHSW1     , 0xfa1b, , , , , , , , )

XDATABIT( DMA_SPI_CFG       , 0xfa20, , , , , , , , )
XDATABIT( DMA_SPI_CR        , 0xfa21, , , , , , , , )
XDATABIT( DMA_SPI_STA       , 0xfa22, , , , , , , , )
XDATABIT( DMA_SPI_AMT       , 0xfa23, , , , , , , , )
XDATABIT( DMA_SPI_DONE      , 0xfa24, , , , , , , , )
XDATABIT( DMA_SPI_TXAH      , 0xfa25, , , , , , , , )
XDATABIT( DMA_SPI_TXAL      , 0xfa26, , , , , , , , )
XDATABIT( DMA_SPI_RXAH      , 0xfa27, , , , , , , , )
XDATABIT( DMA_SPI_RXAL      , 0xfa28, , , , , , , , )
XDATABIT( DMA_SPI_CFG2      , 0xfa29, , , , , , , , )

XDATABIT( DMA_UR1T_CFG      , 0xfa30, , , , , , , , )
XDATABIT( DMA_UR1T_CR       , 0xfa31, , , , , , , , )
XDATABIT( DMA_UR1T_STA      , 0xfa32, , , , , , , , )
XDATABIT( DMA_UR1T_AMT      , 0xfa33, , , , , , , , )
XDATABIT( DMA_UR1T_DONE     , 0xfa34, , , , , , , , )
XDATABIT( DMA_UR1T_TXAH     , 0xfa35, , , , , , , , )
XDATABIT( DMA_UR1T_TXAL     , 0xfa36, , , , , , , , )
XDATABIT( DMA_UR1R_CFG      , 0xfa38, , , , , , , , )
XDATABIT( DMA_UR1R_CR       , 0xfa39, , , , , , , , )
XDATABIT( DMA_UR1R_STA      , 0xfa3a, , , , , , , , )
XDATABIT( DMA_UR1R_AMT      , 0xfa3b, , , , , , , , )
XDATABIT( DMA_UR1R_DONE     , 0xfa3c, , , , , , , , )
XDATABIT( DMA_UR1R_RXAH     , 0xfa3d, , , , , , , , )
XDATABIT( DMA_UR1R_RXAL     , 0xfa3e, , , , , , , , )

XDATABIT( DMA_UR2T_CFG      , 0xfa40, , , , , , , , )
XDATABIT( DMA_UR2T_CR       , 0xfa41, , , , , , , , )
XDATABIT( DMA_UR2T_STA      , 0xfa42, , , , , , , , )
XDATABIT( DMA_UR2T_AMT      , 0xfa43, , , , , , , , )
XDATABIT( DMA_UR2T_DONE     , 0xfa44, , , , , , , , )
XDATABIT( DMA_UR2T_TXAH     , 0xfa45, , , , , , , , )
XDATABIT( DMA_UR2T_TXAL     , 0xfa46, , , , , , , , )
XDATABIT( DMA_UR2R_CFG      , 0xfa48, , , , , , , , )
XDATABIT( DMA_UR2R_CR       , 0xfa49, , , , , , , , )
XDATABIT( DMA_UR2R_STA      , 0xfa4a, , , , , , , , )
XDATABIT( DMA_UR2R_AMT      , 0xfa4b, , , , , , , , )
XDATABIT( DMA_UR2R_DONE     , 0xfa4c, , , , , , , , )
XDATABIT( DMA_UR2R_RXAH     , 0xfa4d, , , , , , , , )
XDATABIT( DMA_UR2R_RXAL     , 0xfa4e, , , , , , , , )

XDATABIT( DMA_UR3T_CFG      , 0xfa50, , , , , , , , )
XDATABIT( DMA_UR3T_CR       , 0xfa51, , , , , , , , )
XDATABIT( DMA_UR3T_STA      , 0xfa52, , , , , , , , )
XDATABIT( DMA_UR3T_AMT      , 0xfa53, , , , , , , , )
XDATABIT( DMA_UR3T_DONE     , 0xfa54, , , , , , , , )
XDATABIT( DMA_UR3T_TXAH     , 0xfa55, , , , , , , , )
XDATABIT( DMA_UR3T_TXAL     , 0xfa56, , , , , , , , )
XDATABIT( DMA_UR3R_CFG      , 0xfa58, , , , , , , , )
XDATABIT( DMA_UR3R_CR       , 0xfa59, , , , , , , , )
XDATABIT( DMA_UR3R_STA      , 0xfa5a, , , , , , , , )
XDATABIT( DMA_UR3R_AMT      , 0xfa5b, , , , , , , , )
XDATABIT( DMA_UR3R_DONE     , 0xfa5c, , , , , , , , )
XDATABIT( DMA_UR3R_RXAH     , 0xfa5d, , , , , , , , )
XDATABIT( DMA_UR3R_RXAL     , 0xfa5e, , , , , , , , )

XDATABIT( DMA_UR4T_CFG      , 0xfa60, , , , , , , , )
XDATABIT( DMA_UR4T_CR       , 0xfa61, , , , , , , , )
XDATABIT( DMA_UR4T_STA      , 0xfa62, , , , , , , , )
XDATABIT( DMA_UR4T_AMT      , 0xfa63, , , , , , , , )
XDATABIT( DMA_UR4T_DONE     , 0xfa64, , , , , , , , )
XDATABIT( DMA_UR4T_TXAH     , 0xfa65, , , , , , , , )
XDATABIT( DMA_UR4T_TXAL     , 0xfa66, , , , , , , , )
XDATABIT( DMA_UR4R_CFG      , 0xfa68, , , , , , , , )
XDATABIT( DMA_UR4R_CR       , 0xfa69, , , , , , , , )
XDATABIT( DMA_UR4R_STA      , 0xfa6a, , , , , , , , )
XDATABIT( DMA_UR4R_AMT      , 0xfa6b, , , , , , , , )
XDATABIT( DMA_UR4R_DONE     , 0xfa6c, , , , , , , , )
XDATABIT( DMA_UR4R_RXAH     , 0xfa6d, , , , , , , , )
XDATABIT( DMA_UR4R_RXAL     , 0xfa6e, , , , , , , , )

XDATABIT( DMA_LCM_CFG       , 0xfa70, , , , , , , , )
XDATABIT( DMA_LCM_CR        , 0xfa71, , , , , , , , )
XDATABIT( DMA_LCM_STA       , 0xfa72, , , , , , , , )
XDATABIT( DMA_LCM_AMT       , 0xfa73, , , , , , , , )
XDATABIT( DMA_LCM_DONE      , 0xfa74, , , , , , , , )
XDATABIT( DMA_LCM_TXAH      , 0xfa75, , , , , , , , )
XDATABIT( DMA_LCM_TXAL      , 0xfa76, , , , , , , , )
XDATABIT( DMA_LCM_RXAH      , 0xfa77, , , , , , , , )
XDATABIT( DMA_LCM_RXAL      , 0xfa78, , , , , , , , )

/////////////////////////////////////////////////
//USB Control Regiter
/////////////////////////////////////////////////

//sfr       USBCLK      =           0xdc;
//sfr       USBDAT      =           0xec;
//sfr       USBCON      =           0xf4;
//sfr       USBADR      =           0xfc;

//使用方法:
//      char dat;
//
//      READ_USB(CSR0, dat);        //读USB寄存器
//      WRITE_USB(FADDR, 0x00);     //写USB寄存器

#define     READ_USB(reg, dat)          \
            {                           \
                while (USBADR & 0x80);  \
                USBADR = (reg) | 0x80;  \
                while (USBADR & 0x80);  \
                (dat) = USBDAT;         \
            }

#define     WRITE_USB(reg, dat)         \
            {                           \
                while (USBADR & 0x80);  \
                USBADR = (reg) & 0x7f;  \
                USBDAT = (dat);         \
            }

#define     USBBASE                 0
#define     FADDR                   (USBBASE + 0)
#define     UPDATE                  0x80
#define     POWER                   (USBBASE + 1)
#define     ISOUD                   0x80
#define     USBRST                  0x08
#define     USBRSU                  0x04
#define     USBSUS                  0x02
#define     ENSUS                   0x01
#define     INTRIN1                 (USBBASE + 2)
#define     EP5INIF                 0x20
#define     EP4INIF                 0x10
#define     EP3INIF                 0x08
#define     EP2INIF                 0x04
#define     EP1INIF                 0x02
#define     EP0IF                   0x01
#define     INTROUT1                (USBBASE + 4)
#define     EP5OUTIF                0x20
#define     EP4OUTIF                0x10
#define     EP3OUTIF                0x08
#define     EP2OUTIF                0x04
#define     EP1OUTIF                0x02
#define     INTRUSB                 (USBBASE + 6)
#define     SOFIF                   0x08
#define     RSTIF                   0x04
#define     RSUIF                   0x02
#define     SUSIF                   0x01
#define     INTRIN1E                (USBBASE + 7)
#define     EP5INIE                 0x20
#define     EP4INIE                 0x10
#define     EP3INIE                 0x08
#define     EP2INIE                 0x04
#define     EP1INIE                 0x02
#define     EP0IE                   0x01
#define     INTROUT1E               (USBBASE + 9)
#define     EP5OUTIE                0x20
#define     EP4OUTIE                0x10
#define     EP3OUTIE                0x08
#define     EP2OUTIE                0x04
#define     EP1OUTIE                0x02
#define     INTRUSBE                (USBBASE + 11)
#define     SOFIE                   0x08
#define     RSTIE                   0x04
#define     RSUIE                   0x02
#define     SUSIE                   0x01
#define     FRAME1                  (USBBASE + 12)
#define     FRAME2                  (USBBASE + 13)
#define     INDEX                   (USBBASE + 14)
#define     INMAXP                  (USBBASE + 16)
#define     CSR0                    (USBBASE + 17)
#define     SSUEND                  0x80
#define     SOPRDY                  0x40
#define     SDSTL                   0x20
#define     SUEND                   0x10
#define     DATEND                  0x08
#define     STSTL                   0x04
#define     IPRDY                   0x02
#define     OPRDY                   0x01
#define     INCSR1                  (USBBASE + 17)
#define     INCLRDT                 0x40
#define     INSTSTL                 0x20
#define     INSDSTL                 0x10
#define     INFLUSH                 0x08
#define     INUNDRUN                0x04
#define     INFIFONE                0x02
#define     INIPRDY                 0x01
#define     INCSR2                  (USBBASE + 18)
#define     INAUTOSET               0x80
#define     INISO                   0x40
#define     INMODEIN                0x20
#define     INMODEOUT               0x00
#define     INENDMA                 0x10
#define     INFCDT                  0x08
#define     OUTMAXP                 (USBBASE + 19)
#define     OUTCSR1                 (USBBASE + 20)
#define     OUTCLRDT                0x80
#define     OUTSTSTL                0x40
#define     OUTSDSTL                0x20
#define     OUTFLUSH                0x10
#define     OUTDATERR               0x08
#define     OUTOVRRUN               0x04
#define     OUTFIFOFUL              0x02
#define     OUTOPRDY                0x01
#define     OUTCSR2                 (USBBASE + 21)
#define     OUTAUTOCLR              0x80
#define     OUTISO                  0x40
#define     OUTENDMA                0x20
#define     OUTDMAMD                0x10
#define     COUNT0                  (USBBASE + 22)
#define     OUTCOUNT1               (USBBASE + 22)
#define     OUTCOUNT2               (USBBASE + 23)
#define     FIFO0                   (USBBASE + 32)
#define     FIFO1                   (USBBASE + 33)
#define     FIFO2                   (USBBASE + 34)
#define     FIFO3                   (USBBASE + 35)
#define     FIFO4                   (USBBASE + 36)
#define     FIFO5                   (USBBASE + 37)
#define     UTRKCTL                 (USBBASE + 48)
#define     UTRKSTS                 (USBBASE + 49)

/*******************STC8H系列单片机全部中断向量及其入口地址********************/

#define PACK
#ifdef PACK

#define  INT0_VECTOR     VECT(  0, 0x03 + 0x3000 )
#define  Timer0_VECTOR   VECT(  1, 0x0b + 0x3000 )
#define  INT1_VECTOR     VECT(  2, 0x13 + 0x3000 )
#define  Timer1_VECTOR   VECT(  3, 0x1b + 0x3000 )
#define  UART1_VECTOR    VECT(  4, 0x23 + 0x3000 )
#define  ADC_VECTOR      VECT(  5, 0x2b + 0x3000 )
#define  LVD_VECTOR      VECT(  6, 0x33 + 0x3000 )
#define  PCA_VECTOR      VECT(  7, 0x3b + 0x3000 )     
#define  UART2_VECTOR    VECT(  8, 0x43 + 0x3000 )
#define  SPI_VECTOR      VECT(  9, 0x4b + 0x3000 )
#define  INT2_VECTOR     VECT(  10, 0x53 + 0x3000 )
#define  INT3_VECTOR     VECT(  11, 0x5b + 0x3000 )
#define  Timer2_VECTOR   VECT(  12, 0x63 + 0x3000 )   
#define  User_VECTOR   VECT(  13, 0x6b + 0x3000 )   
#define  INT4_VECTOR     VECT(  16, 0x83 + 0x3000 )
#define  UART3_VECTOR    VECT(  17, 0x8b + 0x3000 )
#define  UART4_VECTOR    VECT(  18, 0x93 + 0x3000 )
#define  Timer3_VECTOR   VECT(  19, 0x9b + 0x3000 )
#define  Timer4_VECTOR   VECT(  20, 0xa3 + 0x3000 )
#define  CMP_VECTOR      VECT(  21, 0xab + 0x3000 )
#define  I2C_VECTOR      VECT(  24, 0xc3 + 0x3000 )
#define  USB_VECTOR      VECT(  25, 0xcb + 0x3000 )
#define  PWMA_VECTOR   VECT(  26, 0xd3 + 0x3000 )
#define  PWMB_VECTOR   VECT(  27, 0xdb + 0x3000 )
#define  TKSU_VECTOR     VECT(  35, 0x11b + 0x3000 )
#define  RTC_VECTOR      VECT(  36, 0x123 + 0x3000 )
#define  P0INT_VECTOR   VECT(  37, 0x12b + 0x3000 )
#define  P1INT_VECTOR   VECT(  38, 0x133 + 0x3000 )
#define  P2INT_VECTOR   VECT(  39, 0x13b + 0x3000 )
#define  P3INT_VECTOR   VECT(  40, 0x143 + 0x3000 )
#define  P4INT_VECTOR   VECT(  41, 0x14b + 0x3000 )
#define  P5INT_VECTOR   VECT(  42, 0x153 + 0x3000 )
#define  P6INT_VECTOR   VECT(  43, 0x15b + 0x3000 )
#define  P7INT_VECTOR   VECT(  44, 0x163 + 0x3000 )

#define  DMA_M2M_VECTOR   VECT(  47, 0x17b + 0x3000 )
#define  DMA_ADC_VECTOR    VECT(  48, 0x183 + 0x3000 )
#define  DMA_SPI_VECTOR      VECT(  49, 0x18b + 0x3000 )
#define  DMA_UR1T_VECTOR   VECT(  50, 0x193 + 0x3000 )
#define  DMA_UR1R_VECTOR  VECT(  51, 0x19b + 0x3000 )
#define  DMA_UR2T_VECTOR   VECT(  52, 0x1a3 + 0x3000 )
#define  DMA_UR2R_VECTOR  VECT(  53, 0x1ab + 0x3000 )
#define  DMA_UR3T_VECTOR   VECT(  54, 0x1b3 + 0x3000 )
#define  DMA_UR3R_VECTOR  VECT(  55, 0x1bb + 0x3000 )
#define  DMA_UR4T_VECTOR   VECT(  56, 0x1c3 + 0x3000 )
#define  DMA_UR4R_VECTOR  VECT(  57, 0x1cb + 0x3000 )
#define  DMA_LCM_VECTOR   VECT(  58, 0x1d3 + 0x3000 )
#define  LCM_VECTOR   VECT(  59, 0x1db + 0x3000 )

#else

#define  INT0_VECTOR     VECT(  0, 0x03 + 0 )
#define  Timer0_VECTOR   VECT(  1, 0x0b + 0 )
#define  INT1_VECTOR     VECT(  2, 0x13 + 0 )
#define  Timer1_VECTOR   VECT(  3, 0x1b + 0 )
#define  UART1_VECTOR    VECT(  4, 0x23 + 0 )
#define  ADC_VECTOR      VECT(  5, 0x2b + 0 )
#define  LVD_VECTOR      VECT(  6, 0x33 + 0 )
#define  PCA_VECTOR      VECT(  7, 0x3b + 0 )     
#define  UART2_VECTOR    VECT(  8, 0x43 + 0 )
#define  SPI_VECTOR      VECT(  9, 0x4b + 0 )
#define  INT2_VECTOR     VECT(  10, 0x53 + 0 )
#define  INT3_VECTOR     VECT(  11, 0x5b + 0 )
#define  Timer2_VECTOR   VECT(  12, 0x63 + 0 )   
#define  User_VECTOR   VECT(  13, 0x6b + 0 )   
#define  INT4_VECTOR     VECT(  16, 0x83 + 0 )
#define  UART3_VECTOR    VECT(  17, 0x8b + 0 )
#define  UART4_VECTOR    VECT(  18, 0x93 + 0 )
#define  Timer3_VECTOR   VECT(  19, 0x9b + 0 )
#define  Timer4_VECTOR   VECT(  20, 0xa3 + 0 )
#define  CMP_VECTOR      VECT(  21, 0xab + 0 )
#define  I2C_VECTOR      VECT(  24, 0xc3 + 0 )
#define  USB_VECTOR      VECT(  25, 0xcb + 0 )
#define  PWMA_VECTOR   VECT(  26, 0xd3 + 0 )
#define  PWMB_VECTOR   VECT(  27, 0xdb + 0 )
#define  TKSU_VECTOR     VECT(  35, 0x11b + 0 )
#define  RTC_VECTOR      VECT(  36, 0x123 + 0 )
#define  P0INT_VECTOR   VECT(  37, 0x12b + 0 )
#define  P1INT_VECTOR   VECT(  38, 0x133 + 0 )
#define  P2INT_VECTOR   VECT(  39, 0x13b + 0 )
#define  P3INT_VECTOR   VECT(  40, 0x143 + 0 )
#define  P4INT_VECTOR   VECT(  41, 0x14b + 0 )
#define  P5INT_VECTOR   VECT(  42, 0x153 + 0 )
#define  P6INT_VECTOR   VECT(  43, 0x15b + 0 )
#define  P7INT_VECTOR   VECT(  44, 0x163 + 0 )

#define  DMA_M2M_VECTOR   VECT(  47, 0x17b + 0 )
#define  DMA_ADC_VECTOR    VECT(  48, 0x183 + 0 )
#define  DMA_SPI_VECTOR      VECT(  49, 0x18b + 0 )
#define  DMA_UR1T_VECTOR   VECT(  50, 0x193 + 0 )
#define  DMA_UR1R_VECTOR  VECT(  51, 0x19b + 0 )
#define  DMA_UR2T_VECTOR   VECT(  52, 0x1a3 + 0 )
#define  DMA_UR2R_VECTOR  VECT(  53, 0x1ab + 0 )
#define  DMA_UR3T_VECTOR   VECT(  54, 0x1b3 + 0 )
#define  DMA_UR3R_VECTOR  VECT(  55, 0x1bb + 0 )
#define  DMA_UR4T_VECTOR   VECT(  56, 0x1c3 + 0 )
#define  DMA_UR4R_VECTOR  VECT(  57, 0x1cb + 0 )
#define  DMA_LCM_VECTOR   VECT(  58, 0x1d3 + 0 )
#define  LCM_VECTOR   VECT(  59, 0x1db + 0 )

#endif

#ifdef __IAR_SYSTEMS_ICC__
#pragma language=default
#endif

/**************************************************************************************************
 */
#endif
