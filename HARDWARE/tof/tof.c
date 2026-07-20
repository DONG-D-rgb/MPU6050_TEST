#include "tof.h"
#include "MPU6050.h"
#include "main.h"
#include "stdio.h"

#define UART_LINE_MAX 64
static char line[UART_LINE_MAX];
static uint16_t idx = 0;
volatile int32_t g_distance_mm = -2;

void parse_line(const char *s)
{
    int d;
    if (sscanf(s, "%d mm", &d) == 1)
    {
        g_distance_mm = d;
    }
}

void uart_rx_byte(uint8_t ch)
{
    if (idx < UART_LINE_MAX - 1)
    {
        line[idx++] = (char)ch;
        if (ch == '\n')
        {
            line[idx] = '\0';
            parse_line(line);
            idx = 0;
        }
    }
    else
    {
        idx = 0;
    }
}
