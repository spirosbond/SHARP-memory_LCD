/*
 * adc.h
 *
 * Created: 22/10/2014 16:00:54 μμ
 *  Author: SPIROS
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <adc.h>

#define MY_ADC	ADCA
#define ADC_PIN1	ADCCH_POS_PIN7
#define ADC_PIN2	ADCCH_POS_PIN5
#define ADC_FREQ	62000UL
#define ADC_RESULT_MAX	2047.0
#define ADC_REF_VOLTAGE 1.0

extern struct adc_config adc_conf;
extern struct adc_channel_config adcch_conf;

void adc_init(void);
double getADCVoltage(uint8_t adc_pin, float oversampling);
//uint16_t getLastADCValue(uint8_t adc_pin);
uint16_t getCalibrationData(void);
double getADCManualValue(uint8_t adc_pin, float oversampling);

#endif /* ADC_H_ */