/*
 * adc.h
 *
 * Created: 22/10/2014 16:00:54 μμ
 *  Author: SPIROS
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <adc.h>

#define MY_ADC			ADCA
#define ADC_PIN_BAT		ADCCH_POS_PIN14
#define ADC_PIN_PVV		ADCCH_POS_PIN12
#define ADC_PIN_PVC		ADCCH_POS_PIN13

#define ADC_FREQ			F_CPU/128
#define ADC_GAIN			1
#define ADC_RESULT_MAX		2047.0
#define ADC_REF_VOLTAGE		1.0
#define ADC_DEFAULT_OSMPL	1.0

#define ADC_PVV_CTRL	IOPORT_CREATE_PIN(PORTF, PIN1_bp) //PIN used to Enable the measurement voltage divider for PV voltage
#define ADC_BAT_CTRL	IOPORT_CREATE_PIN(PORTF, PIN0_bp) //PIN used to Enable the measurement voltage divider for Battery voltage

#define ADC_BAT_RATIO	(402.0 + 100.0) / 100.0
#define ADC_PVV_RATIO	(576.0 + 20.0) / 20.0
#define ADC_PVC_RATIO	100.0 / 1.24
#define ADC_PVC_RSENSE	0.8

extern struct adc_config adc_conf;
extern struct adc_channel_config adcch_conf;

void adc_init(void);
double getADCVoltage(uint8_t adc_pin, double oversampling);
//uint16_t getLastADCValue(uint8_t adc_pin);
uint16_t getCalibrationData(void);
double getADCValue(uint8_t adc_pin, double oversampling);
double getBatteryADCValue(void);
double getPVVADCValue(void);
double getPVCADCValue(void);
double getBatteryADCVoltage(void);
double getPVVADCVoltage(void);
double getPVCADCVoltage(void);
double getBatteryVoltage(void);
double getPVVVoltage(void);
double getPVCVoltage(void);
double getPVCCurrent(void);
double getPVPower(void);

#endif /* ADC_H_ */