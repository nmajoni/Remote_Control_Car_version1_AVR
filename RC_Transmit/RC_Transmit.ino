/*
 * RC_Transmit.ino
 *
 * Created: 14-May-17 16:44:34
 * Author: nyasha majoni
 *         nmajoni.com
 */ 

#include <avr/io.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*======================================================*/
/* Communication channel addresses                      */
/*======================================================*/
uint8_t        steer_address = 0x0A;
uint8_t fwd_and_back_address = 0x0B;


RF24 myRadio(7, 8); // CNS, CE

void setup() {
	myRadio.begin();
	myRadio.openWritingPipe(steer_address);
	myRadio.openWritingPipe(fwd_and_back_address);
	myRadio.setPALevel(RF24_PA_HIGH);
}

void loop() {
	delay(5);
	myRadio.stopListening();
	uint16_t potValue   = analogRead(A0);  //from the steering knob
	uint16_t angleValue = map(potValue, 0, 1023, 0, 180);
	myRadio.write(&angleValue, sizeof(angleValue));
}