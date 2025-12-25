//#include <Arduboy2.h>
//#include <ArduboyTones.h>
//Arduboy2Base arduboy;
//ArduboyTones sound(arduboy.audio.enabled);
//Sprites sprites;


#include "STC8H.h"
#include "TYPE.h"
#include "Graphic.c"
#include "oled.c"
#include "ADC.c"
#include "Key.c"
#include "Game.h"
#include "Draw.h"
#include "FixedMath.h"
#include "Platform.h"
#include "SpriteData.inc.h"
#include "Sounds.h"
#define 	MAIN_Fosc		40000000L	//定义主时钟

#define Wifi P20
#define Audio P21 
#define laser P13 
#define light P17 
#define beep P54

void delayms(uint t){
    uint16_t i;
    while(t--) for(i=0;i<600;i++);
}


uint16_t i;


// Generate Sound

#define TONES_END 0x8000
uint16_t now_freq;
uint8_t now_dura;
uint8_t flag = 0;
const uint16_t __code  *sound_array;

uint8_t status = 0,ptr = 0;

void Tones(const uint16_t __code *s){
    sound_array = s;
    ptr = 0;
    status = 1;
    now_freq = 0;
    now_dura = 0;
   // ptr +=2;
}
void Buzzer_Poll(){
    if(status){
        if(now_freq == TONES_END || now_dura==TONES_END){
            beep = 0;
            status = 0;
            ptr = 0;
            now_dura = 0;
            IE2 &=(~0x04);
            AUXR &= (~0x10);
            return;
        }else{
            IE2 |= 0x04;
            AUXR |= 0x10;
            uint16_t reload = MAIN_Fosc/now_freq;
            T2L = reload;
            reload >>= 8;
            T2H = reload;
              
            if(now_dura > 0){
                now_dura--;
                return;
            }else{        
                now_freq = sound_array[ptr];
                now_dura = sound_array[ptr + 1];
                ptr += 2;
                return;
            }
        }
    }
}

uint8_t	Timer1_Init()	//1000Hz
{
  	AUXR |= 0x40;			//定时器时钟1T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0xC0;				//设置定时初始值
	TH1 = 0x63;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断

	return 0;
}
uint8_t	Timer2_Init()	
{
 	AUXR |= 0x04;			//定时器时钟1T模式
	T2L = 0xC0;				//设置定时初始值
	T2H = 0x63;				//设置定时初始值
	AUXR |= 0x10;			//定时器2开始计时
	IE2 |= 0x04;			//使能定时器2中
	return 0;
}


uint8_t Platform::GetInput()
{

    uint8_t result = 0,kr,kl;    
    kl=Key_Scan()>>8;
    kr=Key_Scan();
    
  if(kl==0x41)
  {
    result |= INPUT_B;  
  }
  if(kl==0x58)
  {
    result |= INPUT_A;  
  }
  if(kl==0x43)
  {
    result |= INPUT_C;  
  }
  if(kr==0x44)
  {
    result |= INPUT_UP;  
  }
  if(kr==0x49)
  {
    result |= INPUT_DOWN;  
  }
  if(kr==0x48)
  {
    result |= INPUT_LEFT;  
  }
  if(kr==0x4a)
  {
    result |= INPUT_RIGHT;  
  }
    return result;
}


void Platform::PlaySound(const uint16_t __code *audioPattern)
{
        Tones(audioPattern);
	//tones(audioPattern);
}

void Platform::SetLED(uint8_t r, uint8_t g, uint8_t b)
{
    return;
}

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
    Graphic_DrawPoint((uint8_t)x,(uint8_t)y,colour);
}

// Adpated from https://github.com/a1k0n/arduboy3d/blob/master/draw.cpp
// since the AVR has no barrel shifter, we'll do a progmem lookup
const uint8_t topmask_[] PROGMEM = {
  0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80 };
const uint8_t bottommask_[] PROGMEM = {
  0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };

void Platform::DrawVLine(uint8_t x, int8_t y0_, int8_t y1_, uint8_t pattern) 
{
    uint8_t *screenptr = Graphic_GetBuffer() + x;

    if (y1_ < y0_ || y1_ < 0 || y0_ > 63) return;

  // clip (FIXME; clipping should be handled elsewhere)
  // cast to unsigned after clipping to simplify generated code below
    uint8_t y0 = y0_, y1 = y1_;
    if (y0_ < 0) y0 = 0;
    if (y1_ > 63) y1 = 63;

    uint8_t *page0 = screenptr + ((y0 & 0x38) << 4);
    uint8_t *page1 = screenptr + ((y1 & 0x38) << 4);
    if (page0 == page1) 
    {
        uint8_t mask = pgm_read_byte(topmask_ + (y0 & 7))
        & pgm_read_byte(bottommask_ + (y1 & 7));
        *page0 &= ~mask;
        *page0 |= pattern & mask;  // fill y0..y1 in same page in one shot
    }
    else
    {
        uint8_t mask = pgm_read_byte(topmask_ + (y0 & 7));
        *page0 &= ~mask;
        *page0 |= pattern & mask;  // write top 1..8 pixels
        page0 += 128;
        while (page0 != page1) 
        {
        *page0 = pattern;  // fill middle 8 pixels at a time
        page0 += 128;
        }
        mask = pgm_read_byte(bottommask_ + (y1 & 7));  // and bottom 1..8 pixels
        *page0 &= ~mask;
        *page0 |= pattern & mask;
    }
}

uint8_t* Platform::GetScreenBuffer()
{
    return Graphic_GetBuffer();
}



void Platform::DrawBitmap(int16_t sx, int16_t sy, const uint8_t *bitmap,const uint8_t *alpha)
{
    uint8_t w = pgm_read_byte(&bitmap[0]);
    uint8_t h = pgm_read_byte(&bitmap[1]);
    uint x,y,nowx,nowy;
    uint8_t pixel;
    const uint8_t* BMP = bitmap+2;
    const uint8_t* ALPHA = alpha + 2;
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            nowy=sy+y;
            nowx=sx+x;
            if(ALPHA[(uint8_t)(y/8)*w+x]&(0x01<<(uint8_t)(y%8))){
                pixel=BMP[(uint8_t)(y/8)*w+x]&(0x01<<(uint8_t)(y%8));
                Graphic_DrawPoint(nowx,nowy,!pixel);//手的贴图取模后不小心反色了，，，之后用！修正一下
            }
         }
    }
    return;
}   


void Platform::FillScreen(uint8_t colour)
{
    //arduboy.fillScreen(colour);
    if(colour) Graphic_ClearBufferBit(1);
    else if(colour) Graphic_ClearBufferBit(0);
}


bool Platform::IsAudioEnabled()
{
	if(Audio == 0) return 0;//return arduboy.audio.enabled();
        return 1;
}

void Platform::SetAudioEnabled(bool isEnabled)
{
    if(isEnabled){
        Audio = 1;
        //arduboy.audio.on();
    }else{
        Audio = 0;
        //arduboy.audio.off();
    }
}

void Platform::ExpectLoadDelay()
{
    // Resets the timer so that we don't tick multiple times after a level load
    //lastTimingSample = millis();
}

void setup()
{
  //arduboy.boot();
  //arduboy.flashlight();
  //arduboy.systemButtons();
  //arduboy.bootLogo();
  //arduboy.setFrameRate(TARGET_FRAMERATE);

  //arduboy.audio.off();
  
  //Serial.begin(9600);

//  SeedRandom((uint16_t) arduboy.generateRandomSeed());
  Game::Init();
  
  //lastTimingSample = millis();
}
/*
void loop()
{
  static int16_t tickAccum = 0;
  unsigned long timingSample = millis();
  tickAccum += (timingSample - lastTimingSample);
  lastTimingSample = timingSample;
	
#if DEV_MODE
  if(arduboy.nextFrameDEV())
#else
  if(arduboy.nextFrame())
#endif
  {
	constexpr int16_t frameDuration = 1000 / TARGET_FRAMERATE;
	while(tickAccum > frameDuration)
	{
		Game::Tick();
		tickAccum -= frameDuration;
	}
	
	Game::Draw();
    
    //Serial.write(arduboy.getBuffer(), 128 * 64 / 8);

#if DEV_MODE
	// CPU load bar graph	
	int load = arduboy.cpuLoad();
	uint8_t* screenPtr = arduboy.getBuffer();
	
	for(int x = 0; x < load && x < 128; x++)
	{
		screenPtr[x] = (screenPtr[x] & 0xf8) | 3;
	}
	screenPtr[100] = 0;
#endif
	
    arduboy.display(false);
  }
}
*/
long int timing_start,timing_end,ms = 0,ms_cnt = 0;
uint8_t show_fps = 0;
uint8_t Mini_Map = 0;
int main(){
    uint8_t Frame_Skip=3;
    P0M0=0x00;
    P0M1=0x00;
    P1M1=0x3f; 
    P1M0=0x00;   //设置为高阻抗
    P2M0=0x00;
    P2M1=0x00;
    P3M0=0x00;
    P3M1=0x00;
    P5M0=0x00;
    P5M1=0x00;
    P3=0xff;
    Wifi=0;
    Audio=0;
    laser=0;
    light=0;    
    ADC_Init();
    OLED_Init();
    OLED_ColorTurn(0);
    OLED_Display_On();
    OLED_Clear();   
    Graphic_ClearBufferBit(0);
    Graphic_Flush();
    Game::Init();
    Timer1_Init();
    Timer2_Init();
    EA = 1;;
    IE2 &=(~0x04);
    AUXR &= (~0x10);
    while(1){
        //timing_start = ms;
        //Graphic_Printf(0,0,"%d",Platform::GetInput());
        show_fps = (Platform::GetInput() & INPUT_C) ? 1:0;
        Mini_Map = (Platform::GetInput() & INPUT_A) ? 1:0;
        Game::Tick();
        Frame_Skip++;
        if(Frame_Skip>2){
            Frame_Skip=0;
            Game::Draw(); 
            //if(show_fps == 1 ||1) Graphic_Printf(0,0,"%.1f",1000.0/ms_cnt);
            Graphic_Flush();
            Graphic_ClearBufferBit(0);
            timing_end = ms;
            //ms_cnt = timing_end - timing_start;
        }
    }
    return 0;
}
#pragma vector=Timer1_VECTOR
__interrupt void timer1_Isr()
{      
    Buzzer_Poll();
    ms ++;
    //if(light) light =0;
    //else light = 1;
    //light = ~light;
    //for(int i = 0;i < 150; i++);
    //light = 0;
    //for(int i = 0;i < 150; i++);
}
#pragma vector=Timer2_VECTOR
__interrupt void timer2_Isr()
{    
    beep =~beep;  
    //Buzzer_Poll();
    //if(light) light =0;
    //else light = 1;
    //light = ~light;
    //for(int i = 0;i < 150; i++);
    //light = 0;
    //for(int i = 0;i < 150; i++);
}