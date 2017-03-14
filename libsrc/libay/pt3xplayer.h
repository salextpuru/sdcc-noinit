#ifndef PT3XPLAYER
#define PT3XPLAYER

/**
 *	Init player
 */
void pt3Init(void* mod_adress);

/**
 *	Play one quark (20 millisec).
 *	Its function must be called every 20ms
 *	for playing 
 */
void pt3Play();

/**
 * 	Mute
 */
void pt3Mute();

/**
 * 	Disable loop if this bit set
 */
#define PT3_UNLOOP 0x01

/**
 * 	This bit must be set for PT2 or res for PT3
 */
#define PT3_PT2	0x02

/**
 * 	Output channels
 */
#define PT3_ABC	0
#define PT3_ACB	4
#define PT3_CAB	8

/**
 * 	Is set each time, when loop point is passed
 */
#define PT3_LOOP_FLAG 0x80

/**
 * 	Set Mode
 */
void pt3SetMode(char mode);

/**
 * 	Get Mode
 */
char pt3GetMode();

#endif /* PT3XPLAYER */
