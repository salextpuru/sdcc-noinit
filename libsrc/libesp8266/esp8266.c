#include <string.h>
#include <esp8266.h>
#include <zxmc_uart.h>
#include <zifi_uart.h>

// Состояние приемника
enum rStatus{
	// Ожидаем приема данных (+IPD)
	rsWait=0,
	// Идет прием данных (номер соед. ex8266_nsock)
	rsData=1,
	// Идет прием ответа на команду
	rsAnswer=2
};

#ifndef ESP8266_NETNAME
#define ESP8266_NETNAME	"esp8266net"
#endif

#ifndef ESP8266_PASSWD
#define ESP8266_PASSWD	"esp8266passwd"
#endif

/**
 * @brief Транспортный UART
 */
static zxuart*		uart;

/**
 * @brief Авторизация (32 символа максимум)
 */
static const char netname[0x20]=ESP8266_NETNAME;
static const char passwd[0x20]=ESP8266_PASSWD;

/**
 * @brief Номер соединения по которому принимаются данные
 */
static uint8_t	ex8266_nsock;

/**
 * @brief Размер данных, которые должны быть Приняты из сокета
 */
static uint16_t ex8266_rsize;

/* КОМАНДЫ */

// ES	Рестартует устройство
#define CMD_RESET	"AT+RST"
// ES	Команда пустышка 
#define CMD_NONE	"AT"
// ES	Получить версию
#define CMD_VERSION	"AT+GMR"
// ES	Установить режим (CL, AP, CL+AP)
#define CMD_MODE	"AT+CWMODE="
// ES	Установить режим (единственное или множественное соединение)
#define CMD_CONMODE	"AT+CIPMUX="
// ES-->AP	Соединиться с точкой доступа
#define CMD_TOAP	"AT+CWJAP="
// ES	Запустить сервер
#define CMD_SERVER	"AT+CIPSERVER="
// ES-->IP:PORT	Соединиться с кем-то
#define CMD_CONNECT	"AT+CIPSTART="
// ES-->IP:PORT	Послать пакет данных
#define CMD_SEND	"AT+CIPSEND="
// IP:PORT-->ES	Принятые данные из сокета
#define CMD_RECV	"+IPD="

// Рестартовать
static int8_t esp8266_reset(){
	
	return 0;
}

static int8_t up(struct tIFNET* eth, uint32_t ip, uint8_t type, uint8_t flags, void* ifdata){
	eth->ip = ip;
	eth->type = type;
	eth->flags = flags;
	
	if(ifdata){
		strcpy(netname, ((esp8266auth*)(ifdata))->netname);
		strcpy(passwd, ((esp8266auth*)(ifdata))->passwd);
	}
	
	// Биты 0 и 1
	switch( flags & 3 ){
		case esp8266ZIFI:{
			uart=zifi_uart();
			break;
		}
		case esp8266ZXMC:{
			uart=zxmc_uart();
			break;
		}
		default:
			return -1;
	}
	
	//
	if( uart->init() ){
		return -1;
	}
	if( uart->setbauds(115200) ){
		return -1;
	}
	//
	return esp8266_reset();
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
