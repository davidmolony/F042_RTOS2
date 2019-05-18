# F042_RTOS2
Repo using RTOS and timer1 complimentary PWM + timer17 interrupts to commute a BLDC motor on STM32F042 Nucleo.

This program is made using STM32CUBEMX 5.1.0 and compiled using system workbench for STM32 with GCC-ARM compiler. 

The circuit it is run on uses a breadboarded 3 phase H-bridge with IRFB7545PBF MOSFET driven by NCP81080DR2G gate drivers.
Current limiting and control is presently taken care of by a bench power supply. Overvoltage from accidental regeneration is clamped using a Littlefuse varistor with a 45V threshold.

Commutation is made by software update of registers on timer1, from interrupt on Timer17 overflow. ARR is updated through RTOS.

If you think it's a good idea to use this personally, commercially or otherwise, I wish you all the luck in the world and take no responsibility for the consequences.
