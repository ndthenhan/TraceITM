
#include "printITM.h"
#include "stm32f4xx.h"
#include <stdarg.h>
#include <stdio.h>

/*  #########################
This is basic retargeting of the _write
syscall to ITM. It allows us to use printf()
and have the output go to the SWO console in
a debugger like CubeIDE or Segger Ozone.
######################################*/

void printITMport(uint8_t port, const char *fmt, ...) {
  char buf[128];
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);
  if (len > 0) {
    for (int i = 0; i < len; i++) {
      // Safety timeout prevents hanging if SWO buffer is full
      uint32_t timeout = 5000;
      while (ITM->PORT[port].u32 == 0 && timeout--)
        ;
      if (timeout > 0) {
        ITM->PORT[port].u8 = (uint8_t)buf[i];
      }
    }
  }
}

/*print port1*/

void printITMport1_hex(void) {
  // ITM->PORT[1].u8 = (uint8_t)(0x55);
  uint32_t timeout = 5000;
  while (ITM->PORT[1].u32 == 0 && timeout--)
    ;
  if (timeout > 0) {
    ITM->PORT[1].u8 = 0x50;
  }
/*

            ITM->PORT[1].u8 = (uint8_t)(0x50);
ITM->PORT[1].u8 = (uint8_t)(0x51);
ITM->PORT[1].u8 = (uint8_t)(0x52);
ITM->PORT[1].u8 = (uint8_t)(0x53);

 */}

void ITM_SendFloat(uint8_t port, float value) {
  uint32_t raw = *(uint32_t *)&value;

  while (ITM->PORT[port].u32 == 0)
    ; // wait until ready
  ITM->PORT[port].u32 = raw;
  /* 
  ITM->PORT[port].u8 = (raw >> 0) & 0xFF;
  ITM->PORT[port].u8 = (raw >> 8) & 0xFF;
  ITM->PORT[port].u8 = (raw >> 16) & 0xFF;
  ITM->PORT[port].u8 = (raw >> 24) & 0xFF;
   */
}

/* int _write(int file, char *ptr, int len)
{
    //__BKPT(0);

    for (int i = 0; i < len; i++)
        ITM_SendChar(ptr[i]);   // CMSIS version
    return len;


} */

/*  #########################
This is 2nd retargeting of the _write
syscall to ITM. It allows us to use printf()
and have the output go to the SWO console in
a debugger like CubeIDE or Segger Ozone.
######################################*/

/* int _write(int file, char *ptr, int len) {
    // Only attempt to send if a debugger is active and trace is enabled
    if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) &&
        (CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {

        for (int i = 0; i < len; i++) {
            ITM_SendChar((*ptr++));
        }
    }

    // Always return the length so the caller (printf) knows
    // the data was "processed," preventing the warning and potential logic
errors. return len;
} */

/*  #########################
This is 3rd retargeting of the _write
syscall to ITM. It allows us to use printf()
and have the output go to the SWO console in
a debugger like CubeIDE or Segger Ozone.
######################################*/

/* int _write(int file, char *ptr, int len) {
   // 1. Check if Trace is enabled globally (DEMCR)
   // 2. Check if ITM is enabled locally (TCR)
   // 3. Check if Stimulus Port 0 is enabled (TER)
   if ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) &&
       (ITM->TCR & ITM_TCR_ITMENA_Msk) &&
       (ITM->TER & (1UL << 0))) {

       for (int i = 0; i < len; i++) {
           // Manual non-blocking check to prevent the "CubeProgrammer Hang"
           // If the port is not ready, we skip this character rather than
locking the CPU uint32_t timeout = 10000; while (ITM->PORT[0].u32 == 0 &&
timeout--);

           if (timeout > 0) {
               ITM->PORT[0].u8 = (uint8_t) *ptr;
           }
           ptr++;
       }
   }
   return len;
} */

/*  #########################
Your current _write relies on DHCSR, which is only set when a debugger
is active. If you want your code to run
(and not hang) even when completely
unplugged from the PC, use this check instead
######################################*/

/* int _write(int file, char *ptr, int len) {
    // Check if ITM is actually enabled locally (TCR) and Port 0 is open
    // This allows the program to run even if no debugger is attached.
    if ((ITM->TCR & ITM_TCR_ITMENA_Msk) && (ITM->TER & 1UL)) {
        for (int i = 0; i < len; i++) {
            // Safety timeout prevents hanging if SWO buffer is full
            uint32_t timeout = 5000;
            while (ITM->PORT[0].u32 == 0 && timeout--);
            if (timeout > 0) {
                ITM->PORT[0].u8 = (uint8_t) *ptr;
            }
            ptr++;
        }
    }
    return len;
} */
