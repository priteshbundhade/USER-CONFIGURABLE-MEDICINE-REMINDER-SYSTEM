#include"headers.h"
void InitSwitchInterrupt()
{
   //cfg port pin 0.1 &0.3 as EINT0 & EINT1 as i/p pin
   //clear bit pair 2&3 abd bit pair 6&7 w/o affecting other bits
   PINSEL0 &= ((u32)~(3<<2) | ((u32)~3<<6));

   //update bit 2&3, bit 4&5 for EINT0 & EINT1 pin function
   PINSEL0 |= EINT0_INPUT_SW | EINT1_INPUT_SW;

  //cfg VIC peripheral/block
  //allow EINT0 & EINT1 as irq type
  //VICIntSelect = 0; //default
  //Enable EINT0 & EINT1 through channel
  VICIntEnable  = (1<< EINT0_VIC_CHNO) | (1<< EINT1_VIC_CHNO);

  //cfg EINT0 v.irq with highest priority(0)
  VICVectCntl0 =(1<<5)|EINT0_VIC_CHNO;

  //load eint0_isr address into LUT sfr
  VICVectAddr0 = (u32 )eint0_isr;


  //cfg EINT1 v.irq with highest priority(1)
  VICVectCntl1 =(1<<5)|EINT1_VIC_CHNO;
  //load eint1_isr address into LUT sfr
  VICVectAddr1 = (u32 )eint1_isr;

  //cfg EINT0 & EINT1 via External Interrupt Peripheral
  //Enable EINT0 EINT1
  //EXTINT = 0   //default
	
  //cfg EINT0 & EINT1 as edge Triggered Interrupt
    EXTMODE = (1<<0)|(1<<1);
	
	//Falling edge trigger (for Active Low switch)
    EXTPOLAR &= ~((1<<0) | (1<<1));
		
	// cfg port pin 0.16 as an output pin which is buzzer
    IODIR0 |= 1 << BUZ ;
}

void eint0_isr(void) __irq
{
   //Initilize flag1 with 1 
      flag1 = 1;

   //clear EINT0 status in ExtInt Peripheral
      EXTINT = 1<<0;

   //clear EINT0 status in VIC Peripheral
      VICVectAddr = 0;
}

 void eint1_isr(void) __irq
{
	// Initilize flag2 with 1
	   flag2 = 1;

 //clear EINT1 status in ExtInt Peripheral
     EXTINT = 1<<1;
										 
 //clear EINT1 status in VIC Peripheral
     VICVectAddr = 0;	
}  
