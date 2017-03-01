#ifndef SPR0_H_DEFINED
#define SPR0_H_DEFINED
#include <types.h>

// Sprite descriptor
typedef struct {
	WORD	sz;		// size of sprite (include header)
	BYTE	w;		// sprite width (in char-places)
	BYTE	h;		// sprite high (in char-places)
	char	datap[];	// sprite data (w*h*8 - without attrs or w*h*9 - with attrs)
}Sprite0;

// Sprite output without attrs
void	spr0_out0(const Sprite0* adr, BYTE x, BYTE y)__naked;

// Sprite output with attrs
void	spr0_out0_attr(const Sprite0* adr, BYTE x, BYTE y)__naked;

// Output mode PUT (only for pixels, but not for atts)
void	spr0_out0_setopt_nop()__naked;

// Output mode AND (only for pixels, but not for atts)
void	spr0_out0_setopt_and()__naked;

// Output mode OR (only for pixels, but not for atts)
void	spr0_out0_setopt_or()__naked;

// Output mode XOR (only for pixels, but not for atts)
void	spr0_out0_setopt_xor()__naked;

// Set screen adress.
// Possible adresses:	0x0000, 0x4000, 0x8000, 0xC0000
//			0x2000, 0x6000, 0xA000, 0xE0000
void spr0_set_scr_adr(WORD adr)__naked;

#endif /* SPR0_H_DEFINED */
