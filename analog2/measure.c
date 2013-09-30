#include "analog2.h"

uint16_t ReadChannel(uint8_t channel, uint8_t configurebits) {
	if (DEBUG) return 0xAA;
	PORTD = configurebits << 4;
	ADMUX = (0 << MUX1) | (0 << MUX0) | (0 << REFS1) | (1 << REFS0) | (0<ADLAR) | channel;
	//ADMUX = (ADMUX & 0xF8) | channel; // clears last 3 bits before ORing
	//ADCSRA |= (1<<ADSC);    //start ad convert
	//while(ADCSRA & (1<<ADSC)); // wait till the data has been converted

	// do it one more time, the result is pretty noise if adc turned on

	ADCSRA |= (1<<ADSC);    //start ad convert
	while(ADCSRA & (1<<ADSC)); // wait till the data has been converted

	return (ADC);
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

