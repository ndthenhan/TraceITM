#include "itm.h"
#include "stm32f4xx.h"

void ITM_Init(void) {
  // Enable tracing
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  // Enable the trace clock to the physical pins
  // This bit (TRACE_IOEN) is what CubeProgrammer sets automatically.
  DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;

  // Unlock ITM
     ITM->LAR = 0xC5ACCE55;

  // Disable ITM before config
  ITM->TCR = 0;
    ITM->TER = 0;

  // SWO speed = 2 MHz
  TPI->ACPR = (SystemCoreClock / 2000000) - 1;
  // NRZ/Async
  TPI->SPPR = 2;

  // Disable formatter
  TPI->FFCR = 0x100;

  // Enable ITM + SWO + Sync
  ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_TSENA_Msk | ITM_TCR_SWOENA_Msk |
             ITM_TCR_SYNCENA_Msk;

  // Enable stimulus port 0
  //ITM->TER = 1;
// Enable stimulus ports 0 and 1
    ITM->TER = (1 << 0) | (1 << 1);


}
void DWT_Init(void) {
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // Enable DWT
  DWT->CYCCNT = 0;                                // Reset counter
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // Enable cycle counter
}

void ITM_Init_Passive(void) {
  // 1. Enable Trace hardware (Global)
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  // 2. Unlock ITM Access
  ITM->LAR = 0xC5ACCE55;

  // 3. ONLY enable if not already enabled by debugger
  // We avoid setting TCR/ACPR/SPPR to prevent overwriting the Debugger's config
  if (!(ITM->TCR & ITM_TCR_ITMENA_Msk)) {
    ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SWOENA_Msk;
  }

  // 4. Ensure Port 0 is enabled
  ITM->TER |= 1;
}

void ITM_Init_Stable(void) {

  // 1. Enable Global Trace
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  // Enable the trace clock to the physical pins
  // This bit (TRACE_IOEN) is what CubeProgrammer sets automatically.
  DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
  // 2. Unlock ITM (Required for STM32F4)
  ITM->LAR = 0xC5ACCE55;

  // 3. ONLY configure if the ITM isn't already running
  // This prevents breaking the Cortex-Debug connection
  if (!(ITM->TCR & ITM_TCR_ITMENA_Msk)) {
    ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SWOENA_Msk;
    ITM->TER = 0x1; // Enable Port 0

    // Only set speed if we are sure no debugger is already attached
    // Using your 168MHz constant: (168MHz / 2MHz) - 1 = 83
    TPI->ACPR = 83;
    TPI->SPPR = 2; // NRZ mode
  }
}
