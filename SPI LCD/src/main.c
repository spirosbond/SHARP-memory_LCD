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


#define F_CPU 32000000

#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
#include "led.h"
#include "display.h"
#include "fonts.h"
#include "snake.h"
#include "measurements.h"

void showRandomFrame(void);

int16_t i,j;

int main (void)
{
	
	board_init();
	sysclk_init();
	cpu_irq_enable();
	
	MLCDInit();
	MLCDSelect();
	MLCDClear();
	
	adc_init();
	pmic_init();
	adc_enable(&MY_ADC);
	
	//playSnake();
	/*while(linenum%(MLCD_YRES+1)!=0){
		
		MLCDWriteLine(data,linenum++);
		
	}*/
	
	while(1){
		
		MLCDClear();

		MLCDDrawColumn(220,2,2,rand()%201,false);
		MLCDDrawColumn(220,5,3,rand()%201,false);
		MLCDDrawColumn(220,9,4,rand()%201,false);
		
		MLCDDrawColumn(220,14,5,rand()%201,false);
		MLCDDrawColumn(220,20,6,rand()%201,false);
		MLCDDrawColumn(220,27,7,rand()%201,false);
		
		MLCDDrawColumn(220,35,8,rand()%201,false);
		
	/*	//MLCDClear();
		MLCDWriteString("ADC_RESULT_1: ",1,1,MLCD_BLACK);
		MLCDWriteString("ADC_V_1: ",31,1,MLCD_BLACK);
		MLCDWriteString("ADC_COMP_1: ",61,1,MLCD_BLACK);
		MLCDWriteString("ADC_RESULT_2: ",111,1,MLCD_BLACK);
		MLCDWriteString("ADC_V_2: ",141,1,MLCD_BLACK);
		MLCDWriteString("ADC_COMP_2: ",171,1,MLCD_BLACK);
	
		//MLCDWriteDouble((getADCVoltage(ADC_PIN8)*1000)/7.43334, 1, 27, MLCD_BLACK);
		//MLCDWriteDouble(41.2*getADCVoltage(ADC_PIN9), 31, 27, MLCD_BLACK);
		double v1 = getADCVoltage(ADC_PIN1,1024.0);
		MLCDWriteDouble(getADCManualValue(ADC_PIN1,128.0), 1, 27, MLCD_BLACK);
		MLCDWriteDouble(v1, 31, 27, MLCD_BLACK);
		MLCDWriteDouble(v1*1000/18.666667, 61, 27, MLCD_BLACK);
		
		MLCDWriteLine(0xff,95);
		
		double v2 = getADCVoltage(ADC_PIN2,1024.0);
		MLCDWriteDouble(getADCManualValue(ADC_PIN2,128.0), 111, 27, MLCD_BLACK);
		MLCDWriteDouble(v2, 141, 27, MLCD_BLACK);
		MLCDWriteDouble(31*v2, 171, 27, MLCD_BLACK);
		
		MLCDWriteString("Va",1,47,MLCD_BLACK);
		MLCDWriteString("V",31,47,MLCD_BLACK);
		MLCDWriteString("Va",111,47,MLCD_BLACK);
		MLCDWriteString("V",141,47,MLCD_BLACK);
		
		//MLCDWriteUInt(getADCVoltage(ADC_PIN3,128.0)*20, 201, 40, MLCD_BLACK);
		//MLCDWriteString("%",201,47,MLCD_BLACK);
		
		//MLCDWriteUFloat(getCalibrationData(),141,24,MLCD_BLACK);*/
		
		MLCDRefreshFrame();
		delay_ms(500);
		
		if(gpio_pin_is_low(GPIO_PUSH_BUTTON_1) && gpio_pin_is_low(GPIO_PUSH_BUTTON_0)){
			playSnake();
		}
	}
	
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


