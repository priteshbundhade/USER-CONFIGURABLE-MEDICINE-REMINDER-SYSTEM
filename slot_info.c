#include"headers.h"
void Set_Medicine_Time()
{
   //Clear the LCD first & Enter the timings for Slot 1
        CmdLCD(CLEAR_LCD);
        StrLCD("Slot 1:- ");
        CmdLCD(GOTO_LINE2_POS0);
  // Enter the hours for Slot 1
        h1 = Enter_hour();
  // Again Clear the LCD
        CmdLCD(CLEAR_LCD);
        StrLCD("Slot 1:- ");
        CmdLCD(GOTO_LINE2_POS0);
  // Enter the Minutes for slot 1
        m1 = Enter_min();


  //First clear the LCD & Enter the timings for Slot 2
        CmdLCD(CLEAR_LCD);
        StrLCD("Slot 2:- ");
        CmdLCD(GOTO_LINE2_POS0);
  // Enter the hours for slot 2
        h2 = Enter_hour();
  // Again clear the lcd
        CmdLCD(CLEAR_LCD);
        StrLCD("Slot 2:- ");
        CmdLCD(GOTO_LINE2_POS0);
  // Enter the Minutes for slot 2
        m2 = Enter_min();


  //First Clear the LCD & enter the timings for Slot 3
        CmdLCD(CLEAR_LCD);
				StrLCD("Slot 3:- ");
        CmdLCD(GOTO_LINE2_POS0);
	// Enter the hours for slot 3
        h3 = Enter_hour();
  // Clear the LCD again
        CmdLCD(CLEAR_LCD);
        StrLCD("Slot 3:- ");
        CmdLCD(GOTO_LINE2_POS0);
 // Enter the minutes for slot 3
        m3 = Enter_min();

}

u32 Enter_hour()
{
     // Enter Hours
         StrLCD("Hr: ");
         val = ReadNum();
         return val;
}

u32 Enter_min()
{
     // Enter minutes
         StrLCD("Min: ");
         val = ReadNum();
         return val;
}

u32 Enter_sec()
{
     // Enter seconds
         StrLCD("Sec: ");
         val = ReadNum();
         return val;
}
