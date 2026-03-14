==============================================================
USER-CONFIGURABLE MEDICINE REMINDER SYSTEM
Target Controller : LPC2148 (ARM7)
Language          : Embedded C
==============================================================

--------------------------------------------------------------
1. PROJECT AIM
--------------------------------------------------------------
This project implements a medicine reminder system using LPC2148.
The system allows the user to configure medicine timings and 
generates an alert (LCD message + buzzer) at the scheduled time.

--------------------------------------------------------------
2. HARDWARE USED
--------------------------------------------------------------
- LPC2148 Microcontroller
- 16x2 LCD
- 4x4 Matrix Keypad
- Buzzer
- Switch-1 (Connected to P0.1 ? EINT0)
- Switch-2 (Connected to P0.3 ? EINT1)
- USB-UART / Flash Magic for programming

--------------------------------------------------------------
3. PIN CONFIGURATION
--------------------------------------------------------------

Switch-1  ? P0.1  ? EINT0  (Active Low, Falling Edge)
Switch-2  ? P0.3  ? EINT1  (Active Low, Falling Edge)

LCD       ? Connected to Port1
Buzzer    ? Connected to Port1 output pin
RTC       ? Internal RTC of LPC2148

--------------------------------------------------------------
4. WORKING PRINCIPLE
--------------------------------------------------------------

1) Normal Mode:
   - RTC continuously runs.
   - Current time displayed on LCD.
   - System compares RTC time with stored medicine times.

2) Switch-1 Pressed (EINT0 Triggered):
   - System enters Configuration Mode.
   - LCD shows menu:
       1. Edit RTC Time
       2. Set Medicine Time
   - User enters data using keypad.
   - Data is stored in memory.
   - System returns to normal mode.

3) Medicine Time Match:
   - LCD displays "Take Medicine Now"
   - Buzzer starts ON/OFF alert pattern.
   - 1-minute timer starts.

4) Switch-2 Pressed (EINT1 Triggered):
   - Buzzer stops immediately.
   - Reminder cleared.
   - System returns to RTC display mode.

5) If no acknowledgment within 1 minute:
   - Buzzer stops automatically.
   - System continues monitoring.

--------------------------------------------------------------
5. INTERRUPT CONFIGURATION
--------------------------------------------------------------

External Interrupt Mode:
    EXTMODE  = Edge Triggered
    EXTPOLAR = Falling Edge (Active Low Switch)

VIC Channels:
    EINT0 ? Channel 14
    EINT1 ? Channel 15

Interrupt Flow:
    Switch Press ? Falling Edge ? VIC ? ISR ? Required Operation

NOTE:
ISR is kept short.
Heavy operations are handled in main program for stability.

--------------------------------------------------------------
6. SOFTWARE FLOW
--------------------------------------------------------------

System Initialization:
    - Configure PLL
    - Initialize LCD
    - Initialize RTC
    - Initialize Keypad
    - Configure External Interrupts
    - Configure Timer

Main Loop:
    while(1)
    {
        Display RTC Time
        Compare RTC with stored medicine schedule
        If match ? Generate Alert
    }

--------------------------------------------------------------
7. FEATURES
--------------------------------------------------------------
- Real-time clock display
- User configurable medicine schedule
- Interrupt-based switch handling
- Automatic alert generation
- 1-minute acknowledgment timeout
- Continuous monitoring

--------------------------------------------------------------
8. IMPORTANT NOTES
--------------------------------------------------------------
- Switches are Active Low.
- Falling edge interrupt is used.
- Clear EXTINT inside ISR.
- Always write VICVectAddr = 0 in ISR end.
- Use external pull-up resistor for switches.

--------------------------------------------------------------
9. FILE STRUCTURE (Example)
--------------------------------------------------------------
main.c          ? Main logic
lcd.c           ? LCD driver
kpm.c           ? Keypad driver
rtc.c           ? RTC configuration
interrupt.c     ? EINT configuration
switch1.c       ? switch1 configuration
delay.c         ? delay configuration

--------------------------------------------------------------
END OF README
-------------------------------------------------------------- 
