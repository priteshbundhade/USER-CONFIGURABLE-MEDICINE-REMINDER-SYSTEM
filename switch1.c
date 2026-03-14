#include"headers.h"
void Switch1()
{
	// After pressing switch 1 First LCD is clearing and display the options
	CmdLCD(CLEAR_LCD);
	
	//Option 1 for Editing the RTC time 
	StrLCD("1: Edit RTC Time");
	
	//Option 2 for scheduling medicine which displays on Line 2
  CmdLCD(GOTO_LINE2_POS0);
  StrLCD("2: Set Med Time");

    //Option 3 for exit 
  CmdLCD(GOTO_LINE3_POS0);
  StrLCD("3: Exit");
	
	// Enter the Option 
  Option = KeyScan();

	if(Option == '1')
  {
     //Enter & Reset the Clock timings
        EnterRTCTime(&hour,&min,&sec);
        SetRTCTime(hour,min,sec);
                 
     //Clear the LCD & show the message of Clock Time reset
        CmdLCD(CLEAR_LCD);
        StrLCD("Time Reset");
  }
  else if(Option == '2')
  {
		 //Set the medicine slots according to the requirement
       Set_Medicine_Time();
		
		// Clear the LCD and display the message 
       CmdLCD(CLEAR_LCD);
       StrLCD("Slots saved");
  }
	else if(Option == '3')
	{
		//Clear the LCD and go back to Home
		CmdLCD(CLEAR_LCD);
		return;
	}
	// after 1 sec delay again clear the LCD and show RTC clock
	      delay_s(1);
		    CmdLCD(CLEAR_LCD);
}

void EnterRTCTime(s32 *hour,s32 *min,s32 *sec)
{
   //First clear the LCD & Enter the hours
   CmdLCD(CLEAR_LCD);
   *hour = Enter_hour();
  
   //Again clear the LCD & Enter the minutes
   CmdLCD(CLEAR_LCD);
   *min = Enter_min();
   
   //Again clear the LCD & Enter seconds^M
   CmdLCD(CLEAR_LCD);
   *sec = Enter_sec();  
}


