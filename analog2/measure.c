#include "analog2.h"

uint16_t ReadChannel(uint8_t channel, uint8_t configurebits) {
#ifdef DEBUG
	return 0xAA;
#endif
	uint8_t low;
	PORTD = configurebits << 4;
	ADMUX = ADC_REF_POWER | (0<ADLAR);
	ADMUX = (ADMUX & 0xF8) | channel; // clears last 3 bits before ORing

	ADCSRA |= (1<<ADSC);    //start ad convert
	while(ADCSRA & (1<<ADSC)); // wait till the data has been converted

	low = ADCL; // must read LSB first

	return (ADCH<<8) | low;

}
uint16_t ReadHumidity() {
	return ReadChannel(0, 0);
}

uint16_t ReadPressure() {
	return ReadChannel(1, 0);
}

uint16_t ReadGas() {
	return ReadChannel(2,0);
}
uint16_t ReadDust() {
	return ReadChannel(3,0);
}

void Gas(int toggle) {
	if (toggle == 1) {
		PORTD |= 0x4;
	} else {
		PORTD &= (~0x4);
	}
}
void Dust(int toggle) {
	if (toggle == 1) {
		PORTD |= 0x8;
	} else {
		PORTD &= (~0x8);
	}
}
void Pressure(int toggle) {
	if (toggle == 1) {
		PORTD |= 0x2;
	} else {
		PORTD &= (~0x2);
	}
}
