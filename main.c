


#include <avr/io.h>
#include <util/delay.h>


void ADC_Init(void){
  //Select ADC Reference Voltage, Datasheet Page 217
  //REFS0 bit set, AVcc as Voltage Reference
  ADMUX  &=~ (1<<REFS1);  //Clear REFS1 bit
  ADMUX  |=  (1<<REFS0);  //Set REFS0 bit
  
  //Clear all MUX bits, Sets ADC channel 0, See table 23-4, Page 218
  ADMUX  &=~ (1<<MUX0);
  ADMUX  &=~ (1<<MUX1);
  ADMUX  &=~ (1<<MUX2);
  ADMUX  &=~ (1<<MUX3);
  
  //Set ADC Prescaler, See datasheet page 218
  //Set Prescaler to 128, See table 23-5, Page 219
  //ADC clock should be between 50000 Hz to 200000Hz (Datasheet page 208)
  //CPU clock is 16000000Hz
  //ADC clock = CPU clock / Prescaler
  //ADC clock = 16000000Hz / 128 = 125000Hz
  ADCSRA |=  (1<<ADPS0);
  ADCSRA |=  (1<<ADPS1);
  ADCSRA |=  (1<<ADPS2);
  
  //Enable ADC, Datasheet Page 218
  ADCSRA |=  (1<<ADEN);
}


void ADC_Select_Channel(uint8_t channel){
  //Clear All MUX bits
  ADMUX  &=~ (1<<MUX0);
  ADMUX  &=~ (1<<MUX1);
  ADMUX  &=~ (1<<MUX2);
  ADMUX  &=~ (1<<MUX3);
  
  //Set the Channel
  ADMUX  |=  channel;
}


uint16_t ADC_Read(void){
  //Start conversion by setting ADSC bit
  ADCSRA |=  (1<<ADSC);
  //Wait Until ADIF bit is set
  while(( ADCSRA & (1<<ADIF) ) == 0);
  //Clear ADIF bit by setting it
  ADCSRA |=  (1<<ADIF);
  //Read ADC result by ADCW
  return ADCW;
}

int main(void){
  
  //Initialize ADC by calling ADC_Init();
  ADC_Init();
  //Select ADC Channel by calling ADC_Select_Channel(0);
  //If you want to set ADC channel 5, just call ADC_Select_Channel(5);
  //As example I'm using ADC channel 0
  ADC_Select_Channel(0);
  
  
while(1){
        
		//Get ADC value in val variable
		int val = ADC_Read();
		
		//Do something using ADC value
		if(val <500){
		  //LED on
		}
		else{
		  //LED off
		}
		
		//Add some delay
		_delay_ms(100);
		
	}
}
