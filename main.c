#include"headers.h"
// Declaration of minutes and hours for medicine slots
s32 h1,m1,h2,m2,h3,m3;

// Declaration for RTC time,date & day
s32 hour = 8,min = 29,sec = 30;
s32 date = 3,month = 5,year = 2026;
s32 day = THU;
u32 val,dly,flag1,flag2;
u8 Option;
int main()
{
 // Initialize RTC 
    InitRTC();
	
 // Initialize LCD
    InitLCD();
	
 // Initialize KPM 
    InitKPM();
	
	// Initialize External Interrupts 
    InitSwitchInterrupt();

 // Set the initial time (hours, minutes, seconds)
        SetRTCTime(hour,min,sec);

 // Set the initial data (date, month, year)
        SetRTCDate(date,month,year);

 // Set initial day (SUN to SAT )
        SetRTCDay(day);
   while(1)      
   {
    // Display RTC time,date & day
        Display_RTC();            
		 
	  // If Switch 1 is pressed its shows the options on the display
       if(flag1)
			 {
				 flag1 = 0;
				 Switch1();
			 }
		// If RTC time matched with any medicine slot Buzzer should beep
      if(Check_medicine_time())
			{
				      dly = 60;
				    // Timings matched with the slot first lcd is Clearing and Printing  the message
               CmdLCD(CLEAR_LCD);
               StrLCD("Take Medicine");
            // Buzzer is beeping until switch 2 is not pressed 
               IOSET0 = 1 << BUZ;
					 
               while(dly)
               {   
								 // If flag2 == 1 ie, Switch 2 is pressed now buzzer gets OFF
                     if(flag2)
										 {
											  flag2 = 0;
											 // Buzzer stops beeping
											  IOCLR0 = 1 << BUZ;
                        break;											 
										 }											 
								 // Clear the LCD first and Display the Real time Clock 
                       delay_s(1);
                       dly--;
               }
               // If switch 2 is not pressed till 1 min buzzer automatically stops beeping 
               if(dly == 0)
							 {
                      IOCLR0 = 1 << BUZ;
							 }
							 // Clear LCD and again display RTC
									CmdLCD(CLEAR_LCD);
							 
			}
	 }
}

void Display_RTC()
{
  // Get & display RTC time
        GetRTCTime(&hour,&min,&sec);
        DisplayRTCTime(hour,min,sec);

  // Get & display RTC Date
        GetRTCDate(&date,&month,&year);
        DisplayRTCDate(date,month,year);

  // Get & display RTC day
        GetRTCDay(&day);
        DisplayRTCDay(day);     
}


u32 Check_medicine_time()
{
	if(((h1 == hour) && (m1 == min) && (sec == 0)) || 
		((h2 == hour) && (m2 == min) && (sec == 0)) || 
	  ((h3 == hour) && (m3 == min) && (sec == 0)))
  {
     return 1;
	}
	return 0;
}
