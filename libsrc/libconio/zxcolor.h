//------------------------------------------------------------------------------
//	���� ������
//------------------------------------------------------------------------------
#ifndef ZXCOLOR_H
#define ZXCOLOR_H
//------------------------------------------------------------------------------
#define BLACK		0x00
#define BLUE		0x01
#define RED		0x02
#define MAGENTA		0x03
#define GREEN		0x04
#define CYAN		0x05
#define YELLOW		0x06
#define WHITE		0x07


// ������� ������� � ������� ��������
#define ATTRN(t,f)	((f<<3) | (t))
// ������� ������� � ������� ��������
#define ATTRB(t,f)	((f<<3) | (t) | 0x40)

//------------------------------------------------------------------------------
#endif /* ZXCOLOR_H */
