#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"lcd_defines.h"
#include"rtc_defines.h"
#include"lcd.h"
#include"kpm.h"
#include"rtc.h"

#define BUZ 19             // @p0.19

#define EINT0_INPUT_SW 0x0000000C   // @p0.1 (EINT0)
#define EINT0_VIC_CHNO 14  

#define EINT1_INPUT_SW 0x000000C0   // @p0.3 (EINT0)
#define EINT1_VIC_CHNO 15

// Declaration of interrupt request function
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;

void InitSwitchInterrupt(void);

// Declaration of minutes and hours for medicine slots
extern s32 h1,m1,h2,m2,h3,m3;

// Declaration for RTC time,date & day
extern s32 hour ,min, sec;
extern s32 date ,month ,year;
extern s32 day ;
extern u32 val,dly,flag1,flag2;
extern u8 Option;

//Function declarations
void Display_RTC(void);
void EnterRTCTime(s32 *hour,s32 *min,s32 *sec);
void Set_Medicine_Time(void);
u32 Check_medicine_time(void);
void InitSwitchInterrupt(void);
void Switch1(void);
u32 Enter_hour(void);
u32 Enter_min(void);
u32 Enter_sec(void);

