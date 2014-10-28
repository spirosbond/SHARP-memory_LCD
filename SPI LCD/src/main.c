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
	
	/*while(linenum%(MLCD_YRES+1)!=0){
		
		MLCDWriteLine(data,linenum++);
		
	}*/
	
	while(1){
	/*	
		LED_On(LED0);
		MLCDWriteFrame(frame);
		delay_ms(1000);
		LED_Off(LED0);
		
		LED_On(LED1);
		showRandomFrame();
		delay_ms(1000);
		LED_Off(LED1);
		
		LED_On(LED1);
		LED_On(LED0);
		MLCDShowImecLogo();
		delay_ms(1000);
		LED_Off(LED0);
		LED_Off(LED1);
		
		MLCDUpdateByte(MLCD_BYTE_WHITE, 240, 50);
		MLCDUpdateByte(MLCD_BYTE_WHITE, 239, 50);
		MLCDUpdateByte(MLCD_BYTE_WHITE, 238, 50);
		MLCDRefreshFrame();
		delay_ms(1000);
		
		MLCDUpdatePixel(4,MLCD_PIXEL_BLACK,239,50);
		MLCDRefreshFrame();
		delay_ms(1000);
		
		MLCDUpdatePixel(4,MLCD_PIXEL_WHITE,239,50);
		MLCDRefreshFrame();
		delay_ms(1000);
*/
		/*LED_On(LED1);

		MLCDWriteString("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOP QRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",1,1,false);
		MLCDWriteString("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOP QRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",FONT_HEIGHT_ROWS*4,1,true);
		MLCDRefreshFrame();
		delay_ms(2000);
		LED_Off(LED1);
		
		MLCDClear();
		
		MLCDDrawSquare(5, 10, 20,false);
		MLCDDrawSquare(10, 100, 45,false);
		MLCDDrawSquare(10, 161, 30,false);
		MLCDDrawSquare(10, 220, 5,false);
		//MLCDDrawSquare(10, 220, 45,false);
		MLCDRefreshFrame();
		delay_ms(1000);*/
		/*
		MLCDDrawSnakeBait(120,25,false);
		MLCDRefreshFrame();
		delay_ms(1000);*/
		//MLCDDrawSquare(1, 234, 20,false);
		//MLCDRefreshFrame();
		/*if(gpio_pin_is_low(GPIO_PUSH_BUTTON_1) && gpio_pin_is_low(GPIO_PUSH_BUTTON_0)){
			MLCDClear();
			playSnake();
		}
		*/
		//MLCDClear();
		MLCDWriteString("ADC_RESULT_4: ",1,1,MLCD_BLACK);
		MLCDWriteString("ADC_RESULT_4: ",31,1,MLCD_BLACK);
		MLCDWriteString("ADC_RESULT_5: ",71,1,MLCD_BLACK);
		MLCDWriteString("ADC_RESULT_5: ",101,1,MLCD_BLACK);
		/*MLCDWriteUInt(0, 21, 24, MLCD_BLACK);
		MLCDWriteUInt(123456, 41, 24, MLCD_BLACK);
		MLCDWriteUFloat(123.1,61,24,MLCD_BLACK);
		MLCDWriteUFloat(32.129,81,24,MLCD_BLACK);
		MLCDWriteUFloat(0.0123,101,24,MLCD_BLACK);
		MLCDWriteUFloat(0,121,24,MLCD_BLACK);
		MLCDWriteUFloat(12345.789,141,24,MLCD_BLACK);*/
		//MLCDWriteDouble((getADCVoltage(ADC_PIN8)*1000)/7.43334, 1, 27, MLCD_BLACK);
		//MLCDWriteDouble(41.2*getADCVoltage(ADC_PIN9), 31, 27, MLCD_BLACK);
		MLCDWriteDouble(getADCManualValue(ADC_PIN1,128.0), 1, 27, MLCD_BLACK);
		//MLCDWriteDouble(getADCVoltage(ADC_PIN1,128.0)*1000/8.3737, 31, 27, MLCD_BLACK);
		MLCDWriteDouble(getADCVoltage(ADC_PIN1,128.0), 31, 27, MLCD_BLACK);
		MLCDWriteDouble(getADCManualValue(ADC_PIN2,128.0), 71, 27, MLCD_BLACK);
		//MLCDWriteDouble(43.138*getADCVoltage(ADC_PIN2,128.0), 101, 27, MLCD_BLACK);
		MLCDWriteDouble(getADCVoltage(ADC_PIN2,128.0), 101, 27, MLCD_BLACK);
		MLCDWriteString("Va",1,47,MLCD_BLACK);
		MLCDWriteString("V",31,47,MLCD_BLACK);
		MLCDWriteString("Va",71,47,MLCD_BLACK);
		MLCDWriteString("V",101,49,MLCD_BLACK);
		
		//MLCDWriteUFloat(getCalibrationData(),141,24,MLCD_BLACK);
		
		MLCDRefreshFrame();
		//delay_ms(10);
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


