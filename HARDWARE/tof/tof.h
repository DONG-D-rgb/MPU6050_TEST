#ifndef __TOF_H
#define __TOF_H



#include "stdint.h"

void parse_line(const char *s);
void uart_rx_byte(uint8_t ch);
extern volatile int32_t g_distance_mm;




#endif
