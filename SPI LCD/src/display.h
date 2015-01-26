/*
 * display.h
 *
 * Created: 16/10/2014 16:01:35
 *  Author: bontom38
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>
#include <asf.h>

#define MLCD_WR	0x80 //MLCD write line command
#define MLCD_CM 0x20 //MLCD clear memory command
#define MLCD_TR 0x00 //MLCD NOP command (used to switch VCOM)
//LCD resolution
#define MLCD_XRES		400 //pixels per horizontal line
#define MLCD_YRES		240 //pixels per vertical line
#define MLCD_BYTES_LINE	(MLCD_XRES/8) //number of bytes in a line is 50 B
#define MLCD_FRAME_SIZE (MLCD_YRES * MLCD_BYTES_LINE) //frame size in pixels
//defines the VCOM bit in the command word that goes to the LCD
#define VCOM_HI				0x40
#define VCOM_LO				0x00
#define MLCD_EXTCOMIN_FREQ	1	//frequency of the VCOM PWM signal
#define MLCD_EXTCOMIN_DC	50		//Duty cycle of the PWM signal. Do not change
#define MLCD_BYTE_BLACK		0x00	//8 black pixels (set)
#define MLCD_BYTE_WHITE		0xFF	//8 white pixels (cleared)
#define MLCD_BLACK			false		//boolean flag to set pixel black (set)
#define MLCD_WHITE			true			//boolean flag to set pixel white (cleared)
#define MLCD_PB0			IOPORT_CREATE_PIN(PORTF, PIN2_bp)	//MLCD Push Button 0
#define MLCD_PB1			IOPORT_CREATE_PIN(PORTF, PIN3_bp)	//MLCD Push Button 1
#define MLCD_PB2			IOPORT_CREATE_PIN(PORTF, PIN4_bp)	//MLCD Push Button 2
#define MLCD_PB3			IOPORT_CREATE_PIN(PORTF, PIN5_bp)	//MLCD Push Button 3
#define MLCD_ARROW_UP		0
#define MLCD_ARROW_DOWN		1
#define MLCD_ARROW_LEFT		2
#define MLCD_ARROW_RIGHT	3

#define SPI_MDL		SPIC		//SPI module for MLCD
#define SPI_PORT	PORTC		//Port definition for MLCD
#define SPI_MODE	SPI_MODE_0	//SPI mode for MLCD. 
#define SPI_BAUD	2000000	//SPI Baud Rate of communication with MLCD

#define SPI_SCS		IOPORT_CREATE_PIN(PORTC, PIN1_bp)	//PIN used to Chip Select the MLCD
#define SPI_DISP	IOPORT_CREATE_PIN(PORTC, PIN0_bp)	//PIN used to turn on and off the MLCD

extern struct spi_device spi_device_conf;	//SPI device configuration of MLCD
extern struct pwm_config pwm_cfg;			//PWM configuration for MLCD
extern uint8_t frame[MLCD_YRES][MLCD_BYTES_LINE];	//Complete frame of MLCD separated in bytes

/**
*	Initialize the PINS used by SPI communication with MLCD
*
*/
void spi_init_pins(void);

/**
*	Initialize SPI module for MLCD
*
*/
void spi_init_module(void);

/**
*	Turn Display ON
*
*/
void MLCDTurnOn(void);

/**
*	Turn Display OFF
*
*/
void MLCDTurnOff(void);

/**
*	Initialize MLCD communication and pwm signals
*
*/
void MLCDInit(void);

/**
*	Select the the device at pin SPI_SCS.
*	This function sets this pin high, since the MLCD is selected by a high Signal.
*/
void MLCDSelect(void);

/**
*	Deselect the the device at pin SPI_SCS.
*	This function sets this pin low, since the MLCD is deselected by a low Signal.
*/
void MLCDDeselect(void);

/**
*	Clears complete frame to white (cleared)
*
*/
void MLCDClearAll(void);

/**
*	Clears complete screen to white (cleared) but leaves frame variable intact. Not recommended.
*
*/
void MLCDClearScreen(void);

/**
*	Clears complete frame to white (cleared) but leaves screen as is. Recommended for quick refreshing.
*
*/
void MLCDClearFrame(void);

/**
*	Sets complete frame to black (set) but leaves screen as is. Recommended for quick refreshing.
*
*/
void MLCDSetFrame(void);

/**
*	Sets complete frame to black (set)
*
*/
void MLCDSet(void);

/**
*	Writes a complete line of the MLCD with a byte array
*	uint8_t data: byte array of pixels of the complete line
*/
void MLCDWriteLine(uint8_t data[MLCD_BYTES_LINE], uint8_t linNum);

/**
*	Writes a complete line of the frame with a byte array without resending the write-line-code. Used for faster refresh rate.
*	uint8_t data: byte array of pixels of the complete line
*/
void MLCDAddLine(uint8_t data[MLCD_BYTES_LINE], uint8_t lineNum);

/**
*	Set the complete value of the frame and refresh the MLCD.
*	uint8_t data: byte array of pixels of the complete frame
*/
void MLCDWriteFrame(uint8_t data[MLCD_YRES][MLCD_BYTES_LINE]);

/**
*	Load IMEC logo from program memory and show it to the MLCD
*
*/
void MLCDShowImecLogo(void);

/**
*	Update the MLCD to the status of the frame
*
*/
void MLCDRefreshFrame(void);

/**
*	Update frame byte without refreshing it to the MLCD
*	uint8_t data: Byte with the new values
*	uint8_t row: Frame row from 1 to 240
*	uint8_t column: Frame column byte from 1 to 50
*/
void MLCDUpdateByte(uint8_t data, uint8_t row, uint8_t column);

/**
*	Update frame pixel without refreshing it to the MLCD
*	uint8_t pixelPos: Position of pixel in BYTE.
*	bool v: Bit with the new value of the pixel, MLCD_BLACK or MLCD_WHITE
*	uint8_t row: Frame row from 1 to 240
*	uint8_t column: Frame column byte from 1 to 50
*/
void MLCDUpdatePixel(uint8_t pixelPos, bool v, uint8_t row, uint8_t column);

/**
*	Write a character from fonts.h at the frame without refreshing the MLCD
*	uint8_t character: Character's address from fonts.h
*	uint8_t fontSize: Font size (FONT_SIZE_NORMAL or FONT_SIZE_LARGE)
*	uint8_t nColumnsInBytes: Character's number of bytes per row
*	uint8_t row: Frame row from 1 to 240. Top left of character
*	uint8_t column: Frame column byte from 1 to 50. Top left of character
*	bool white: True if the character should be white (cleared) on black background or false for the opposite
*/
void MLCDWriteCharacter(const uint8_t *character, uint8_t fontSize, uint8_t nColumnsInBytes, uint8_t row, uint8_t column, bool white);

/**
*	Write a string to the frame without refreshing the MLCD
*	char * str: String to be written
*	uint8_t fontSize: Font size (FONT_SIZE_NORMAL or FONT_SIZE_LARGE)
*	uint8_t row: Frame row from 1 to 240. Top left of string
*	uint8_t column: Frame column byte from 1 to 50. Top left of string
*	bool white: True if each character should be white (cleared) on black background or false for the opposite
*/
void MLCDWriteString(char *str, uint8_t fontSize, uint8_t row, uint8_t column, bool white);

/**
*	Writes an unsigned integer to the frame without refreshing the MLCD
*	uint8_t fontSize: Font size (FONT_SIZE_NORMAL or FONT_SIZE_LARGE)
*	uint8_t row: Frame row from 1 to 240. Top left of number
*	uint8_t column: Frame column byte from 1 to 50. Top left of number
*	bool white: True if the digits should be white (cleared) on black background or false for the opposite
*/
void MLCDWriteInt(uint64_t num, uint8_t fontSize, uint8_t row, uint8_t column, bool white);

/**
*	Writes a double to the frame without refreshing the MLCD
*	uint8_t fontSize: Font size (FONT_SIZE_NORMAL or FONT_SIZE_LARGE)
*	uint8_t row: Frame row from 1 to 240. Top left of number
*	uint8_t column: Frame column byte from 1 to 50. Top left of number
*	bool white: True if the digits should be white (cleared) on black background or false for the opposite
*/
void MLCDWriteDouble(double num, uint8_t fontSize, uint8_t row, uint8_t column, bool white);

/**
*	Draws a square in the frame without refreshing the MLCD
*	uint8_t sizeInBytes: Size of the square in number of bytes
*	uint8_t row: Frame row from 1 to 240. Top left of square
*	uint8_t column: Frame column byte from 1 to 50. Top left of square
*	bool white: True if the square should be white (cleared) or false for the opposite
*/
void MLCDDrawSquare(uint8_t sizeInBytes, uint8_t row, uint8_t column, bool white);

/**
*	Draws a column with a specified size in bytes (thickness) and height without refreshing the MLCD
*	uint8_t row: Frame row from 1 to 240. Bottom left of column
*	uint8_t column: Frame column byte from 1 to 50. Bottom left of column
*	uint8_t size: Size (thickness) of column in bytes.
*	uint8_t height: Height of the column in lines (pixels)
*	bool white: True if the column should be white (cleared) or false for the opposite
*/
void MLCDDrawColumn(uint8_t row, uint8_t column, uint8_t sizeInBytes, uint8_t height, bool white);

/**
*	Draws a column with a specified size in bytes (thickness) and height without refreshing the MLCD, while filling it until the fillHeight
*	uint8_t row: Frame row from 1 to 240. Bottom left of column
*	uint8_t column: Frame column byte from 1 to 50. Bottom left of column
*	uint8_t size: Size (thickness) of column in bytes.
*	uint8_t height: Height of the column in lines (pixels)
*	uint8_t fillHeight: Height of the area to be filled in lines (pixels). Must be less-equal than height
*	bool white: True if the column should be white (cleared) or false for the opposite
*/
void MLCDDrawColumnFixed(uint8_t row, uint8_t column, uint8_t sizeInBytes, uint8_t height, uint8_t fillHeight, bool white);

/**
*	Draw a snake bite square icon without refreshing the MLCD
*	uint8_t row: Frame row from 1 to 240. Top left of square
*	uint8_t column: Frame column byte from 1 to 50. Top left of square
*	bool white: True if the icon should be white (cleared) on black background or false for the opposite
*/
void MLCDDrawSnakeBait(uint8_t row, uint8_t column, bool white);

/**
*	Draw the battery icon with the correct filling
*	uint8_t row: Frame row from 1 to 240. Top left of square
*	uint8_t column: Frame column byte from 1 to 50. Top left of square
*	uint8_t percentage: The percentage of the battery from 0~100 %
*	bool white: True if the icon should be white (cleared) on black background or false for the opposite
*/
void MLCDDrawBattery(uint8_t row, uint8_t column,uint8_t percentage, bool white);

/**
*	Draw the Left or Right arrow icon with the correct direction
*	uint8_t row: Frame row from 1 to 240. Top left of square
*	uint8_t column: Frame column byte from 1 to 50. Top left of square
*	uint8_t direction: The direction of the arrow (UP, DOWN, LEFT, RIGHT)
*	bool white: True if the icon should be white (cleared) on black background or false for the opposite
*/
void MLCDDrawRLArrow(uint8_t row, uint8_t column,uint8_t direction, bool white);

/**
*	Draw the Up or Down arrow icon with the correct direction
*	uint8_t row: Frame row from 1 to 240. Top left of square
*	uint8_t column: Frame column byte from 1 to 50. Top left of square
*	uint8_t direction: The direction of the arrow (UP, DOWN, LEFT, RIGHT)
*	bool white: True if the icon should be white (cleared) on black background or false for the opposite
*/
void MLCDDrawUDArrow(uint8_t row, uint8_t column,uint8_t direction, bool white);

#endif /* DISPLAY_H_ */