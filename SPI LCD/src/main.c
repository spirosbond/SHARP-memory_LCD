/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */


#define F_CPU 2000000/2

#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
#include <math.h>
#include "led.h"
#include "display.h"
#include "fonts.h"
#include "fontsLarge.h"
#include "snake.h"
#include "measurements.h"

#define PB0	IOPORT_CREATE_PIN(PORTF, 6)
#define PB1	IOPORT_CREATE_PIN(PORTF, 7)

#define MAX_VOLTAGE	30
#define MAX_CURRENT	6
#define MAX_POWER	50
#define MAX_BAT		5

void showRandomFrame(void);
void BarScreen(void);
void showBattery(double b);
void showArrows(void);
void PowerScreen(void);
void PORT_ConfigureInterrupt0(PORT_t * port, PORT_INT0LVL_t intLevel, uint8_t pinMask);
void PORT_ConfigureInterrupt1(PORT_t * port, PORT_INT1LVL_t intLevel, uint8_t pinMask);

int16_t i,j;
double voltage, current, power, battery, oldBattery = 0, maxVoltage=0, maxCurrent=0, maxPower=0, powerHist[50];

uint8_t powerTail = 0;
uint8_t screen = 0;


int main (void)
{
	board_init();
	ioport_set_pin_dir(PB0, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB0, IOPORT_MODE_PULLUP);
	ioport_set_pin_dir(PB1, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB1, IOPORT_MODE_PULLUP);
	sysclk_init();
	
	ioport_set_pin_sense_mode(ioport_pin_to_mask(PORTF_PIN2CTRL), IOPORT_SENSE_FALLING);
	ioport_set_pin_sense_mode(ioport_pin_to_mask(PORTF_PIN3CTRL), IOPORT_SENSE_FALLING);
	ioport_set_pin_sense_mode(ioport_pin_to_mask(PORTF_PIN4CTRL), IOPORT_SENSE_FALLING);
	ioport_set_pin_sense_mode(ioport_pin_to_mask(PORTF_PIN5CTRL), IOPORT_SENSE_FALLING);
	PORT_ConfigureInterrupt0( &PORTF, PORT_INT0LVL_MED_gc, PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm);
	pmic_init();
	pmic_set_scheduling(PMIC_SCH_ROUND_ROBIN);
	pmic_enable_level(PMIC_LVL_MEDIUM);
	
	cpu_irq_enable();
	
	MLCDInit();
	MLCDTurnOn();
	MLCDClearAll();
	
	adc_init();
	
	MLCDShowImecLogo();
	//delay_ms(2000);
	MLCDClearFrame();
	
	while(1){
		//LED_Toggle(LED0);
		
		//MLCDWriteDouble(getBatteryADCVoltage(),	FONT_SIZE_NORMAL,	18+FONT_SIZE_NORMAL,	40,	MLCD_BLACK);
		
		//LED_On(LED0);
		
		voltage = getPVVVoltage();
		current = getPVCCurrent();
		power = voltage*current;
		battery = getBatteryVoltage();
		
		if(voltage > maxVoltage)	maxVoltage = voltage;
		if(current > maxCurrent)	maxCurrent = current;
		if(power > maxPower)		maxPower = power;
		
		for(i=powerTail; i>0; i--){
			powerHist[i] = powerHist[i-1];
		}
		
		powerHist[0] = power;
		
		if(screen%2 == 0)		PowerScreen();
		else if (screen%2 == 1)	BarScreen();
		//else if (screen%4 == 2)	PowerScreen();
		//else if (screen%4 == 3)	BarScreen();
		
		if(powerTail!=49)	powerTail++;
		
		MLCDWriteString("TFPV Group",FONT_SIZE_LARGE,1,1,MLCD_BLACK);
		showArrows();
		showBattery(battery);
		MLCDRefreshFrame();
		MLCDClearFrame();
		//LED_Off(LED1);
		if(gpio_pin_is_low(PB1) && gpio_pin_is_low(PB0)){
			playSnake();
		}
		//sleep_set_mode(SLEEP_SMODE_PDOWN_gc);
		//sleep_enable();
		//sleep_enter();
		//sleep_disable();
	}
	
}

ISR(PORTF_INT0_vect)
{
	//sleep_disable();
	
	if(gpio_pin_is_low(MLCD_PB0)){
		//LED_Off(LED1);
		LED_On(LED0);
		screen++;		
	} else if(gpio_pin_is_low(MLCD_PB1)){
		//showRandomFrame();
		maxVoltage = 0;
		maxCurrent = 0;
		maxPower = 0;
		//MLCDRefreshFrame();
		//MLCDClearFrame();
	} else if(gpio_pin_is_low(MLCD_PB2)){
		//LED_Off(LED0);
		LED_On(LED1);
		screen--;
	} else if(gpio_pin_is_low(MLCD_PB3)){
		MLCDShowImecLogo();
		delay_ms(1000);
		MLCDClearFrame();
	} else{
		LED_Off(LED1);
		LED_Off(LED0);	
	}
}

void PowerScreen(void){
	//LED_On(LED0);
	//double power = getPVPower();
	//LED_Off(LED0);
	
	
	for(i=0; i<=powerTail; i++){
		MLCDDrawColumn(MLCD_YRES,	MLCD_BYTES_LINE - i,	1,	(MLCD_YRES/2)*powerHist[i]/MAX_POWER,	MLCD_BLACK);
	}
	
	
	MLCDWriteDouble(powerHist[0],	FONT_SIZE_LARGE,	MLCD_YRES/3-FONT_SIZE_LARGE/2,	MLCD_BYTES_LINE/2-12,	MLCD_BLACK);
	MLCDWriteString("mW",			FONT_SIZE_LARGE,	MLCD_YRES/3-FONT_SIZE_LARGE/2,	MLCD_BYTES_LINE/2+6,	MLCD_BLACK);
	MLCDWriteDouble(maxPower,		FONT_SIZE_NORMAL,	MLCD_YRES-FONT_SIZE_NORMAL+1,		1,		MLCD_WHITE);
}

void showBattery(double b){
	uint8_t battery = 100*b/MAX_BAT;
	uint8_t numOfDigits = log10(battery) + 1;
	
	MLCDWriteInt(battery,	FONT_SIZE_NORMAL,	18,	49 - 2*numOfDigits,	MLCD_BLACK);
	MLCDWriteString("%",	FONT_SIZE_NORMAL,	18,	49,					MLCD_BLACK);
	MLCDDrawBattery(1, 47, battery, false);

	
	if(b > oldBattery + 0.003){
		MLCDWriteString("+", FONT_SIZE_NORMAL, 1, 46, MLCD_BLACK);
		oldBattery = b;
	}
	else if(b < oldBattery - 0.003){
		MLCDWriteString("-", FONT_SIZE_NORMAL, 1, 46, MLCD_BLACK);
		oldBattery = b;
	}
	
}

void BarScreen(void){
	//LED_On(LED0);	
	
	//LED_Off(LED0);
	
	MLCDDrawColumn(200,	4,	10,	156 * voltage/MAX_VOLTAGE,	false);
	MLCDDrawColumn(200,	20,	10,	156 * current/MAX_CURRENT,	false);
	MLCDDrawColumn(200,	36,	10,	156 * power/MAX_POWER,	false);
	
	MLCDWriteString("Voltage",	FONT_SIZE_NORMAL,	207,	4,	MLCD_BLACK);
	MLCDWriteString("Current",	FONT_SIZE_NORMAL,	207,	20,	MLCD_BLACK);
	MLCDWriteString("Power",	FONT_SIZE_NORMAL,	207,	37,	MLCD_BLACK);
	
	MLCDWriteDouble(voltage,	FONT_SIZE_NORMAL,	200-FONT_SIZE_NORMAL,	4 + 2 - log10(voltage) + 1,	MLCD_WHITE);
	MLCDWriteString("V",		FONT_SIZE_NORMAL,	224,	13,	MLCD_BLACK);
	
	MLCDWriteDouble(current,	FONT_SIZE_NORMAL,	200-FONT_SIZE_NORMAL,	20 + 2 - log10(current) + 1,	MLCD_WHITE);
	MLCDWriteString("mA",	FONT_SIZE_NORMAL,		224,	28,	MLCD_BLACK);

	MLCDWriteDouble(power,	FONT_SIZE_NORMAL,		200-FONT_SIZE_NORMAL,	36 + 2 - log10(power) + 1,	MLCD_WHITE);
	MLCDWriteString("mW",	FONT_SIZE_NORMAL,	224,	45,	MLCD_BLACK);
	
	MLCDWriteDouble(maxVoltage,	FONT_SIZE_NORMAL,	224,	4,	MLCD_BLACK);
	MLCDWriteDouble(maxCurrent,	FONT_SIZE_NORMAL,	224,	19,	MLCD_BLACK);
	MLCDWriteDouble(maxPower,	FONT_SIZE_NORMAL,	224,	34,	MLCD_BLACK);
	
}

void showRandomFrame(void){

	uint8_t data2[MLCD_BYTES_LINE];
	//for(i=0;i<MLCD_YRES;i++){
		for(j=0;j<MLCD_BYTES_LINE;j++){
			data2[j] = rand()%256;
		}
		
	//}
	for(i=0;i<MLCD_YRES;i++){
		MLCDWriteLine(data2,i+1);
	}
}

void showArrows(void){
	MLCDDrawRLArrow(FONT_SIZE_LARGE+1,	MLCD_BYTES_LINE-1,	MLCD_ARROW_RIGHT,	MLCD_BLACK);
	MLCDDrawRLArrow(FONT_SIZE_LARGE+1,	1,					MLCD_ARROW_LEFT,	MLCD_BLACK);
}


void PORT_ConfigureInterrupt0(PORT_t * port, PORT_INT0LVL_t intLevel, uint8_t pinMask){
	port->INTCTRL = ( port->INTCTRL & ~PORT_INT0LVL_gm ) | intLevel;
	port->INT0MASK = pinMask;
}
void PORT_ConfigureInterrupt1(PORT_t * port, PORT_INT1LVL_t intLevel, uint8_t pinMask){
	port->INTCTRL = ( port->INTCTRL & ~PORT_INT1LVL_gm ) | intLevel;
	port->INT1MASK = pinMask;
}
