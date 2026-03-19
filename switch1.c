#include"headers.h"
void Switch1()
{
    // After pressing switch 1 First LCD is clearing and display the options
        CmdLCD(CLEAR_LCD);

   //Option 1 for Editing the RTC time
        StrLCD("1:Edit RTC Clock");

	//Option 2 for scheduling medicine which displays on Line 2
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("2:Set Med Time");
  
	
//Option 3 for display slot timings
    CmdLCD(GOTO_LINE3_POS0);
  	StrLCD("3:View Slots");

//Option 4 for exit which display RTC again
    CmdLCD(GOTO_LINE3_POS0);
        StrLCD("4:Exit");

  // Enter the Option
    Option = KeyScan();

  if(Option == '1')
  {
     //Enter & Reset the Clock timings
        EnterRTCTime(&hour,&min,&sec);
        SetRTCTime(hour,min,sec);

        //Enter & Reset the Clock Dates
        EnterRTCDate(&date,&month,&year);
        SetRTCDate(date,month,year);

    //Enter & Reset the Clock Day of week
        EnterRTCDay(&day);
        SetRTCDay(day);

     //Clear the LCD & show the message of Clock Time reset
        CmdLCD(CLEAR_LCD);
        StrLCD("Clock Reset");
                flag1 = 0;

     // after 1 sec delay again clear the LCD and show RTC clock
           delay_s(1);
           CmdLCD(CLEAR_LCD);
           return;
  }
  else if(Option == '2')
  {
        //Set the medicine slots according to the requirement
       Set_Medicine_Time();

        // Clear the LCD and display the message
       CmdLCD(CLEAR_LCD);
       StrLCD("Slots saved");

        // after 1 sec delay again clear the LCD and show RTC clock
           delay_s(1);
           CmdLCD(CLEAR_LCD);
           flag1 = 0;
           return;
  }
  else if(Option == '3')
  {
      // Clear LCD first
          CmdLCD(CLEAR_LCD);

          //Display Slot 1 timings
          StrLCD("Slot1:- ");
          U32LCD(h1);
          CharLCD(':');
          U32LCD(m1);

          //Display Slot 2 timings
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("Slot2:- ");
          U32LCD(h2);
          CharLCD(':');
          U32LCD(m2);

          //Display Slot 3 timings
          CmdLCD(GOTO_LINE3_POS0);
          StrLCD("Slot3:- ");
          U32LCD(h3);
          CharLCD(':');
          U32LCD(m3);
          // 5 sec delay again display RTC
          delay_s(5);
  }
  else if(Option == '4')
  {  
      //clear the LCD and show RTC clock
           CmdLCD(CLEAR_LCD);
           flag1=0;
           return; 
  }
}

void EnterRTCTime(s32 *hour,s32 *min,s32 *sec)
{
   //First clear the LCD & Enter the hours
   CmdLCD(CLEAR_LCD);
   *hour = Enter_hour();

   //Again clear the LCD & Enter the minutes
   CmdLCD(CLEAR_LCD);
   *min = Enter_min();

   //Again clear the LCD & Enter seconds
   CmdLCD(CLEAR_LCD);
   *sec = Enter_sec();
}

void EnterRTCDate(s32 *date,s32 *month,s32 *year)
{
   //First clear the LCD & Enter the date
   CmdLCD(CLEAR_LCD);
   *date = Enter_date();

   //Again clear the LCD & Enter the month
   CmdLCD(CLEAR_LCD);
   *month = Enter_month();

   //Again clear the LCD & Enter year
   CmdLCD(CLEAR_LCD);
   *year = Enter_year();
}

void EnterRTCDay(s32 *day)
{
  //First clear the LCD & Enter the day of week
   CmdLCD(CLEAR_LCD);
   *day = Enter_day();        
}

u32 Enter_date()
{
     // Enter Date
         StrLCD("Date(1-31):");
         val = ReadNum();
                 if(val > 31)
                 {  
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Not Valid");
                        CmdLCD(GOTO_LINE2_POS0);
      									StrLCD("Enter b/w 1-31");
                        delay_s(3);
                        CmdLCD(CLEAR_LCD);
                        Enter_date();
                 }
                 return val;
}

u32 Enter_month()
{
     // Enter month
         StrLCD("Month(1-12):");
         val = ReadNum();
                 if(val <= 0 && val > 12)
                 {
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Not Valid");
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("Enter b/w 1-12");
                        delay_s(3);
                        CmdLCD(CLEAR_LCD);
		     							  Enter_month();
                 }
								 return val;
}

u32 Enter_year()
{
     // Enter year
         StrLCD("Year(0-2100):");
         val = ReadNum();
                 if(val >=2100)
                 {  
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Not Valid");
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("Enter b/w 0-2100");
                        delay_s(3);
                        CmdLCD(CLEAR_LCD);
                        Enter_year();
                 }
                 return val;
}
u32 Enter_day()
{
     // Enter Day of week
         StrLCD("Day(0-6):");
         val = ReadNum();
                 if(val > 6 )
                 {  
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Not Valid");
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("Enter b/w 0-6");
                        delay_s(3);
                        CmdLCD(CLEAR_LCD);
                        Enter_day();
                 }
                 return val;
}
