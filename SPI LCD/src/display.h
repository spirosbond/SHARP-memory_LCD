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

#define MLCD_WR 0x80 //MLCD write line command
#define MLCD_CM 0x20 //MLCD clear memory command
#define MLCD_TR 0x00 //MLCD NOP command (used to switch VCOM)
//LCD resolution
#define MLCD_XRES 400 //pixels per horizontal line
#define MLCD_YRES 240 //pixels per vertical line
#define MLCD_BYTES_LINE (MLCD_XRES/8) //number of bytes in a line
#define MLCD_FRAME_SIZE (MLCD_YRES * MLCD_BYTES_LINE)
//defines the VCOM bit in the command word that goes to the LCD
#define VCOM_HI 0x40
#define VCOM_LO 0x00
#define MLCD_EXTCOMIN_FREQ 1
#define MLCD_EXTCOMIN_DC 50
#define MLCD_BYTE_BLACK 0x00
#define MLCD_BYTE_WHITE 0xFF
#define MLCD_BLACK false
#define MLCD_WHITE true

#define SPI_MDL SPIC
#define SPI_PORT PORTC
#define SPI_MODE SPI_MODE_0
#define SPI_BAUD 2000000

#define SPI_SCS IOPORT_CREATE_PIN(PORTC, PIN1_bp)

extern struct spi_device spi_device_conf;
extern struct pwm_config pwm_cfg;
extern uint8_t frame[MLCD_YRES][MLCD_BYTES_LINE];

void spi_init_pins(void);
void spi_init_module(void);
void MLCDInit(void);
void MLCDSelect(void);
void MLCDDeselect(void);
void MLCDClear(void);
void MLCDSet(void);
void MLCDWriteLine(uint8_t data[MLCD_BYTES_LINE], uint8_t linNum);
void MLCDAddLine(uint8_t data[MLCD_BYTES_LINE], uint8_t lineNum);
void MLCDWriteFrame(uint8_t data[MLCD_YRES][MLCD_BYTES_LINE]);
void MLCDShowImecLogo(void);
void MLCDRefreshFrame(void);
void MLCDUpdateByte(uint8_t data, uint8_t row, uint8_t column);
void MLCDUpdatePixel(uint8_t pixelPos, bool v, uint8_t row, uint8_t column);
void MLCDWriteCharacter(const uint8_t *character, uint8_t row, uint8_t column, bool white);
void MLCDWriteString(char *str, uint8_t row, uint8_t column, bool white);
void MLCDWriteUInt(uint64_t num, uint8_t row, uint8_t column, bool white);
void MLCDWriteDouble(double num, uint8_t row, uint8_t column, bool white);
void MLCDDrawSquare(uint8_t sizeInBytes, uint8_t row, uint8_t column, bool white);
void MLCDDrawColumn(uint8_t row, uint8_t column, uint8_t size, uint8_t height, bool white);
void MLCDDrawSnakeBait(uint8_t row, uint8_t column, bool white);

#endif /* DISPLAY_H_ */