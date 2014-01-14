#define BDIR	0x00 	//
#define CDIR	0x00    // port directions
#define DDIR	0x72	//

#define BINIT	0x00 	//
#define CINIT	0x00	// port initial states
#define DINIT	0x00	//

#define SLAVE_ADDR 0x08


#define GET_HUMIDITY 0x20
#define GET_PRESSURE 0x21
#define GET_GAS 0x22
#define GET_DUST 0x23

#define DUST_ON 0x24
#define DUST_OFF 0x25
#define GAS_ON 0x26
#define GAS_OFF 0x27
#define PRESSURE_ON 0x28
#define PRESSURE_OFF 0x29

#define TEST_BYTE 0xAA

#define ADC_PRESCALER ((1<<ADPS2) | (1<<ADPS1)) // prescale 64

#define ADC_REF_EXTERNAL (0)
#define ADC_REF_POWER ((1<<REFS0)|(0<<REFS1)) // AVCC as refernce value
#define ADC_REF_INTERNAL ((1<<REFS1) | (1<<REFS0))

#include <avr/io.h>
#include <compat/twi.h>
#include <avr/interrupt.h>

#include "TWI_slave.h"
#include <util/twi.h>
#include "measure.h"
