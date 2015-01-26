/*
 * fontsLarge.c
 *
 * Created: 26/11/2014 15:31:59
 *  Author: bontom38
 */ 
#include <stdlib.h>
#include <stdio.h>
#include "fontsLarge.h"

const uint8_t * getLargeCharacterImage(char c, uint8_t* nColumnsInBytes){
	switch (c){
		case ' ':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x20)/sizeof(image_data_LargeFont_0x20[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x20;
		break;
		case '!':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x21)/sizeof(image_data_LargeFont_0x21[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x21;
		break;
		case '\"':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x22)/sizeof(image_data_LargeFont_0x22[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x22;
		break;
		case '#':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x23)/sizeof(image_data_LargeFont_0x23[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x23;
		break;
		case '$':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x24)/sizeof(image_data_LargeFont_0x24[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x24;
		break;
		case '%':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x25)/sizeof(image_data_LargeFont_0x25[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x25;
		break;
		case '&':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x26)/sizeof(image_data_LargeFont_0x26[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x26;
		break;
		case '\'':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x27)/sizeof(image_data_LargeFont_0x27[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x27;
		break;
		case '(':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x28)/sizeof(image_data_LargeFont_0x28[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x28;
		break;
		case ')':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x29)/sizeof(image_data_LargeFont_0x29[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x29;
		break;
		case '*':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x2a)/sizeof(image_data_LargeFont_0x2a[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x2a;
		break;
		case '+':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x2b)/sizeof(image_data_LargeFont_0x2b[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x2b;
		break;
		case ',':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x2c)/sizeof(image_data_LargeFont_0x2c[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x2c;
		break;
		case '-':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x2d)/sizeof(image_data_LargeFont_0x2d[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x2d;
		break;
		case '.':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x2e)/sizeof(image_data_LargeFont_0x2e[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x2e;
		break;
		case '/':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x2f)/sizeof(image_data_LargeFont_0x2f[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x2f;
		break;
		case '0':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x30)/sizeof(image_data_LargeFont_0x30[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x30;
		break;
		case '1':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x31)/sizeof(image_data_LargeFont_0x31[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x31;
		break;
		case '2':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x32)/sizeof(image_data_LargeFont_0x32[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x32;
		break;
		case '3':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x33)/sizeof(image_data_LargeFont_0x33[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x33;
		break;
		case '4':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x34)/sizeof(image_data_LargeFont_0x34[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x34;
		break;
		case '5':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x35)/sizeof(image_data_LargeFont_0x35[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x35;
		break;
		case '6':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x36)/sizeof(image_data_LargeFont_0x36[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x36;
		break;
		case '7':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x37)/sizeof(image_data_LargeFont_0x37[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x37;
		break;
		case '8':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x38)/sizeof(image_data_LargeFont_0x38[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x38;
		break;
		case '9':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x39)/sizeof(image_data_LargeFont_0x39[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x39;
		break;
		case ':':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x3a)/sizeof(image_data_LargeFont_0x3a[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x3a;
		break;
		case ';':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x3b)/sizeof(image_data_LargeFont_0x3b[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x3b;
		break;
		case '<':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x3c)/sizeof(image_data_LargeFont_0x3c[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x3c;
		break;
		case '=':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x3d)/sizeof(image_data_LargeFont_0x3d[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x3d;
		break;
		case '>':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x3e)/sizeof(image_data_LargeFont_0x3e[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x3e;
		break;
		case '?':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x3f)/sizeof(image_data_LargeFont_0x3f[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x3f;
		break;
		case '@':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x40)/sizeof(image_data_LargeFont_0x40[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x40;
		break;
		case 'A':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x41)/sizeof(image_data_LargeFont_0x41[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x41;
		break;
		case 'B':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x42)/sizeof(image_data_LargeFont_0x42[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x42;
		break;
		case 'C':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x43)/sizeof(image_data_LargeFont_0x43[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x43;
		break;
		case 'D':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x44)/sizeof(image_data_LargeFont_0x44[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x44;
		break;
		case 'E':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x45)/sizeof(image_data_LargeFont_0x45[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x45;
		break;
		case 'F':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x46)/sizeof(image_data_LargeFont_0x46[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x46;
		break;
		case 'G':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x47)/sizeof(image_data_LargeFont_0x47[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x47;
		break;
		case 'H':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x48)/sizeof(image_data_LargeFont_0x48[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x48;
		break;
		case 'I':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x49)/sizeof(image_data_LargeFont_0x49[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x49;
		break;
		case 'J':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x4a)/sizeof(image_data_LargeFont_0x4a[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x4a;
		break;
		case 'K':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x4b)/sizeof(image_data_LargeFont_0x4b[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x4b;
		break;
		case 'L':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x4c)/sizeof(image_data_LargeFont_0x4c[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x4c;
		break;
		case 'M':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x4d)/sizeof(image_data_LargeFont_0x4d[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x4d;
		break;
		case 'N':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x4e)/sizeof(image_data_LargeFont_0x4e[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x4e;
		break;
		case 'O':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x4f)/sizeof(image_data_LargeFont_0x4f[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x4f;
		break;
		case 'P':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x50)/sizeof(image_data_LargeFont_0x50[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x50;
		break;
		case 'Q':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x51)/sizeof(image_data_LargeFont_0x51[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x51;
		break;
		case 'R':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x52)/sizeof(image_data_LargeFont_0x52[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x52;
		break;
		case 'S':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x53)/sizeof(image_data_LargeFont_0x53[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x53;
		break;
		case 'T':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x54)/sizeof(image_data_LargeFont_0x54[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x54;
		break;
		case 'U':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x55)/sizeof(image_data_LargeFont_0x55[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x55;
		break;
		case 'V':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x56)/sizeof(image_data_LargeFont_0x56[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x56;
		break;
		case 'W':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x57)/sizeof(image_data_LargeFont_0x57[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x57;
		break;
		case 'X':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x58)/sizeof(image_data_LargeFont_0x58[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x58;
		break;
		case 'Y':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x59)/sizeof(image_data_LargeFont_0x59[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x59;
		break;
		case 'Z':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x5a)/sizeof(image_data_LargeFont_0x5a[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x5a;
		break;
		case '[':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x5b)/sizeof(image_data_LargeFont_0x5b[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x5b;
		break;
		case '\\':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x5c)/sizeof(image_data_LargeFont_0x5c[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x5c;
		break;
		case ']':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x5d)/sizeof(image_data_LargeFont_0x5d[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x5d;
		break;
		case '^':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x5e)/sizeof(image_data_LargeFont_0x5e[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x5e;
		break;
		case '_':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x5f)/sizeof(image_data_LargeFont_0x5f[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x5f;
		break;
		case '`':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x60)/sizeof(image_data_LargeFont_0x60[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x60;
		break;
		case 'a':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x61)/sizeof(image_data_LargeFont_0x61[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x61;
		break;
		case 'b':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x62)/sizeof(image_data_LargeFont_0x62[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x62;
		break;
		case 'c':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x63)/sizeof(image_data_LargeFont_0x63[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x63;
		break;
		case 'd':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x64)/sizeof(image_data_LargeFont_0x64[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x64;
		break;
		case 'e':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x65)/sizeof(image_data_LargeFont_0x65[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x65;
		break;
		case 'f':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x66)/sizeof(image_data_LargeFont_0x66[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x66;
		break;
		case 'g':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x67)/sizeof(image_data_LargeFont_0x67[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x67;
		break;
		case 'h':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x68)/sizeof(image_data_LargeFont_0x68[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x68;
		break;
		case 'i':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x69)/sizeof(image_data_LargeFont_0x69[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x69;
		break;
		case 'j':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x6a)/sizeof(image_data_LargeFont_0x6a[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x6a;
		break;
		case 'k':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x6b)/sizeof(image_data_LargeFont_0x6b[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x6b;
		break;
		case 'l':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x6c)/sizeof(image_data_LargeFont_0x6c[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x6c;
		break;
		case 'm':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x6d)/sizeof(image_data_LargeFont_0x6d[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x6d;
		break;
		case 'n':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x6e)/sizeof(image_data_LargeFont_0x6e[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x6e;
		break;
		case 'o':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x6f)/sizeof(image_data_LargeFont_0x6f[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x6f;
		break;
		case 'p':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x70)/sizeof(image_data_LargeFont_0x70[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x70;
		break;
		case 'q':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x71)/sizeof(image_data_LargeFont_0x71[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x71;
		break;
		case 'r':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x72)/sizeof(image_data_LargeFont_0x72[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x72;
		break;
		case 's':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x73)/sizeof(image_data_LargeFont_0x73[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x73;
		break;
		case 't':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x74)/sizeof(image_data_LargeFont_0x74[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x74;
		break;
		case 'u':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x75)/sizeof(image_data_LargeFont_0x75[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x75;
		break;
		case 'v':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x76)/sizeof(image_data_LargeFont_0x76[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x76;
		break;
		case 'w':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x77)/sizeof(image_data_LargeFont_0x77[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x77;
		break;
		case 'x':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x78)/sizeof(image_data_LargeFont_0x78[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x78;
		break;
		case 'y':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x79)/sizeof(image_data_LargeFont_0x79[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x79;
		break;
		case 'z':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x7a)/sizeof(image_data_LargeFont_0x7a[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x7a;
		break;
		case '{':
			*nColumnsInBytes = sizeof(image_data_LargeFont_0x7b)/sizeof(image_data_LargeFont_0x7b[0])/FONT_SIZE_LARGE;
			return image_data_LargeFont_0x7b;
			break;
			case '|':
			*nColumnsInBytes = sizeof(image_data_LargeFont_0x7c)/sizeof(image_data_LargeFont_0x7c[0])/FONT_SIZE_LARGE;
			return image_data_LargeFont_0x7c;
			break;
		case '}':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x7d)/sizeof(image_data_LargeFont_0x7d[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x7d;
		break;
		case '~':
		*nColumnsInBytes = sizeof(image_data_LargeFont_0x7e)/sizeof(image_data_LargeFont_0x7e[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_0x7e;
		break;
		default:
		*nColumnsInBytes = sizeof(image_data_LargeFont_error)/sizeof(image_data_LargeFont_error[0])/FONT_SIZE_LARGE;
		return image_data_LargeFont_error;
	}
	
}

