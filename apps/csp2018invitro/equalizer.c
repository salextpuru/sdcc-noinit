#include "equalizer.h"
#include <aydump.h>
#include <winprocs.h>

/*
 * Количество буковок в эквалайзере
 */
enum {boxSize=7};

/*
 * Координаты и размеры буковок в эквалайзере
 */
static const struct {
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t h;
} boxText[boxSize] = {
	{0,16,6,6},
	{6,16,4,6},
	{10,16,4,6},

	{16,16,4,6},
	{20,16,4,6},
	{24,16,4,6},
	{28,16,4,6},
};

/*
 * Таблица цветов для эквалайзера
 */
static const uint8_t colorTable[0x10]= {1,1,2,3,4,5,6,7,0101,0101,0102,0103,0104,0105,0106,0107};

void equalizer_draw() {
	// AY DUMP
	ayDumpGet();
	
	// Эквалайзер (подкрашиваем буковки цветами, полученными их дампа AY)
	// Volume
	winSetAtr(boxText[0].x, boxText[0].y, boxText[0].w, boxText[0].h, colorTable[ayDump[8]], 0x07 );
	winSetAtr(boxText[1].x, boxText[1].y, boxText[1].w, boxText[1].h, colorTable[ayDump[9]], 0x07 );
	winSetAtr(boxText[2].x, boxText[2].y, boxText[2].w, boxText[2].h, colorTable[ayDump[10]], 0x07 );
	// Freq
	winSetAtr(boxText[3].x, boxText[3].y, boxText[3].w, boxText[3].h, colorTable[ayDump[1]], 0x07 );
	winSetAtr(boxText[4].x, boxText[4].y, boxText[4].w, boxText[4].h, colorTable[ayDump[3]], 0x07 );
	winSetAtr(boxText[5].x, boxText[5].y, boxText[5].w, boxText[5].h, colorTable[ayDump[5]], 0x07 );
	winSetAtr(boxText[6].x, boxText[6].y, boxText[6].w, boxText[6].h, colorTable[ayDump[6]], 0x07 );
}
