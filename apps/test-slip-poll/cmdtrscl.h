/**
 * 	Transfer of command (client side)
 */
#ifndef __CMDTRSCL_H__
#define __CMDTRSCL_H__

#include <zxuart.h>

void cmdtrscl_init(zxuart* uart_);

void esp_poll();

#endif /* __CMDTRSCL_H__ */
