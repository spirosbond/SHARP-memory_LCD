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
#include "fontsLarge.h"
#include "fontUtils.h"
#include "graphics.h"

uint8_t frame[MLCD_YRES][MLCD_BYTES_LINE];


struct spi_device spi_device_conf = {
	.id = SPI_SCS
};

struct pwm_config pwm_cfg;

void spi_init_pins(void)
{
	ioport_configure_port_pin(&PORTC, PIN0_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTC, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTF, PIN2_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTF, PIN3_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTF, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTF, PIN5_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	
	ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
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
	
	pwm_init(&pwm_cfg, PWM_TCC0, PWM_CH_C, MLCD_EXTCOMIN_FREQ);
	pwm_start(&pwm_cfg, MLCD_EXTCOMIN_DC);
	
	//delay_ms(100);
	
	spi_init_module();
}

void MLCDTurnOn(void){
	gpio_set_pin_high(SPI_DISP);
}

void MLCDTurnOff(void){
	gpio_set_pin_low(SPI_DISP);
}

void MLCDSelect(void){
	spi_deselect_device(&SPI_MDL, &spi_device_conf);	//opposite because MLCD is enabled when pin is HIGH
}

void MLCDDeselect(void){
	spi_select_device(&SPI_MDL, &spi_device_conf);	//opposite because MLCD is disabled when pin is LOW
}

void MLCDClearAll(void){
	uint8_t CM[2] = {MLCD_CM,MLCD_TR};
	
	MLCDSelect();
	//gpio_set_pin_high(SPI_SCS);
	spi_write_packet(&SPI_MDL,CM, 2);
	while(!spi_is_tx_ok(&SPI_MDL));
	//gpio_set_pin_low(SPI_SCS);
	MLCDDeselect();
	//frame = (uint8_t**) malloc(MLCD_YRES*sizeof(uint8_t*));
	//for(i=0;i<MLCD_YRES;i++){
	//	frame[i] = (uint8_t*) malloc(MLCD_BYTES_LINE*sizeof(uint8_t));
		//memset(&frame[i][0], 255, sizeof(uint8_t) * MLCD_BYTES_LINE);
	//}
	memset(frame, 255, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
	//memset(&frame[MLCD_YRES/2][MLCD_BYTES_LINE], 255, sizeof(frame[0][0]) * (MLCD_FRAME_SIZE-MLCD_BYTES_LINE*MLCD_YRES/2));
}

void MLCDClearScreen(void){
	uint8_t CM[2] = {MLCD_CM,MLCD_TR};
	
	MLCDSelect();
	//gpio_set_pin_high(SPI_SCS);
	spi_write_packet(&SPI_MDL,CM, 2);
	while(!spi_is_tx_ok(&SPI_MDL));
	//gpio_set_pin_low(SPI_SCS);
	MLCDDeselect();
	//frame = (uint8_t**) malloc(MLCD_YRES*sizeof(uint8_t*));
	//for(i=0;i<MLCD_YRES;i++){
	//	frame[i] = (uint8_t*) malloc(MLCD_BYTES_LINE*sizeof(uint8_t));
	//memset(&frame[i][0], 255, sizeof(uint8_t) * MLCD_BYTES_LINE);
	//}
	//memset(frame, 255, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
	//memset(&frame[MLCD_YRES/2][MLCD_BYTES_LINE], 255, sizeof(frame[0][0]) * (MLCD_FRAME_SIZE-MLCD_BYTES_LINE*MLCD_YRES/2));
}

void MLCDClearFrame(void){
	memset(frame, 255, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
}

void MLCDSet(void){
	memset(frame, 0, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
	MLCDWriteFrame(frame);
}

void MLCDSetFrame(void){
	memset(frame, 0, sizeof(frame[0][0]) * MLCD_FRAME_SIZE);
}

void MLCDWriteLine(uint8_t data[MLCD_BYTES_LINE], uint8_t lineNum){
	//gpio_set_pin_high(SPI_SCS);
	MLCDSelect();
	spi_write_single(&SPI_MDL, MLCD_WR);
	while(!spi_is_tx_ok(&SPI_MDL));
	MLCDAddLine(data, lineNum);
	spi_write_single(&SPI_MDL, MLCD_TR);
	while(!spi_is_tx_ok(&SPI_MDL));
	MLCDDeselect();
	//gpio_set_pin_low(SPI_SCS);
}

void MLCDAddLine(uint8_t data[MLCD_BYTES_LINE], uint8_t lineNum){
	
	spi_write_single(&SPI_MDL, reverseByte(lineNum));
	while(!spi_is_tx_ok(&SPI_MDL));
	spi_write_packet(&SPI_MDL, data, MLCD_BYTES_LINE);
	memcpy(&frame[lineNum-1][0],data,sizeof(data[0])*MLCD_BYTES_LINE);	//TODO: Add if clause to perform this only if needed. Pass a boolean variable from the caller if data is part of the frame.
	while(!spi_is_tx_ok(&SPI_MDL));
	spi_write_single(&SPI_MDL, MLCD_TR);
	while(!spi_is_tx_ok(&SPI_MDL));
	
}

void MLCDWriteFrame(uint8_t data[MLCD_YRES][MLCD_BYTES_LINE]){
	//gpio_set_pin_high(SPI_SCS);
	MLCDSelect();
	spi_write_single(&SPI_MDL, MLCD_WR);
	while(!spi_is_tx_ok(&SPI_MDL));
	
	uint8_t lineNum=1;
	while(lineNum%(MLCD_YRES+1)!=0){
		MLCDAddLine(data[lineNum-1], lineNum);
		lineNum++;
	}
	
	spi_write_single(&SPI_MDL, MLCD_TR);
	while(!spi_is_tx_ok(&SPI_MDL));
	MLCDDeselect();
	//gpio_set_pin_low(SPI_SCS);
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

/*void MLCDWriteCharacter(const uint8_t *character, uint8_t row, uint8_t column, bool white){
	uint8_t tempColumn=column;
	uint16_t i;
	
	for(i=0;i<FONT_SIZE_BYTES;i++){
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
}*/

void MLCDWriteCharacter(const uint8_t *character, uint8_t fontSize, uint8_t nColumnsInBytes, uint8_t row, uint8_t column, bool white){
	uint8_t tempColumn=column;
	uint16_t i;
	
	for(i=0; i<(fontSize*nColumnsInBytes); i++){
		if(white)
			MLCDUpdateByte(~character[i],row,tempColumn);
		else
			MLCDUpdateByte(character[i],row,tempColumn);
		tempColumn++;
		if(tempColumn%(column + nColumnsInBytes) == 0){
			tempColumn=column;
			row++;
		}
	}
}
void MLCDWriteString(char *str, uint8_t fontSize, uint8_t row, uint8_t column, bool white){
	uint8_t tempColumn = column;
	uint16_t i=0;
	while(str[i]!='\0'){
		uint8_t nColumnsInBytes = 0;
		if(fontSize == FONT_SIZE_NORMAL){
			const uint8_t * ch = getCharacterImage(str[i], &nColumnsInBytes);
			MLCDWriteCharacter(ch,FONT_SIZE_NORMAL, nColumnsInBytes, row, tempColumn, white);
		}else if(fontSize == FONT_SIZE_LARGE){
			const uint8_t * ch = getLargeCharacterImage(str[i], &nColumnsInBytes);
			MLCDWriteCharacter(ch,FONT_SIZE_LARGE, nColumnsInBytes, row, tempColumn, white);
		}
		i++;
		tempColumn+=nColumnsInBytes;
		if(tempColumn>MLCD_BYTES_LINE-nColumnsInBytes+1){
			tempColumn = 1;
			row+=fontSize;
		}
		
	}
}

void MLCDWriteInt(uint64_t num, uint8_t fontSize, uint8_t row, uint8_t column, bool white){
	char * uIntAsString = getIntAsString(num);
	MLCDWriteString(uIntAsString,fontSize, row, column, white);
	free(uIntAsString);
}

void MLCDWriteDouble(double num, uint8_t fontSize, uint8_t row, uint8_t column, bool white){
	char * doubleAsString = getDoubleAsString(num);
	MLCDWriteString(doubleAsString,fontSize, row, column, white);
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

void MLCDDrawColumn(uint8_t row, uint8_t column, uint8_t sizeInBytes, uint8_t height, bool white){
	/*uint16_t i;
	int16_t tempRow = row - 8*sizeInBytes + 1;
	for(i=0; i<height; i++, tempRow--){
		if(tempRow<=0){
			tempRow = MLCD_YRES + tempRow;
		}
		MLCDDrawSquare(sizeInBytes,tempRow, column, white);
		
	}*/
	
	uint8_t tempRow = row, tempColumn = column;
	uint16_t i,j;
	for(i=0;i<sizeInBytes;i++){
		
		for(j=0;j<height;j++){
			if(white){
				MLCDUpdateByte(MLCD_BYTE_WHITE, tempRow, tempColumn);
			}
			else{
				MLCDUpdateByte(MLCD_BYTE_BLACK, tempRow, tempColumn);
			}
			tempRow--;
			if (tempRow == 0)	tempRow = MLCD_YRES;
		}
		
		tempColumn++;
		if (tempColumn%(MLCD_BYTES_LINE+1) == 0)	tempColumn = 1;
		tempRow = row;
	}
}

void MLCDDrawColumnFixed(uint8_t row, uint8_t column, uint8_t sizeInBytes, uint8_t height, uint8_t fillHeight, bool white){
	/*uint16_t i;
	int16_t tempRow = row - 8*sizeInBytes + 1;
	for(i=0; i<height; i++, tempRow--){
		if(tempRow<=0){
			tempRow = MLCD_YRES + tempRow;
		}
		MLCDDrawSquare(sizeInBytes,tempRow, column, white);
		
	}*/
	
	uint8_t tempRow = row, tempColumn = column;
	uint16_t i,j;
	for(i=0;i<sizeInBytes;i++){
		
		for(j=0;j<height;j++){
			if(j<=fillHeight){
				if(white){
					MLCDUpdateByte(MLCD_BYTE_WHITE, tempRow, tempColumn);
				}
				else{
					MLCDUpdateByte(MLCD_BYTE_BLACK, tempRow, tempColumn);
				}
			}
			else{
				if(!white){
					MLCDUpdateByte(MLCD_BYTE_WHITE, tempRow, tempColumn);
				}
				else{
					MLCDUpdateByte(MLCD_BYTE_BLACK, tempRow, tempColumn);
				}
			}
			tempRow--;
			if (tempRow == 0)	tempRow = MLCD_YRES;
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

void MLCDDrawBattery(uint8_t row, uint8_t column,uint8_t percentage, bool white){
	uint16_t i;
	const uint8_t *battery;
	if(percentage<5)		battery = battery_5;
	else if (percentage<10)	battery = battery_10;
	else if (percentage<15)	battery = battery_15;
	else if (percentage<20)	battery = battery_20;
	else if (percentage<25)	battery = battery_25;
	else if (percentage<30)	battery = battery_30;
	else if (percentage<35)	battery = battery_35;
	else if (percentage<40)	battery = battery_40;
	else if (percentage<45)	battery = battery_45;
	else if (percentage<50)	battery = battery_50;
	else if (percentage<55)	battery = battery_55;
	else if (percentage<60)	battery = battery_60;
	else if (percentage<65)	battery = battery_65;
	else if (percentage<70)	battery = battery_70;
	else if (percentage<75)	battery = battery_75;
	else if (percentage<80)	battery = battery_80;
	else if (percentage<85)	battery = battery_85;
	else if (percentage<90)	battery = battery_90;
	else if (percentage<95)	battery = battery_95;
	else					battery = battery_100;
	for(i=0; i<17; i++){
		if(white){
			MLCDUpdateByte(~battery[i*4], row, column);
			MLCDUpdateByte(~battery[i*4 + 1], row, column + 1);
			MLCDUpdateByte(~battery[i*4 + 2], row, column + 2);
			MLCDUpdateByte(~battery[i*4 + 3], row, column + 3);
		}
		else{
			MLCDUpdateByte(battery[i*4], row, column);
			MLCDUpdateByte(battery[i*4 + 1], row, column + 1);
			MLCDUpdateByte(battery[i*4 + 2], row, column + 2);
			MLCDUpdateByte(battery[i*4 + 3], row, column + 3);
		}
		row++;
	}
}

void MLCDDrawRLArrow(uint8_t row, uint8_t column,uint8_t direction, bool white){
	uint16_t i;
	const uint8_t *arrow;
	switch(direction){
		case MLCD_ARROW_LEFT:
			arrow = arrow_left;
			break;
		case MLCD_ARROW_RIGHT:
			arrow = arrow_right;
			break;
		default:
			return;
	
	}
	
	for(i=0; i<17; i++){
		if(white){
			MLCDUpdateByte(~arrow[i*2], row, column);
			MLCDUpdateByte(~arrow[i*2 + 1], row, column + 1);
		}
		else{
			MLCDUpdateByte(arrow[i*2], row, column);
			MLCDUpdateByte(arrow[i*2 + 1], row, column + 1);
		}
		row++;
	}
	
}

void MLCDDrawUDArrow(uint8_t row, uint8_t column,uint8_t direction, bool white){
	uint16_t i;
	const uint8_t *arrow;
	switch(direction){
		case MLCD_ARROW_DOWN:
			arrow = arrow_down;
			break;
		case MLCD_ARROW_UP:
			arrow = arrow_up;	
			break;
		default:
			return;
	
	}
	
	for(i=0; i<11; i++){
		if(white){
			MLCDUpdateByte(~arrow[i*3], row, column);
			MLCDUpdateByte(~arrow[i*3 + 1], row, column + 1);
			MLCDUpdateByte(~arrow[i*3 + 2], row, column + 2);
		}
		else{
			MLCDUpdateByte(arrow[i*3], row, column);
			MLCDUpdateByte(arrow[i*3 + 1], row, column + 1);
			MLCDUpdateByte(arrow[i*3 + 2], row, column + 2);
		}
		row++;
	}
	
}