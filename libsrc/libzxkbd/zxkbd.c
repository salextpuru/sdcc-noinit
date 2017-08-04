/*
 * Alex Shamin
 * INCOM Tomsk
 * 04:08:2017
 */

#include "zxkbd.h"

//--------------------------------------------------------
// info
//-------------------------------------------------------
//		Data in(port)
// Port	 Adr   0  1  2  3  4
//
// #FEFE  A8   CS  Z  X  С  V
// #FDFE  A9    A  S  D  F  G
// #FBFE  A10   Q  W  E  R  Т
// #F7FE  A11   1  2  3  4  5
// #EFFE  А12   0  9  8  7  6
// #DFFE  A13   P  O  I  U  Y
// #BFFE  A14   En L  K  J  H  
// #7FFE  A15   SP SS M  N  B
//-------------------------------------------------------
//		Data in(port) 		( Ъ Х Э Ж Ю Б Ё )
// Port	 Adr   0  1  2  3  4
//
// #FEFE  A8   CS  Я  Ч  С  М
// #FDFE  A9    Ф  Ы  В  А  П
// #FBFE  A10   Й  Ц  У  К  Е
// #F7FE  A11   1  2  3  4  5
// #EFFE  А12   0  9  8  7  6
// #DFFE  A13   З  Щ  Ш  Г  Н
// #BFFE  A14   En Д  Л  О  Р
// #7FFE  A15   SP SS И  Т  Ь
//-------------------------------------------------------

enum ctlCode{
	CS=1,
	SS=2,
	En=13
};

// Lat Upper Case
static uint8_t lat_upper[8][5]={
	{ CS, 'Z', 'X', 'С', 'V'},	// #FEFE
	{'A', 'S', 'D', 'F', 'G'},	// #FDFE
	{'Q', 'W', 'E', 'R', 'Т'},	// #FBFE
	{'1', '2', '3', '4', '5'},	// #F7FE
	{'0', '9', '8', '7', '6'},	// #EFFE
	{'P', 'O', 'I', 'U', 'Y'},	// #DFFE
	{ En, 'L', 'K', 'J', 'H' },	// #BFFE
	{' ',  SS, 'M', 'N', 'B'}	// #7FFE
};

// Lat Lower Case
static uint8_t lat_lower[8][5]={
	{ CS, 'z', 'x', 'c', 'v'},	// #FEFE
	{'a', 's', 'd', 'f', 'g'},	// #FDFE
	{'q', 'w', 'e', 'r', 't'},	// #FBFE
	{'1', '2', '3', '4', '5'},	// #F7FE
	{'0', '9', '8', '7', '6'},	// #EFFE
	{'p', 'o', 'i', 'u', 'y'},	// #DFFE
	{ En, 'L', 'K', 'J', 'H'},	// #BFFE
	{' ',  SS, 'm', 'n', 'b'}	// #7FFE
};

// Lat Upper Case + Symbol Shift
static uint8_t lat_upper_SS[8][5]={
	{ CS, ':', 'f', '?', '/'},	// #FEFE
	{'~', '|', '\\', '{','}'},	// #FDFE
	{'Q', 'W', 'E', '<', '>'},	// #FBFE
	{'!', '@', '#', '$', '%'},	// #F7FE
	{'_', ')','(', '\'', '&'},	// #EFFE
	{'\"',';', 'I', ']', '['},	// #DFFE
	{ En, '=', '+', '-', '^'},	// #BFFE
	{' ',  SS, '.', ',', '*'}	// #7FFE
};

// Lat Lower Case + Symbol Shift
#define lat_lower_SS lat_upper_SS

void scanINT()__naked{
__asm;

__endasm;
}
