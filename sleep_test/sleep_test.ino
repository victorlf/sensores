
#include "LowPower.h"

void setup () 
{
pinMode(5, OUTPUT);
}  

void loop () 
{
//  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
//  for (int i = 0; i < 100; i++) { 
//  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
//                SPI_OFF, USART0_OFF, TWI_OFF);
//  }
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); 
  digitalWrite(5, LOW); 
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); 
}
