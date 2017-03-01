#include <wcplugin.h>
#include <string.h>

void	wcPrint(wcWindow* win, const char* text, uint8_t x, uint8_t y, uint8_t color){
	wcPRSRW(win, text, x, y, strlen(text), color);
}
