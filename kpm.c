#include<lpc21xx.h>
#include"types.h"
#include"kpm_defines.h"
#include"kpm.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"defines.h"
#include"delay.h"
u32 kpmLUT[4][4] = {{'7','8','9','/'},
                    {'4','5','6','*'},
                    {'1','2','3','-'},
                    {'B','0','E','+'}
									} ;        
/*u8 kpmLUT[4][4] = {
                   {'7','8','9','+'},
                   {'4','5','6','-'},
                   {'1','2','3','='},
                   {'C','0','E','B'}
                  };*/

void InitKPM(void)
{
  WNIBBLE(IODIR1,ROW0,15);
}

u32 ColScan(void)
{
  return((RNIBBLES(IOPIN1,COL0)<15)?0:1);
}

u32 RowCheck(void)
{
  u32 rno;
  for(rno=0;rno<4;rno++)
  {
    WNIBBLE(IOPIN1,ROW0,~(1<<rno));
    if(ColScan()==0)
            break;
  }
  //Make rows as default 
	WNIBBLE(IOPIN1,ROW0,0) ;
  return rno;
}

u32 ColCheck(void)
{
  u32 cno;
  for(cno=0;cno<4;cno++)
  {
    if(RBIT(IOPIN1,COL0+cno)==0)
          break;
  }
  return cno;
}


u32 KeyScan(void)
{
  u32 rno,cno;
  u8 keyv;

  //wait for switch press
  while(ColScan());

  //find the row no.
  rno = RowCheck();

  //find the col no.
  cno = ColCheck();

  //get the value using kpmLUT
  keyv = kpmLUT[rno][cno];

  //Wait for switch release
  while(!(ColScan()));
  delay_ms(100);
  return keyv;
}

u32 ReadNum(void)
{
  u8 key;
  u32 sum=0;
  while(1)
  {
       key = KeyScan();
       if(key>='0'  && key<='9')
       {
				 CharLCD(key);
         sum = (sum*10)+(key-'0');
       }
			 else if (key == 'E')
			 {
				 break;
			 }			
       else if(key =='C')
       {
          CmdLCD(0x01);
					break;
			 }
       else if(key =='B')
       {
				 if(sum>0)
				 {
          CmdLCD(SHIFT_DISP_LEFT);
					 sum /= 10;
          CharLCD(' ');
          CmdLCD(SHIFT_DISP_LEFT);
				 }
       }
  }
  return sum;
}



