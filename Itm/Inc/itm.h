#ifndef ITM_H
#define ITM_H

void ITM_Init(void);
//int ITM_SendChar(int ch);
void DWT_Init(void);

void ITM_Init_Passive(void);
void ITM_Init_Stable(void);

//int _write(int file, char *ptr, int len);

#endif