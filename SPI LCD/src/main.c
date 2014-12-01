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


#define F_CPU 2000000/4

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

void showRandomFrame(void);
void BarScreen(void);
void showBattery(void);
void showArrows(void);
void PowerScreen(void);
void PORT_ConfigureInterrupt0(PORT_t * port, PORT_INT0LVL_t intLevel, uint8_t pinMask);
void PORT_ConfigureInterrupt1(PORT_t * port, PORT_INT1LVL_t intLevel, uint8_t pinMask);

int16_t i,j;
double powerHist[50];
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
	MLCDClearAll();
	MLCDTurnOn();
	
	adc_init();
	//adc_enable(&MY_ADC);
	
	MLCDShowImecLogo();
	//delay_ms(2000);
	MLCDClearFrame();
	
	while(1){
		
		//MLCDWriteString("TFPV Group",FONT_SIZE_LARGE,1,1,MLCD_BLACK);
		
		//showBattery();
		//showArrows();
		/*if(screen%4 == 0)		PowerScreen();
		else if (screen%4 == 1)	BarScreen();
		else if (screen%4 == 2)	PowerScreen();
		else if (screen%4 == 3)	BarScreen();
		*/
		//MLCDRefreshFrame();
		//MLCDClearFrame();
		
		if(gpio_pin_is_low(PB1) && gpio_pin_is_low(PB0)){
			playSnake();
		}
		sleep_set_mode(SLEEP_SMODE_PDOWN_gc);
		sleep_enable();
		sleep_enter();
		sleep_disable();
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
		MLCDShowImecLogo();
		delay_ms(1000);
		MLCDClearFrame();
	} else if(gpio_pin_is_low(MLCD_PB2)){
		//LED_Off(LED0);
		LED_On(LED1);
		screen--;
	} else if(gpio_pin_is_low(MLCD_PB3)){
		
	} else{
		LED_Off(LED1);
		LED_Off(LED0);	
	}
}

void PowerScreen(void){
	
	double power = getPVPower();
	
	for(i=powerTail; i>0; i--){
		powerHist[i] = powerHist[i-1];
	}
	
	powerHist[0] = power;
	
	for(i=0; i<=powerTail; i++){
		MLCDDrawColumn(MLCD_YRES,	MLCD_BYTES_LINE - i,	1,	(MLCD_YRES/2)*powerHist[i]/215,	MLCD_BLACK);
	}
	
	if(powerTail!=49)	powerTail++;
	
	MLCDWriteDouble(powerHist[0],	FONT_SIZE_LARGE,	MLCD_YRES/3-FONT_SIZE_LARGE/2,	MLCD_BYTES_LINE/2-12,	MLCD_BLACK);
	MLCDWriteString("mW",			FONT_SIZE_LARGE,	MLCD_YRES/3-FONT_SIZE_LARGE/2,	MLCD_BYTES_LINE/2+6,	MLCD_BLACK);
}

void showBattery(void){
	uint8_t battery = 100*getBatteryVoltage()/5.00;
	uint8_t numOfDigits = log10(battery) + 1;
	
	MLCDWriteInt(battery,	FONT_SIZE_NORMAL,	18,	49 - 2*numOfDigits,	MLCD_BLACK);
	MLCDWriteString("%",	FONT_SIZE_NORMAL,	18,	49,					MLCD_BLACK);
	MLCDDrawBattery(1, 47, battery, false);
}

void BarScreen(void){
		
	double voltage = getPVVVoltage();
	double current = getPVCCurrent();
	double power = voltage*current;

	MLCDWriteString("Voltage",	FONT_SIZE_NORMAL,	207,	4,	MLCD_BLACK);
	MLCDWriteString("Current",	FONT_SIZE_NORMAL,	207,	20,	MLCD_BLACK);
	MLCDWriteString("Power",	FONT_SIZE_NORMAL,	207,	38,	MLCD_BLACK);
	
	MLCDWriteDouble(voltage,	FONT_SIZE_NORMAL,	224,	5,	MLCD_BLACK);
	MLCDWriteString("V",		FONT_SIZE_NORMAL,	224,	13,	MLCD_BLACK);
	
	MLCDWriteDouble(current,	FONT_SIZE_NORMAL,	224,	19,	MLCD_BLACK);
	MLCDWriteString("mA",	FONT_SIZE_NORMAL,		224,	28,	MLCD_BLACK);

	MLCDWriteDouble(power,	FONT_SIZE_NORMAL,	224,	34,	MLCD_BLACK);
	MLCDWriteString("mW",	FONT_SIZE_NORMAL,	224,	45,	MLCD_BLACK);
	
	MLCDDrawColumn(200,	6,	8,	166 * voltage/30,		false);
	MLCDDrawColumn(200,	21,	8,	166 * current/100,	false);
	MLCDDrawColumn(200,	38,	8,	166 * power/3000,		false);
	
}

void showRandomFrame(void){

	uint8_t data2[MLCD_YRES][MLCD_BYTES_LINE];
	for(i=0;i<MLCD_YRES;i++){
		for(j=0;j<MLCD_BYTES_LINE;j++){
			data2[i][j] = rand()%256;
		}
	}
	MLCDWriteFrame(data2);
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
