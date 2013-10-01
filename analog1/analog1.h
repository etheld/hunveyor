#define BDIR	0x00 	//
#define CDIR	0x00    // port directions
#define DDIR	0x72	//

#define BINIT	0x00 	//
#define CINIT	0x00	// port initial states
#define DINIT	0x00	//

#define SLAVE_ADDR 0x07


#define GET_TEMPERATURE 0x20
#define GET_SOUND 0x21
#define GET_LIGHT 0x22
#define GET_RED 0x23
#define GET_YELLOW 0x24
#define GET_GREEN 0x25
#define GET_UV 0x26

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
