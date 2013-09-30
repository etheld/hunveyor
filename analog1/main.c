#include "analog1.h"
void init_i2c() {
	// resetting ports to default

	DDRB = BDIR;
	DDRC = CDIR;
	DDRD = DDIR;
	PORTB = BINIT;
	PORTC = CINIT;
	PORTD = DINIT;

	TWI_Slave_Initialise( (SLAVE_ADDR<<1) | (FALSE<<TWI_GEN_BIT) ); // initialize TWI interface with slave_addr
}

void init_AD(void) {

	// reseting port D
	PORTD = (0<<PIND4)	   //mux off
					  | (0<<PIND5)
					  | (0<<PIND6);

	//    7  REFS1
	//    6  REFS0
	//       00 - Referencia az AREF láb, belső referencia lekapcsolva.
	//       01 - Referencia az AVCC láb, AREF láb kondenzátorral testre kötve.
	//       10 - Foglalt
	//       11 - Belső 2.56 Voltos referencia, AREF láb kondenzátorral testre kötve.
	//--------------------------------------------
	//    5  ADLAR
	//--------------------------------------------
	//    4  nem használt
	//--------------------------------------------
	//    3  MUX3
	//    2  MUX2
	//    1  MUX1
	//    0  MUX0

	ADMUX = (0<<MUX0)	  //0. channel (temperature)
					  | (0<<REFS1) | (1<<REFS0)    //AVcc as reference value
					  | (0<<ADLAR);	  //aligned to right

	//    7  ADEN
	//       ADC engedélyezve ha értéke 1, kikapcsolva ha 0.
	//--------------------------------------------
	//    6  ADSC
	//       Egyszeri mérésnél 1-re kell állítani, hogy megtörténjen a mérés.
	//       Folyamatos mérésné ha 1-re állítjuk elindul a mérés,
	//       ami utánna folyamatosan fut.
	//--------------------------------------------
	//    5  ADFR
	//       Ha 1 akkor folyamatos mérés fut, ha 0 akkor egyszeri.
	//--------------------------------------------
	//    4  ADIF
	//       Interrupt Flag - nem kell piszkálni :)
	//       Ha 1 akkor a megszakítás jött létre.
	//--------------------------------------------
	//    3  ADIE
	//       Ha 1 akkor a mérés végén megszakítás jön létre.
	//       Ha 0 akkor a megszakítás kikapcsolva.
	//--------------------------------------------
	//    2  ADSP2
	//    1  ADSP1
	//    0  ADSP0
	//       Előosztás
	//       000 - 1
	//       001 - 2
	//       010 - 4
	//       011 - 8
	//       100 - 16
	//       101 - 32
	//       110 - 64
	//       111 - 128

	ADCSRA = (1<<ADEN)    //adc enable
	        		 | (1<<ADPS2)
	        		 | (1<<ADPS1)
	        		 | (1<<ADPS0)	  // prescale 128
	        		 | (1<<ADIE);	  //AD interrupt enable
}

void SendDataBack(uint16_t data) {
	unsigned char messagebuf[2];
	uint8_t lsb = (uint8_t)data;
	uint8_t msb = data >> 8;
	messagebuf[0] = lsb;
	messagebuf[1] = msb | 0x11;
	TWI_Start_Transceiver_With_Data(messagebuf,2); // sending the reply
}
int main(void)
{

	init_i2c();
	unsigned char messagebuf[8];  // message buffer to receive commands

	sei(); // allow interrupts
	TWI_Start_Transceiver(); // start up the communications
	do {
		if (!TWI_Transceiver_Busy()) {
			if ( TWI_statusReg.RxDataInBuf) { // there is data in the receive buff and last transaction was okay

				TWI_Get_Data_From_Transceiver(messagebuf, 2); // fetch the data to messagebuff
				switch(messagebuf[0]) {
					case GET_TEMPERATURE: SendDataBack(ReadTemperature()); break;
					case GET_SOUND: SendDataBack(ReadTemperature()); break;
					case GET_LIGHT: SendDataBack(ReadLight());break;
					case GET_RED: SendDataBack(ReadRed()); break;
					case GET_YELLOW: SendDataBack(ReadYellow());break;
					case GET_GREEN: SendDataBack(ReadGreen()); break;
					case GET_UV: SendDataBack(ReadUV()); break;
					default: SendDataBack(0xab << 8 | messagebuf[0]);
				}
			}
			if (! TWI_Transceiver_Busy()) {
				TWI_Start_Transceiver(); // restart the transceiver
			}
		}
	} while(1); // infinite loop

	// Set Port D pins as all outputs
//DDRD = 0xff;
// Set all Port D pins as HIGH
//PORTD = 0x00;
	return 1;
}
