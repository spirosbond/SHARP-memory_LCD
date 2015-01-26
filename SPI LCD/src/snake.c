/*
 * snake.c
 *
 * Created: 20/10/2014 18:14:31
 *  Author: bontom38
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
#include "led.h"
#include "display.h"
#include "snake.h"
#include "fonts.h"

int16_t i, j;
bool released = true;

void playSnake(void){
	uint8_t length = 4, row = 121, column = 25, direction = DIR_RIGHT;
	int16_t positionX[100], positionY[100];
	bool newBait=true, lost = false;
	int16_t baitX =0, baitY =0, tailX,tailY;
	
	//ioport_configure_port_pin(&PORTF, PIN1_bm, IOPORT_DIR_INPUT);
	//ioport_configure_port_pin(&PORTF, PIN2_bm, IOPORT_DIR_INPUT);
	MLCDClearAll();
	
	for(i=0;i<length;i++){
		positionX[i]=column;
		positionY[i]=row;
		column++;
	}
	
	while(1){
		srand(positionX[0]);
		
		if(newBait){
			LED_Off(LED1);
			bool overlap = false;
			do{
				overlap = false;
				baitY = (rand()%30)*8 + 1;
				baitX = rand()%50+1;
				for(i=0;i<length;i++){
					if(baitX == positionX[i] && baitY == positionY[i])	overlap = true;
					//if(baitY == positionY[i])	overlap = true;
					if(overlap)	LED_On(LED1);
				}
			}while(overlap);
			MLCDDrawSnakeBait(baitY, baitX, false);
			newBait = false;
		}
		
		for(i=0;i<length;i++){
			
			MLCDDrawSquare(1,positionY[i],positionX[i],true);
		}
		tailX = positionX[0];
		tailY = positionY[0];
		
		for(i=0;i<length-1;i++){
			
			positionX[i] = positionX[i+1];
			positionY[i] = positionY[i+1];
		}
		
		if(positionY[length-1]==baitY && positionX[length-1]==baitX){
			length++;
			newBait=true;
			for(i=length-1;i>0;i--){
				
				positionX[i] = positionX[i-1];
				positionY[i] = positionY[i-1];
			}
			positionX[0] = tailX;
			positionY[0] = tailY;
		}
		
		switch(direction){
			case DIR_RIGHT:
			
			positionX[length-1]++;
			if(positionX[length-1]%(MLCD_BYTES_LINE+1) == 0)	positionX[length-1] = 1;
			
			for(i=0;i<length-1;i++){
				if(positionX[length-1] == positionX[i] && positionY[length-1] == positionY[i])	lost = true;
			}
			
			break;
			case DIR_UP:
			
			positionY[length-1]=positionY[length-1]-8;
			if(positionY[length-1] < 1)	positionY[length-1] = MLCD_YRES-7;
			
			for(i=0;i<length-1;i++){
				if(positionX[length-1] == positionX[i] && positionY[length-1] == positionY[i])	lost = true;
			}
			
			break;
			case DIR_LEFT:
			
			positionX[length-1]--;
			if(positionX[length-1] == 0)	positionX[length-1] = MLCD_BYTES_LINE;
			
			for(i=0;i<length-1;i++){
				if(positionX[length-1] == positionX[i] && positionY[length-1] == positionY[i])	lost = true;
			}
			
			break;
			case DIR_DOWN:
			
			positionY[length-1]=positionY[length-1]+8;
			if(positionY[length-1]%(MLCD_YRES+1) == 0)	positionY[length-1] = 1;
			
			for(i=0;i<length-1;i++){
				if(positionX[length-1] == positionX[i] && positionY[length-1] == positionY[i])	lost = true;
			}
			
			break;
			default:
			
			break;
		}
		
		for(i=0;i<length;i++){
			
			MLCDDrawSquare(1,positionY[i],positionX[i],false);
		}
		
		MLCDRefreshFrame();
		
		if(lost){
			
			MLCDWriteString("You Lost!",FONT_SIZE_NORMAL,20,19,false);
			//MLCDWriteString("Score: ",37,19,false);
			//MLCDWriteString((char)length,37,26,false);
			MLCDRefreshFrame();
			delay_ms(2000);
			MLCDClearAll();
			sysclk_set_source(CONFIG_SYSCLK_SOURCE);
			sysclk_set_prescalers(CONFIG_SYSCLK_PSADIV, CONFIG_SYSCLK_PSBCDIV);
			return;
		}
		
		for(i=1;i>0;i++){
			if(gpio_pin_is_high(MLCD_PB0) && gpio_pin_is_high(MLCD_PB2)){
				released = true;
			}
			if(released && gpio_pin_is_low(MLCD_PB2)){
				direction++;
				if(direction%4 == 0) direction = 0;
				//released = false;
				/*for(j=1;j>0;j++){
					if(gpio_pin_is_high(MLCD_PB0) && gpio_pin_is_high(MLCD_PB2)){
						released = true;
					}
				}*/
				delay_ms(50);
				break;
			}
			if(released && gpio_pin_is_low(MLCD_PB0)){
				
				direction--;
				if(direction > 3) direction = 3;
				//released = false;
				/*for(j=1;j>0;j++){
					if(gpio_pin_is_high(MLCD_PB0) && gpio_pin_is_high(MLCD_PB2)){
						released = true;
					}
				}*/
				delay_ms(50);
				break;
			}
		}
		
	}
	
}