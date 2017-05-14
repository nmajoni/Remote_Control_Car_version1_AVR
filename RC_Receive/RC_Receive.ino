/*
 * RC_Receive.ino
 *
 * Created: 14-May-17 16:59:29
 * Author: nyasha majoni
 *         nmajoni.com
 */ 

#include <avr/io.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(7, 8); // CNS, CE
uint8_t addresses = 0x0A;

Servo myServo;

void setup() {
	myServo.attach(5);
	radio.begin();
	radio.openReadingPipe(1, addresses); // STEER
	radio.setPALevel(RF24_PA_HIGH);
}

void loop() {
	delay(5);
	radio.startListening();
	if ( radio.available()) {
		while (radio.available()) {
			int angleV = 0;
			radio.read(&angleV, sizeof(angleV));
			myServo.write(angleV);
		}
	}
}
