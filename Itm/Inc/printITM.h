#ifndef PRINTITM_H
#define PRINTITM_H
#include <stdint.h>

void printITMport(uint8_t port,const char *fmt, ...);
//void printITMport1(const char *fmt, ...);
void printITMport1_hex(void);
 void ITM_SendFloat(uint8_t port, float value);
#endif // PRINTITM_H 