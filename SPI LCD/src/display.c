/*
 * display.c
 *
 * Created: 16/10/2014 16:01:20
 *  Author: bontom38
 */ 

#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "display.h"
#include "utils.h"
#include "imec_logo.h"
#include "RegisterUtils.h"
#include "fonts.h"
#include "graphics.h"

uint8_t frame[MLCD_YRES][MLCD_BYTES_LINE];


struct spi_device spi_device_conf = {
	.id = SPI_SCS
};

struct pwm_config pwm_cfg;

void spi_init_pins(void)
{
	ioport_configure_port_pin(&PORTC, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	
	ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTC, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTC, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
}

void spi_init_module(void)
{
	spi_master_init(&SPI_MDL);
	spi_master_setup_device(&SPI_MDL, &spi_device_conf, SPI_MODE, SPI_BAUD, 0);
	spi_enable(&SPI_MDL);
}

void MLCDInit(void){
	spi_init_pins();
	
	//delay_ms(100);
	
	pwm_init(&pwm_cfg, PWM_TCE0, PWM_CH_A, MLCD_EXTCOMIN_FREQ);
	pwm_start(&pwm_cfg, MLCD_EXTCOMIN_DC);
	
	//delay_ms(100);
	
	spi_init_module();
}

void MLCDSelect(void){
	spi_select_device(&SPI_MDL, &spi_device_conf);
}

void MLCDDeselect(void){
	spi_deselect_device(&SPI_MDL, &spi_device_conf);
}

void MLCDClear(void){
	uint8_t CM[2] = {MLCD_CM,MLCD_TR};
	
	gpio_set_pin_high(SPI_SCS);
	spi_write_packet(&SPI_MDL,CM, 2);
	while(!spi_is_tx_ok(&SPI_MDL));
	gpio_set_pin_low(SPI_SCS);
	//frame = (uint8_t**) malloc(MLCD_YRES*sizeof(uint8_t*));
	//for(i=0;i<MLCD_YRES;i++){
	//	frame[i] = (uint8_t*) malloc(MLCD_BYTES_LINE*sizeof(uint8_t));
		//memset(&frame[i][0], 255, sizeof(uint8_t) * MLCD_BYTES_LINE);
	//}
	memset(frame, 255, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
	//memset(&frame[MLCD_YRES/2][MLCD_BYTES_LINE], 255, sizeof(frame[0][0]) * (MLCD_FRAME_SIZE-MLCD_BYTES_LINE*MLCD_YRES/2));
}

void MLCDSet(void){
	memset(frame, 0, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
	MLCDWriteFrame(frame);
}

void MLCDWriteLine(uint8_t data[MLCD_BYTES_LINE], uint8_t lineNum){
	gpio_set_pin_high(SPI_SCS);

	spi_write_single(&SPI_MDL, MLCD_WR);
	while(!spi_is_tx_ok(&SPI_MDL));
	MLCDAddLine(data, lineNum);
	spi_write_single(&SPI_MDL, MLCD_TR);
	while(!spi_is_tx_ok(&SPI_MDL));
	
	gpio_set_pin_low(SPI_SCS);
}

void MLCDAddLine(uint8_t data[MLCD_BYTES_LINE], uint8_t lineNum){
	
	spi_write_single(&SPI_MDL, reverseByte(lineNum));
	while(!spi_is_tx_ok(&SPI_MDL));
	spi_write_packet(&SPI_MDL, data, MLCD_BYTES_LINE);
	memcpy(&frame[lineNum-1][0],data,sizeof(data[0])*MLCD_BYTES_LINE);
	while(!spi_is_tx_ok(&SPI_MDL));
	spi_write_single(&SPI_MDL, MLCD_TR);
	while(!spi_is_tx_ok(&SPI_MDL));
	
}

void MLCDWriteFrame(uint8_t data[MLCD_YRES][MLCD_BYTES_LINE]){
	gpio_set_pin_high(SPI_SCS);

	spi_write_single(&SPI_MDL, MLCD_WR);
	while(!spi_is_tx_ok(&SPI_MDL));
	
	uint8_t lineNum=1;
	while(lineNum%(MLCD_YRES+1)!=0){
		MLCDAddLine(data[lineNum-1], lineNum);
		lineNum++;
	}
	
	spi_write_single(&SPI_MDL, MLCD_TR);
	while(!spi_is_tx_ok(&SPI_MDL));
	
	gpio_set_pin_low(SPI_SCS);
}

void MLCDShowImecLogo(void){
	uint16_t i;
	uint8_t logo[MLCD_BYTES_LINE];
	for(i=0;i<MLCD_YRES;i++){
		PGM_READ_BLOCK(logo, &imecLogo[i*MLCD_BYTES_LINE], sizeof(uint8_t)*MLCD_BYTES_LINE);
		MLCDWriteLine(logo,i+1);
	}

}

void MLCDRefreshFrame(void){
	MLCDWriteFrame(frame);
}

void MLCDUpdateByte(uint8_t data, uint8_t row, uint8_t column){
	frame[row-1][column-1] = data;
}

void MLCDUpdatePixel(uint8_t pixelPos, bool v, uint8_t row, uint8_t column){
	if(v)
		SETBIT(frame[row-1][column-1],pixelPos);
	else
		CLEARBIT(frame[row-1][column-1],pixelPos);
}

void MLCDWriteCharacter(const uint8_t *character, uint8_t row, uint8_t column, bool white){
	uint8_t tempColumn=column;
	uint16_t i;
	
	for(i=0;i<FONT_SIZE_BITS;i++){
		if(white)
			MLCDUpdateByte(~character[i],row,tempColumn);
		else
			MLCDUpdateByte(character[i],row,tempColumn);
		tempColumn++;
		if(tempColumn%(column+FONT_WIDTH_BYTES) == 0){
			tempColumn=column;
			row++;
		}
	}
}
void MLCDWriteString(char *str, uint8_t row, uint8_t column, bool white){
	uint8_t tempColumn = column;
	uint16_t i=0;
	while(str[i]!='\0'){
		MLCDWriteCharacter(getCharacterImage(str[i]), row, tempColumn, white);
		i++;
		tempColumn+=FONT_WIDTH_BYTES;
		if(tempColumn>MLCD_BYTES_LINE-FONT_WIDTH_BYTES+1){
			tempColumn = 1;
			row+=FONT_HEIGHT_ROWS;
		}
		
	}
}

void MLCDWriteUInt(uint64_t num, uint8_t row, uint8_t column, bool white){
	char * uIntAsString = getUIntAsString(num);
	MLCDWriteString(uIntAsString, row, column, white);
	free(uIntAsString);
}

void MLCDWriteDouble(double num, uint8_t row, uint8_t column, bool white){
	char * doubleAsString = getDoubleAsString(num);
	MLCDWriteString(doubleAsString, row, column, white);
	free(doubleAsString);
}

void MLCDDrawSquare(uint8_t sizeInBytes, uint8_t row, uint8_t column, bool white){
	uint8_t tempRow = row, tempColumn = column;
	uint16_t i,j;
	for(i=0;i<sizeInBytes;i++){
		
		for(j=0;j<8*sizeInBytes;j++){
			if(white){
				MLCDUpdateByte(MLCD_BYTE_WHITE, tempRow, tempColumn);
			}
			else{
				MLCDUpdateByte(MLCD_BYTE_BLACK, tempRow, tempColumn);
			}
		tempRow++;
		if (tempRow%(MLCD_YRES+1) == 0)	tempRow = 1;
		}
		
		tempColumn++;
		if (tempColumn%(MLCD_BYTES_LINE+1) == 0)	tempColumn = 1;
		tempRow = row;
	}
}

void MLCDDrawSnakeBait(uint8_t row, uint8_t column, bool white){
	uint16_t i;
	for(i=0;i<8;i++){
		if(white)
			MLCDUpdateByte(~snake_bait[i], row, column);
		else
			MLCDUpdateByte(snake_bait[i], row, column);
			
		row++;
	}
}