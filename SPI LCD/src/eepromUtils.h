/*
 * eepromUtils.h
 *
 * Created: 03/12/2014 13:56:26
 *  Author: bontom38
 */ 


#ifndef EEPROMUTILS_H_
#define EEPROMUTILS_H_

extern double EEMEM powerDay[288];
extern uint32_t EEMEM lastAddress;

void eepromUtilsInit(void);
void storePower(double power);
double* readPower(void);

#endif /* EEPROMUTILS_H_ */