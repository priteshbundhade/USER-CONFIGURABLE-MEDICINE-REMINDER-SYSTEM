#include<lpc21xx.h>
#include"types.h"
#include"rtc_defines.h"
#include"lcd.h"
#include"lcd_defines.h"
// Array to hold names of days of the week
s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// declare the peripherals
//s32 hour,min,sec,date,month,year,day;
void InitRTC()
{
  //Disable and reset the RTC
  CCR = RTC_RESET;
  
  #ifndef _LPC2148  
  // Set prescaler integer and fractional parts
        PREINT = PREINT_VAL;
        PREFRAC = PREFRAC_VAL;
  
  // Enable the RTC^M
        CCR = RTC_ENABLE; 

        #else
  // Enable the RTC with external clock source
        CCR = RTC_ENABLE | RTC_CLKSRC;  
        #endif  
}

void SetRTCTime(s32 hour, s32 min, s32 sec)
{
  /*
  Set the RTC time
  Hour to set (0-23)
  Minute to set (0-59)
  Second to set (0-59)
*/
  HOUR = hour;
  MIN = min;
  SEC = sec;
}


void GetRTCTime(s32 *hour,s32 *min, s32 *sec)
{
/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
  *hour = HOUR;
  *min = MIN;
  *sec = SEC;

}
void DisplayRTCTime(s32 hour, s32 min, s32 sec)
{
  /*Display the RTC time on LCD
  hour value (0-23)
  minute value (0-59)
  second value (0-59) seperated by ':'
*/
  CmdLCD(GOTO_LINE1_POS0);
  CharLCD(hour/10+48);
  CharLCD(hour%10+48);
  CharLCD(':');
  CharLCD(min/10+48);
  CharLCD(min%10+48);
  CharLCD(':');
  CharLCD(sec/10+48);           
  CharLCD(sec%10+48);   
}

void SetRTCDate(s32 date,s32 month, s32 year)
{
     /*
  Set the RTC date
  day of month to set (1-31)
  month to set (1-12)
  year to set (four digits)*/
   DOM = date;
   MONTH = month;
   YEAR = year;
}


void GetRTCDate(s32 *date, s32 *month, s32 *year)
{
/*
Get the current RTC date
day Pointer to store the current date (1-31)
month Pointer to store the current month (1-12)
year Pointer to store the current year (four digits)
*/
  *date = DOM;
  *month = MONTH; 
  *year = YEAR;
}

void DisplayRTCDate(s32 date, s32 month, s32 year)
{
  /*
  Display the RTC date on LCD
  Day of month (1-31)
  Month (1-12)
  Year (four digits) and seperated by '/'
  */
  CmdLCD(GOTO_LINE2_POS0);
  CharLCD(date/10+48);
  CharLCD(date%10+48);
  CharLCD('/');
  CharLCD(month/10+48);
  CharLCD(month%10+48);
  CharLCD('/');
  U32LCD(year);
}


void SetRTCDay(s32 dow)
{  
   /*
    Set the current day of the week
        dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
         DOW = dow; 
}

void GetRTCDay(s32 *dow)
{
   /*
   Get the current day of the week
   dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
  */
    *dow = DOW;
}

void DisplayRTCDay(s32 dow)
{
  /*
  Display the current day of the week on LCD
  dow (Day of Week) (0=Sunday, ..., 6=Saturday)
  */
  CmdLCD(GOTO_LINE2_POS0+12);
  StrLCD(week[dow]);
}
