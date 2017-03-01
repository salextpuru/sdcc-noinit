#ifndef STC_PLAYER
#define STC_PLAYER

/**
 *	Init player
 */
void stcInit(void* mod_adress)__naked;

/**
 *	Play one quark (20 millisec).
 *	Its function must be called every 20ms
 *	for playing 
 */
void stcPlay()__naked;

/**
 * 	Disable loop if this bit set
 */
#define STC_UNLOOP 0x01

/**
 * 	Is set each time, when loop point is passed
 */
#define STC_LOOP_FLAG 0x80

/**
 * 	Set Mode
 */
void stcSetMode(char mode)__naked;

/**
 * 	Get Mode
 */
char stcGetMode()__naked;

#endif /* STC_PLAYER */
