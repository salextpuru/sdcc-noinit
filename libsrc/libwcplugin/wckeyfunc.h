#ifndef WCKEYFUNC_INCLUDE
#define WCKEYFUNC_INCLUDE

// Function numbers for wcKeyFunc(uint8_t func_num);
#define	wcSPACE		16
#define	wcUP		17
#define	wcDOWN		18
#define	wcLEFT		19
#define	wcRIGHT		20
#define	wcTAB		21
#define	wcENTER		22
#define	wcESC		23
#define	wcBSPC		24
#define	wcPGUP		25
#define	wcPGDN		26
#define	wcHOME		27
#define	wcEND		28
#define	wcF1		29
#define	wcF2		30
#define	wcF3		31
#define	wcF4		32
#define	wcF5		33
#define	wcF6		34
#define	wcF7		35
#define	wcF8		36
#define	wcF9		37
#define	wcF10		38
#define	wcALT		39
#define	wcSHIFT		40
#define	wcCTRL		41
#define	wcDEL		43
#define	wcINS		85
#define	wcCAPS		44
#define	wcANYKEY	45
#define	wcUSPO		46
#define	wcWAITANYKEY	47

// return if key pressed or no
#define wcKeyNoPressed	0x00
#define wcKeyPressed	0x01
uint8_t	wcKeyFunc(uint8_t func_num);


// Опрос клавиш (можно вызывать только 1 раз в фрейм)
// учитывает SHIFT, CL, а так же ENG/RUS
#define wcKeyTableC	0x01
// Только латинские малые буквы и небуквенные символы
#define wcKeyTableALL	0x00
uint8_t wcKbScan(uint8_t table);

#endif /* WCKEYFUNC_INCLUDE */
