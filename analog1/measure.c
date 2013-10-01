#include "analog1.h"

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
uint16_t ReadTemperature() {
	return ReadChannel(0, 0);
}

uint16_t ReadLight() {
	return ReadChannel(2, 0);
}

uint16_t ReadSound() {
	return ReadChannel(1,0);
}

uint16_t ReadRed() {
	return ReadChannel(3,0);
}
uint16_t ReadYellow() {
	return ReadChannel(3,2);
}
uint16_t ReadGreen() {
	return ReadChannel(3,4);
}
uint16_t ReadUV() {
	return ReadChannel(3,6);
}

