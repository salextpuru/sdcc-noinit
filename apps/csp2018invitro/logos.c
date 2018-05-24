#include <spr0.h>
#include <spr0_fade.h>
#include <im2.h>

const unsigned char logos_base[] = {
	0x04, 0x09, 0x20, 0x08, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0x00, 0xf0, 0x00, 0x38, 0x07, 0x80, 0x1f, 0x9f, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0f, 0x81, 0x18, 0x00, 0x7c, 0x0c, 0xc0, 0x06, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
	0xc3, 0x08, 0x00, 0x8e, 0x18, 0x40, 0x04, 0x0e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3,
	0x08, 0x00, 0x06, 0x30, 0x40, 0x0c, 0x14, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf2, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x08,
	0x00, 0x06, 0x30, 0x40, 0x0c, 0x2c, 0x30, 0xf0, 0xfc, 0x3f, 0x00,
	0x00, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x90, 0x00,
	0x04, 0x30, 0xc0, 0x08, 0xcc, 0xe3, 0x18, 0x44, 0x63, 0x00, 0x00,
	0x00, 0x00, 0xe1, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xe0, 0x00, 0x0c,
	0x30, 0xc0, 0x19, 0x88, 0x26, 0x18, 0x4c, 0x42, 0x00, 0x00, 0x00,
	0x01, 0xe1, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x60, 0x00, 0x08, 0x31,
	0xc0, 0x1b, 0x18, 0x66, 0x18, 0x4c, 0x66, 0x00, 0x00, 0x00, 0x01,
	0xe1, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x31, 0xf0, 0x10, 0x1f, 0x80,
	0x16, 0x18, 0x7c, 0x18, 0x48, 0x1e, 0x00, 0x00, 0x00, 0x01, 0xc8,
	0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x04, 0x08, 0x31, 0xf0, 0x20, 0x03, 0x00, 0x3c,
	0x18, 0x4c, 0x18, 0x88, 0x36, 0x00, 0x00, 0x00, 0x01, 0xc8, 0xe0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x18, 0x08, 0x30, 0x00, 0xc0, 0x07, 0x00, 0x38, 0x30,
	0xcc, 0x30, 0x98, 0x64, 0x00, 0x00, 0x00, 0x01, 0xc8, 0xe0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x21, 0x08, 0x30, 0x01, 0x08, 0x06, 0x00, 0x30, 0x30, 0xcc,
	0x31, 0x18, 0xc4, 0x00, 0x00, 0x00, 0x01, 0x6d, 0xe0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3f, 0x0c, 0x60, 0x01, 0xf8, 0x18, 0x00, 0x70, 0x30, 0x8c, 0x65,
	0x15, 0x8d, 0x00, 0x00, 0x00, 0x01, 0xed, 0xe0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
	0x03, 0xc0, 0x07, 0xf0, 0x60, 0x00, 0xf8, 0xf8, 0x87, 0x86, 0x1b,
	0x8e, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x60, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xfa, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
	0xfb, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7d,
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xb0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb5, 0x60, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xa0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f,
	0xcf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x7f, 0xa5, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x30, 0x3f, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0x7e, 0xb0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xb0, 0x3f, 0x30, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x07, 0x01, 0xe0,
	0x70, 0x0e, 0x30, 0xc4, 0xe0, 0xc3, 0x39, 0xc0, 0x70, 0x8e, 0x01,
	0x0f, 0x00, 0x07, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x18, 0x83, 0x31, 0x88,
	0x31, 0x50, 0xcb, 0x11, 0x43, 0x0a, 0x61, 0x8b, 0x96, 0x01, 0x40,
	0xff, 0xf8, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x30, 0xc6, 0x33, 0x0c, 0x63,
	0x30, 0x86, 0x18, 0xc2, 0x1c, 0x63, 0x18, 0x90, 0x02, 0x24, 0x00,
	0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0c, 0x0c, 0x60, 0xcc, 0x66, 0x0c, 0x40, 0x30,
	0x8c, 0x18, 0xc2, 0x18, 0x62, 0x01, 0x20, 0x02, 0x42, 0xbf, 0x40,
	0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0c, 0x0c, 0x60, 0xcc, 0xc6, 0x0c, 0xc0, 0x31, 0x8c,
	0x18, 0xc6, 0x18, 0x66, 0x01, 0xc0, 0x02, 0x85, 0x7e, 0xe0, 0x5a,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x18, 0x0c, 0x40, 0x8f, 0x04, 0x08, 0x80, 0x21, 0x0c, 0x10,
	0x84, 0x30, 0x44, 0x01, 0x60, 0x04, 0x80, 0xff, 0x60, 0x19, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x18, 0x41, 0x88, 0xe4, 0x18, 0x80, 0x67, 0x08, 0x31, 0x9c,
	0x30, 0xc4, 0x03, 0x20, 0x05, 0x49, 0x7a, 0xe2, 0x2d, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
	0x18, 0x43, 0x08, 0x64, 0x30, 0x82, 0x65, 0x08, 0x21, 0x94, 0x31,
	0x84, 0x13, 0x30, 0x04, 0x02, 0xff, 0x41, 0x09, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18,
	0x66, 0x0c, 0xc6, 0x60, 0xc4, 0x6b, 0x8c, 0x61, 0xae, 0x23, 0x06,
	0x22, 0x10, 0x05, 0x15, 0xfe, 0xa2, 0x95, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x3c,
	0x07, 0x83, 0xc0, 0x78, 0x73, 0x07, 0x81, 0xcc, 0x7e, 0x03, 0xc2,
	0x1c, 0x04, 0x02, 0xfd, 0x01, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
	0x04, 0x15, 0xfe, 0xa0, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x04,
	0x02, 0xfd, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x02, 0x09,
	0xfe, 0x82, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x02, 0x02, 0xfd,
	0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x09, 0x7e, 0xa2,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xfd, 0x00, 0x24,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x09, 0xfe, 0xa0, 0x54, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0xbf, 0x4a, 0xe8, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x41, 0x5d, 0x87, 0x10, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x32, 0x2f, 0x4a, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0xe1, 0x00,
	0x01, 0xe1, 0xe0, 0xc1, 0xe0, 0x01, 0x00, 0x00, 0x01, 0xe0, 0x61,
	0xe0, 0x00, 0x00, 0x5e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x10, 0x80, 0x02,
	0x12, 0x31, 0x42, 0x10, 0x01, 0x02, 0x20, 0x02, 0x00, 0x82, 0x00,
	0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x80, 0x00, 0x12,
	0x50, 0x41, 0xe0, 0x01, 0xe2, 0x20, 0x01, 0xe0, 0xc1, 0xe0, 0x00,
	0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x80, 0x01, 0xe2, 0x90,
	0x42, 0x10, 0x01, 0x12, 0x20, 0x00, 0x10, 0x80, 0x10, 0x00, 0x02,
	0x3b, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x42, 0x10, 0x80, 0x02, 0x03, 0x10, 0x42,
	0x10, 0x01, 0x11, 0xe0, 0x02, 0x10, 0x82, 0x10, 0x00, 0x00, 0x55,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x21, 0xe1, 0x00, 0x03, 0xf1, 0xe1, 0xf1, 0xe0,
	0x01, 0xe0, 0x20, 0x01, 0xe0, 0x81, 0xe0, 0x00, 0x01, 0x2a, 0x84,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x42, 0x07, 0x07,
	0x07, 0x07, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x44, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x44, 0x07, 0x07, 0x72, 0x42, 0x07, 0x07,
	0x07, 0x44, 0x44, 0x44, 0x44, 0x47, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x46, 0x44, 0x07, 0x42, 0x72, 0x42, 0x07, 0x07, 0x07,
	0x44, 0x44, 0x44, 0x44, 0x47, 0x44, 0x44, 0x44, 0x44, 0x44, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
	0x05, 0x46, 0x44, 0x07, 0x07, 0x47, 0x47, 0x07, 0x07, 0x07, 0x44,
	0x44, 0x44, 0x44, 0x47, 0x44, 0x44, 0x44, 0x46, 0x06, 0x44, 0x44,
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x44, 0x44, 0x06, 0x47, 0x47, 0x47, 0x47, 0x07, 0x07, 0x44, 0x44,
	0x44, 0x44, 0x47, 0x44, 0x44, 0x44, 0x44, 0x44, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x47, 0x44, 0x44,
	0x44, 0x47, 0x44, 0x44, 0x44, 0x44, 0x44, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x47, 0x47, 0x47, 0x47,
	0x47, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x44, 0x44, 0x44, 0x07,
	0x06, 0x06, 0x06, 0x46, 0x07, 0x07, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x44, 0x44, 0x44, 0x44, 0x44, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07
};

static const unsigned char logos_s0[] = {
	0x64, 0x03, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x33,
	0xfc, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70,
	0x73, 0xfe, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
	0xf0, 0x63, 0x07, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0xf0, 0xe6, 0x03, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x61, 0xb0, 0xc6, 0x03, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x61, 0xb1, 0x86, 0x06, 0x18, 0x0e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x63, 0x31, 0x87, 0xfc, 0x1f, 0xfc, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x63, 0x33, 0x0f, 0xfc, 0x1f, 0xf0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x33, 0x0c, 0x06, 0x30, 0x60,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x36, 0x0c, 0x06, 0x30,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x36, 0x0c, 0x06,
	0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x34, 0x0c,
	0x06, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x3c,
	0x18, 0x0e, 0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
	0x38, 0x1f, 0xfc, 0x60, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x38, 0x1f, 0xf8, 0x60, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
	0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x38, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3f, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
	0xf8, 0x10, 0x00, 0x00, 0x00, 0x80, 0xfc, 0x03, 0xc8, 0x00, 0x00,
	0x07, 0xfc, 0x30, 0x00, 0x00, 0x01, 0x03, 0xfe, 0x07, 0x98, 0x00,
	0x00, 0x06, 0x0e, 0x30, 0x00, 0x00, 0x03, 0x07, 0x87, 0x06, 0x18,
	0x00, 0x00, 0x0c, 0x06, 0x30, 0x00, 0x00, 0x03, 0x0e, 0x03, 0x8c,
	0x30, 0x00, 0x00, 0x0c, 0x06, 0x30, 0xf8, 0x0f, 0x87, 0xcc, 0x01,
	0xbf, 0xf8, 0x00, 0x00, 0x0c, 0x0c, 0x21, 0xfe, 0x1f, 0xcf, 0xdc,
	0x01, 0xbf, 0xf8, 0x00, 0x00, 0x0f, 0xf8, 0x63, 0x06, 0x30, 0xc3,
	0x18, 0x01, 0x8c, 0x30, 0x00, 0x00, 0x1f, 0xf8, 0x60, 0x06, 0x38,
	0x06, 0x18, 0x01, 0x88, 0x20, 0x00, 0x00, 0x18, 0x0c, 0x60, 0xfe,
	0x1e, 0x06, 0x18, 0x01, 0x98, 0x60, 0x00, 0x00, 0x18, 0x0c, 0x63,
	0xfe, 0x07, 0x86, 0x18, 0x01, 0x98, 0x60, 0x00, 0x00, 0x18, 0x0c,
	0xc7, 0x04, 0x01, 0xc6, 0x18, 0x03, 0x18, 0x60, 0x00, 0x00, 0x18,
	0x0c, 0xc6, 0x0c, 0x60, 0xc4, 0x0c, 0x07, 0x18, 0x60, 0x00, 0x00,
	0x30, 0x1c, 0xc6, 0x1c, 0x61, 0xcc, 0x0e, 0x0e, 0x10, 0x40, 0x00,
	0x00, 0x3f, 0xf8, 0xc7, 0xfc, 0x3f, 0x8f, 0x07, 0xfc, 0x30, 0xc0,
	0x00, 0x00, 0x3f, 0xf0, 0xc3, 0xec, 0x1f, 0x07, 0x01, 0xf0, 0x30,
	0xc0, 0x00, 0x46, 0x46, 0x46, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x44, 0x44,
	0x44, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
	0x42, 0x42, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x44, 0x44,
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x46, 0x46, 0x42,
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46
};
static const unsigned char logos_s1[] = {
	0x64, 0x03, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x1e, 0x06, 0xe0,
	0x6f, 0x3c, 0x0f, 0x80, 0xff, 0x00, 0x00, 0x30, 0x0c, 0x7f, 0x05,
	0xf8, 0x7f, 0x7e, 0x1f, 0xe1, 0xff, 0x00, 0x00, 0x30, 0x08, 0xe1,
	0x8e, 0x18, 0xf1, 0xc6, 0x30, 0x61, 0x82, 0x00, 0x00, 0x70, 0x18,
	0xc1, 0x8c, 0x18, 0xe1, 0x86, 0x00, 0x61, 0x86, 0x00, 0x00, 0x60,
	0x19, 0x81, 0x8c, 0x18, 0xc1, 0x06, 0x0f, 0xe1, 0x86, 0x00, 0x00,
	0x60, 0x19, 0x81, 0x8c, 0x18, 0xc3, 0x06, 0x3f, 0xe1, 0x06, 0x00,
	0x00, 0x60, 0x19, 0x81, 0x88, 0x18, 0x83, 0x0c, 0x70, 0x43, 0x06,
	0x00, 0x00, 0x60, 0x31, 0x83, 0x9c, 0x39, 0x83, 0x0c, 0x60, 0xc3,
	0x04, 0x00, 0x00, 0xc0, 0x31, 0xc7, 0x1c, 0x71, 0x82, 0x0c, 0x61,
	0xc3, 0x0c, 0x00, 0x00, 0xc0, 0x30, 0xfe, 0x1f, 0xe1, 0x86, 0x0c,
	0x7f, 0xce, 0x0c, 0x00, 0x00, 0xc0, 0x30, 0x7c, 0x1b, 0xc1, 0x86,
	0x08, 0x3e, 0xce, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0x06,
	0x00, 0xdc, 0x0c, 0x30, 0x06, 0xec, 0x18, 0x00, 0x00, 0x1f, 0xf1,
	0x8c, 0x00, 0xbf, 0x0c, 0x60, 0x05, 0xcc, 0x10, 0x00, 0x00, 0x00,
	0xe1, 0x98, 0x01, 0xc3, 0x18, 0xc0, 0x0f, 0x18, 0x30, 0x00, 0x00,
	0x01, 0xc0, 0xf0, 0x01, 0x83, 0x19, 0x80, 0x0e, 0x18, 0x30, 0x00,
	0x00, 0x03, 0x80, 0xf0, 0x01, 0x83, 0x1b, 0x00, 0x0c, 0x18, 0x30,
	0x00, 0x00, 0x07, 0x00, 0x60, 0x01, 0x83, 0x1d, 0x80, 0x0c, 0x18,
	0x30, 0x00, 0x00, 0x0e, 0x00, 0xe0, 0x01, 0x03, 0x19, 0x80, 0x08,
	0x10, 0x60, 0x00, 0x00, 0x1c, 0x01, 0xb0, 0x03, 0x87, 0x31, 0x80,
	0x18, 0x30, 0x60, 0x00, 0x00, 0x38, 0x03, 0x30, 0x03, 0x8e, 0x30,
	0xc0, 0x18, 0x30, 0xe0, 0x00, 0x00, 0x3f, 0xc7, 0x18, 0x63, 0xfc,
	0x30, 0xc3, 0x18, 0x3f, 0xe0, 0x00, 0x00, 0x7f, 0xce, 0x18, 0xc3,
	0x78, 0x30, 0x66, 0x18, 0x1e, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x46, 0x46, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
	0x45, 0x45, 0x45, 0x45, 0x46, 0x46, 0x46, 0x46, 0x46, 0x45, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x46, 0x45, 0x45, 0x45,
	0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x45, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
	0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46
};

static const unsigned char logos_s2[] = {
	0x64, 0x03, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x43, 0xc3, 0xf9, 0x8c,
	0x78, 0x78, 0x63, 0x1e, 0x00, 0x00, 0x00, 0x60, 0x46, 0x22, 0x19,
	0x0c, 0xcc, 0xc4, 0x43, 0x31, 0x00, 0x00, 0x00, 0x7f, 0xc4, 0x22,
	0x11, 0x08, 0x84, 0x84, 0x42, 0x61, 0x80, 0x00, 0x00, 0x40, 0xc0,
	0x22, 0x11, 0x09, 0x80, 0x04, 0x42, 0x61, 0x80, 0x00, 0x00, 0x40,
	0xc7, 0xe6, 0x13, 0x09, 0x00, 0xfc, 0xfe, 0x41, 0x80, 0x00, 0x00,
	0xc0, 0x88, 0x66, 0x33, 0x19, 0x01, 0x0c, 0xc6, 0x41, 0x00, 0x00,
	0x00, 0xc0, 0x88, 0x64, 0x32, 0x19, 0x09, 0x0c, 0x86, 0x43, 0x00,
	0x00, 0x00, 0x81, 0x88, 0xe4, 0x23, 0x31, 0x99, 0x1c, 0x84, 0x62,
	0x00, 0x00, 0x00, 0x81, 0x87, 0x64, 0x21, 0xd0, 0xf0, 0xec, 0x84,
	0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e,
	0x0e, 0x78, 0x00, 0x00, 0x00, 0x1e, 0x0f, 0xc1, 0x06, 0x00, 0x00,
	0x21, 0x88, 0x86, 0x00, 0x00, 0x00, 0x21, 0x88, 0x61, 0x1c, 0x00,
	0x00, 0x60, 0x99, 0x82, 0x00, 0x00, 0x00, 0x60, 0x98, 0x23, 0x38,
	0x00, 0x00, 0x60, 0x3d, 0x80, 0x04, 0x23, 0xc0, 0x60, 0x18, 0x33,
	0x70, 0x00, 0x00, 0x38, 0x10, 0xe0, 0x04, 0x24, 0x60, 0x38, 0x10,
	0x32, 0xe0, 0x00, 0x00, 0x1e, 0x10, 0x78, 0x04, 0x60, 0x20, 0x1e,
	0x10, 0x33, 0xc0, 0x00, 0x00, 0x03, 0x10, 0x0c, 0x0f, 0xe3, 0xe0,
	0x03, 0x10, 0x23, 0x20, 0x00, 0x00, 0x81, 0x32, 0x04, 0x08, 0x4c,
	0x40, 0x81, 0x30, 0x26, 0x30, 0x00, 0x00, 0xc1, 0x33, 0x04, 0x08,
	0x48, 0x40, 0xc1, 0x30, 0x46, 0x10, 0x00, 0x00, 0x43, 0x21, 0x0c,
	0x08, 0x48, 0xc0, 0x43, 0x20, 0xc4, 0x18, 0x00, 0x00, 0x3e, 0x20,
	0xf8, 0x08, 0xcf, 0x40, 0x3e, 0x3f, 0x04, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7c, 0x0e, 0x07, 0x00, 0xc2,
	0x1e, 0x36, 0x13, 0x7e, 0x00, 0x00, 0x46, 0x42, 0x31, 0x18, 0x80,
	0xc2, 0x63, 0x26, 0x12, 0x10, 0x00, 0x00, 0x42, 0x42, 0x20, 0x90,
	0x40, 0xe6, 0x41, 0x27, 0x32, 0x10, 0x00, 0x00, 0x60, 0x43, 0x60,
	0x30, 0x00, 0xa4, 0x81, 0x25, 0x22, 0x10, 0x00, 0x00, 0x18, 0xc2,
	0x40, 0x20, 0x01, 0xa4, 0x81, 0x2d, 0x22, 0x10, 0x00, 0x00, 0x04,
	0x82, 0x40, 0x20, 0x1d, 0x14, 0x81, 0x68, 0xa6, 0x30, 0x00, 0x00,
	0x84, 0x82, 0x41, 0x20, 0x81, 0x14, 0x83, 0x48, 0xa4, 0x20, 0x00,
	0x00, 0x84, 0x84, 0x23, 0x11, 0x81, 0x14, 0x46, 0x48, 0xa4, 0x20,
	0x00, 0x00, 0x78, 0xf8, 0x1c, 0x0e, 0x01, 0x08, 0x3c, 0x48, 0x44,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x46, 0x46, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x46, 0x45, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
	0x44, 0x44, 0x44, 0x44, 0x46, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x45, 0x44, 0x44, 0x44, 0x44,
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x46, 0x46, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x46, 0x44, 0x44,
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x46, 0x45, 0x45,
	0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x46
};

static const Sprite0*	logos[] = {
	( Sprite0* )&logos_s0,
	( Sprite0* )&logos_s1,
	( Sprite0* )&logos_s2
};

/*
 * Смена картинок
 */
static uint16_t logos_timer;
static uint8_t logos_counter;

// Возвращает константу. Но как удобно:)
static uint8_t	logos_count() {
	return sizeof ( logos ) /sizeof ( Sprite0* );
}

void logos_check() {
	uint8_t i;

	if ( logos_timer >= 500 ) {
		Sprite0* spr=logos[logos_counter];
		logos_timer=0;

		for ( i=0; i<8; i++ ) {
			spr0_fade_step ( spr,5,8 );
			HALT();
		}

		spr0_out0_attr ( spr,5,8 );

		if ( ( ++logos_counter ) >=  logos_count() ) {
			logos_counter=0;
		}
	}
}

void logos_int50() {
	logos_timer++;
}

void logos_put() {
	spr0_out0_attr ( (Sprite0*)logos_base,0,8 );
}
