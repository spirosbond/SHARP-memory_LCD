/*
 * adc.c
 *
 * Created: 22/10/2014 15:54:32 μμ
 *  Author: SPIROS
 */ 

#include <stdio.h>
#include <adc.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "measurements.h"
#include "display.h"

struct adc_config adc_conf;
struct adc_channel_config adcch_conf;

/*static void adc_handler(ADC_t *adc, uint8_t ch_mask, adc_result_t result)
{
	
	switch(multiplexer){
		case ADCCH_POS_PIN4:
			multiplexer = ADCCH_POS_PIN5;
			ADC_RESULT_4 = result;
			
			break;
		case ADCCH_POS_PIN5:
			multiplexer = ADCCH_POS_PIN4;
			ADC_RESULT_5 = result;
			
			break;
	}
	adcch_set_input(&adcch_conf,  multiplexer, ADCCH_NEG_PIN3, 1);
	adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	
	ADC_RESULT_4 = result;
	
	
}*/

void adc_init(void){
	
	adc_read_configuration(&MY_ADC, &adc_conf);
	adcch_read_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_ON, ADC_RES_12, ADC_REF_BANDGAP);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_MANUAL, 1, 0);
	adc_set_clock_rate(&adc_conf, ADC_FREQ);
	//adc_enable_internal_input(&adc_conf, ADC_INT_BANDGAP);
	//adc_set_callback(&MY_ADC, &adc_handler);
	//adcch_enable_interrupt(&adcch_conf);
	//adcch_set_input(&adcch_conf, multiplexer, ADCCH_NEG_NONE, 1);
	//adcch_enable_oversampling(&adcch_conf,ADC_SAMPNUM_1024X,16);
	//adcch_set_input(&adcch_conf, ADCCH_POS_PIN9, ADCCH_NEG_NONE, 1);
	//adcch_set_pin_scan(&adcch_conf, ADCCH_POS_PIN8, ADCCH_POS_PIN9);
	adc_write_configuration(&MY_ADC, &adc_conf);
	adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
}

double getADCVoltage(uint8_t adc_pin, float oversampling){
	/*switch(adc_pin){
		case ADCCH_POS_PIN4:
			return ADC_RESULT_4*ADC_REF_VOLTAGE/ADC_RESULT_MAX;
			break;
		case ADCCH_POS_PIN5:
			return ADC_RESULT_5*ADC_REF_VOLTAGE/ADC_RESULT_MAX;
			break;
		default:
			LED_On(LED1);
			return 0;
	}*/
	
	return getADCManualValue(adc_pin, oversampling)*ADC_REF_VOLTAGE/ADC_RESULT_MAX;
	
}

/*uint16_t getLastADCValue(uint8_t adc_pin){
	
	switch(adc_pin){
		case ADC_PIN1:
			return ADC_RESULT_4;
			break;
		case ADC_PIN2:
			return ADC_RESULT_5;
			break;
		default:
			LED_On(LED1);
			return 0;
	}
	
}*/

uint16_t getCalibrationData(void){
	return adc_get_calibration_data(ADC_CAL_ADCA);
}

double getADCManualValue(uint8_t adc_pin, float oversampling){
	uint16_t i;
	double result = 0;
	int16_t ADCValue = 0;
	
	adcch_read_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	adcch_set_input(&adcch_conf, adc_pin, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&MY_ADC, ADC_CH0, &adcch_conf);
	
	adc_start_conversion(&MY_ADC, ADC_CH0);
	adc_wait_for_interrupt_flag(&MY_ADC, ADC_CH0);
	
	for(i=0; i<oversampling; i++){
		adc_start_conversion(&MY_ADC, ADC_CH0);
		adc_wait_for_interrupt_flag(&MY_ADC, ADC_CH0);
		ADCValue = adc_get_result(&MY_ADC, ADC_CH0);	//Has to be done in two steps, to keep the minus (-) sign.
		result += ADCValue/oversampling;
	}

	return result;
}