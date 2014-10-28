/*
 * fonts.c
 *	
 * Created: 17/10/2014 16:35:12
 *  Author: bontom38
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fonts.h"

const uint8_t * getCharacterImage(char c){
	switch (c){
		case ' ':
		return image_data_Font_0x20;
			break;
		case '!':
		return image_data_Font_0x21;
			break;
		case '\"':
		return image_data_Font_0x22;
			break;
		case '#':
		return image_data_Font_0x23;
			break;
		case '$':
		return image_data_Font_0x24;
			break;
		case '%':
		return image_data_Font_0x25;
			break;
		case '&':
		return image_data_Font_0x26;
			break;
		case '\'':
		return image_data_Font_0x27;
			break;
		case '(':
		return image_data_Font_0x28;
			break;
		case ')':
		return image_data_Font_0x29;
			break;
		case '*':
		return image_data_Font_0x2a;
			break;
		case '+':
		return image_data_Font_0x2b;
			break;
		case ',':
		return image_data_Font_0x2c;
			break;
		case '-':
		return image_data_Font_0x2d;
			break;
		case '.':
		return image_data_Font_0x2e;
			break;
		case '/':
		return image_data_Font_0x2f;
			break;
		case '0':
		return image_data_Font_0x30;
			break;
		case '1':
		return image_data_Font_0x31;
			break;
		case '2':
		return image_data_Font_0x32;
			break;
		case '3':
		return image_data_Font_0x33;
			break;
		case '4':
		return image_data_Font_0x34;
			break;
		case '5':
		return image_data_Font_0x35;
			break;
		case '6':
		return image_data_Font_0x36;
			break;
		case '7':
		return image_data_Font_0x37;
			break;
		case '8':
		return image_data_Font_0x38;
			break;
		case '9':
		return image_data_Font_0x39;
			break;
		case ':':
		return image_data_Font_0x3a;
			break;
		case ';':
		return image_data_Font_0x3b;
			break;
		case '<':
		return image_data_Font_0x3c;
			break;
		case '=':
		return image_data_Font_0x3d;
			break;
		case '>':
		return image_data_Font_0x3e;
			break;
		case '?':
		return image_data_Font_0x3f;
			break;
		case '@':
		return image_data_Font_0x40;
			break;
		case 'A':
		return image_data_Font_0x41;
			break;
		case 'B':
		return image_data_Font_0x42;
			break;
		case 'C':
		return image_data_Font_0x43;
			break;
		case 'D':
		return image_data_Font_0x44;
			break;
		case 'E':
		return image_data_Font_0x45;
			break;
		case 'F':
		return image_data_Font_0x46;
			break;
		case 'G':
		return image_data_Font_0x47;
			break;
		case 'H':
		return image_data_Font_0x48;
			break;
		case 'I':
		return image_data_Font_0x49;
			break;
		case 'J':
		return image_data_Font_0x4a;
			break;
		case 'K':
		return image_data_Font_0x4b;
			break;
		case 'L':
		return image_data_Font_0x4c;
			break;
		case 'M':
		return image_data_Font_0x4d;
			break;
		case 'N':
		return image_data_Font_0x4e;
			break;
		case 'O':
		return image_data_Font_0x4f;
			break;
		case 'P':
		return image_data_Font_0x50;
			break;
		case 'Q':
		return image_data_Font_0x51;
			break;
		case 'R':
		return image_data_Font_0x52;
			break;
		case 'S':
		return image_data_Font_0x53;
			break;
		case 'T':
		return image_data_Font_0x54;
			break;
		case 'U':
		return image_data_Font_0x55;
			break;
		case 'V':
		return image_data_Font_0x56;
			break;
		case 'W':
		return image_data_Font_0x57;
			break;
		case 'X':
		return image_data_Font_0x58;
			break;
		case 'Y':
		return image_data_Font_0x59;
			break;
		case 'Z':
		return image_data_Font_0x5a;
			break;
		case '[':
		return image_data_Font_0x5b;
			break;
		case '\\':
		return image_data_Font_0x5c;
			break;
		case ']':
		return image_data_Font_0x5d;
			break;
		case '^':
		return image_data_Font_0x5e;
			break;
		case '_':
		return image_data_Font_0x5f;
			break;
		case '`':
		return image_data_Font_0x60;
			break;
		case 'a':
		return image_data_Font_0x61;
			break;
		case 'b':
		return image_data_Font_0x62;
			break;
		case 'c':
		return image_data_Font_0x63;
			break;
		case 'd':
		return image_data_Font_0x64;
			break;
		case 'e':
		return image_data_Font_0x65;
			break;
		case 'f':
		return image_data_Font_0x66;
			break;
		case 'g':
		return image_data_Font_0x67;
			break;
		case 'h':
		return image_data_Font_0x68;
			break;
		case 'i':
		return image_data_Font_0x69;
			break;
		case 'j':
		return image_data_Font_0x6a;
			break;
		case 'k':
		return image_data_Font_0x6b;
			break;
		case 'l':
		return image_data_Font_0x6c;
			break;
		case 'm':
		return image_data_Font_0x6d;
			break;
		case 'n':
		return image_data_Font_0x6e;
			break;
		case 'o':
		return image_data_Font_0x6f;
			break;
		case 'p':
		return image_data_Font_0x70;
			break;
		case 'q':
		return image_data_Font_0x71;
			break;
		case 'r':
		return image_data_Font_0x72;
			break;
		case 's':
		return image_data_Font_0x73;
			break;
		case 't':
		return image_data_Font_0x74;
			break;
		case 'u':
		return image_data_Font_0x75;
			break;
		case 'v':
		return image_data_Font_0x76;
			break;
		case 'w':
		return image_data_Font_0x77;
			break;
		case 'x':
		return image_data_Font_0x78;
			break;
		case 'y':
		return image_data_Font_0x79;
			break;
		case 'z':
		return image_data_Font_0x7a;
			break;
		case '{':
		return image_data_Font_0x7b;
			break;
		case '|':
		return image_data_Font_0x7c;
			break;
		case '}':
		return image_data_Font_0x7d;
			break;
		case '~':
		return image_data_Font_0x7e;
			break;
		default:
		return image_data_Font_error;
	}
	
}

char getDigitAsChar(uint8_t n){
	
	switch(n){
		case 0:
		return '0';
		break;
		case 1:
		return '1';
		break;
		case 2:
		return '2';
		break;
		case 3:
		return '3';
		break;
		case 4:
		return '4';
		break;
		case 5:
		return '5';
		break;
		case 6:
		return '6';
		break;
		case 7:
		return '7';
		break;
		case 8:
		return '8';
		break;
		case 9:
		return '9';
		break;
		default:
		return '0';
	}
	
}

char * getUIntAsString(uint64_t num){
	char * charArrayZero = calloc(2, sizeof(char));
	//char charArrayZero[2];
	if(num==0){
		charArrayZero[0] = '0';
		charArrayZero[1] = '\0';
		return charArrayZero;
	}
	free(charArrayZero);
	uint8_t n = log10(num) + 1;
	int16_t i;
	char *charArray = calloc(n+1, sizeof(char));
	//char charArray[n+1];
	for (i=n-1; i>=0; i--, num /= 10){
		
		charArray[i] = getDigitAsChar(num % 10);

	}
	charArray[n] = '\0';
	/*
	char charArray[100];
	sprintf(charArray,"%u",num);
	*/
	return charArray;
}

char * getDoubleAsString(double num){
	/*char * charArrayZero = calloc(2, sizeof(char));
	if(num == 0){
		charArrayZero[0] = '0';
		charArrayZero[1] = '\0';
		return charArrayZero;
	}
	
	uint8_t n = log10(num) + 1;
	int16_t i;
	char *charArray = calloc(n+3+1+1, sizeof(char)); //decimal point + 3 floating point resolution + . + \0
	uint64_t numD = num;
	float numF = (num - numD)*10;
	
	for (i=n-1; i>=0; i--, numD /=10){
		
		charArray[i] = getDigitAsChar(numD % 10);
		
	}
	
	charArray[n] = '.';
	
	for(i=n+1; i<n+4; i++, numF *= 10){
		charArray[i] = getDigitAsChar((uint8_t) numF);
	}
	
	charArray[n+4] = '\0';*/
	//uint8_t n = log10(num) + 1;
	//char *charArray = calloc(n+3+1+1+1, sizeof(char)); //decimal point + 3 floating point resolution + . + \0 + minus (-) in case
	char *charArray = calloc(50,sizeof(char));
	sprintf(charArray,"%g",num);
	
	return charArray;
}