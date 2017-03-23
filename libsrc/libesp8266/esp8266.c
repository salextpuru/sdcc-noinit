#include <esp8266.h>
#include <zxmc_uart.h>
#include <zifi_uart.h>

#ifndef ESP8266_USER
#define ESP8266_USER	"esp8266user"
#endif

#ifndef ESP8266_PASSWD
#define ESP8266_PASSWD	"esp8266passwd"
#endif

/**
 * @brief Транспортный UART
 */
static zxuart*		uart;

/**
 * @brief Авторизация
 */
static esp8266auth	auth={
	.user=ESP8266_USER,
	.passwd=ESP8266_PASSWD
};

static int8_t up(struct tIFNET* eth, uint32_t ip, uint8_t type, uint8_t flags, void* ifdata){
	
}

static int8_t down(struct tIFNET* eth, uint16_t flags){
	
}

static int8_t connect(struct tIFNET* eth, uint32_t ip, uint16_t port, uint16_t protocol){
	
}

static int8_t close(struct tIFNET* eth, uint8_t fd ){
	
}

static int16_t read(struct tIFNET* eth, uint8_t fd, void* buf, uint16_t size){
	
}

static int16_t write(struct tIFNET* eth, uint8_t fd, void* buf, uint16_t size){
	
}

static int8_t listen(struct tIFNET* eth, uint8_t port){
	
}

static void poll(struct tIFNET* eth){
	
}

tIFNET IFNET_ESP8266 = {
	//uint16_t	id;
	//uint8_t	type;
	//uint8_t	flags;
	//uint32_t	ip;
	
	.up=up,
	.down=down,
	.connect=connect,
	.close=close,
	.read=read,
	.write=write,
	.listen=listen,
	.poll=poll
};
