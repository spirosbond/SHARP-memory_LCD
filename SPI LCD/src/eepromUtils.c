/*
 * eepromUtils.c
 *
 * Created: 03/12/2014 13:56:10
 *  Author: bontom38
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "eepromUtils.h"

double EEMEM powerDay[288];
uint32_t EEMEM size;
//uint32_t la;
uint16_t i;

void eepromUtilsInit(void){
	//lastAddress = &powerDay[0];
}

void storePower(double power){
	uint32_t s = eeprom_read_dword(&size);
	s++;
	eeprom_update_dword(( uint32_t *) &powerDay[s-1], power);
	eeprom_update_dword(&size, s);
}

double* readPower(void){
	uint32_t s = eeprom_read_dword(&size);
	
	double* power = calloc(s, sizeof(double)); //remember to free it after calling this function
	eeprom_read_block (( void *) power , ( const void *) powerDay , s);
	return power;
}