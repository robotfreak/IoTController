
/* LIN PACKET:
   It consist of:
    ___________ __________ _______ ____________ _________ 
   |           |          |       |            |         |
   |Synch Break|Synch Byte|ID byte| Data Bytes |Checksum |
   |___________|__________|_______|____________|_________|
   
   Every byte have start bit and stop bit and it is send LSB first.
   Synch Break - 13 bits of dominant state ("0"), followed by 1 bit recesive state ("1")
   Synch Byte - Byte for Bound rate syncronization, always 0x55
   ID Byte - consist of parity, length and address; parity is determined by LIN standard and depends from address and message length
   Data Bytes - user defined; depend on devices on LIN bus
   Checksum - inverted 256 checksum; data bytes are sumed up and then inverted
*/

#include <Arduino.h>

#define LED_BUILTIN 2
#define RXD2_PIN 16
#define TXD2_PIN 17

#define SYNC_BYTE 0x55

unsigned int baud_rate = 19200; // 9600, 4800, 2400
unsigned long period = 1000*1000 / baud_rate;


void sendBreak() {
	unsigned int del = period*no_bits; // delay for number of bits (no-bits) in microseconds, depends on period
    
    pinMode(TXD2_PIN, OUTPUT);
    digitalWrite(LOW, TXD2_PIN);
    delayMicroseconds(del); // delay
    digitalWrite(HIGH, TXD2_PIN);

}

void sendFrame(unsigned int id) {
    sendBreak();
    Serial2.write(SYNC_BYTE);
    Serial2.write(id << 2)
}

void setup() {
    pinMode (LED_BUILTIN, OUTPUT);
    Serial2.begin(19200, SERIAL_8N1, RXD2_PIN, TXD2_PIN);

}

void loop() {

}
