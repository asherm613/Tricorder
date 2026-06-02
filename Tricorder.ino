#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9, 10);  // Declare object & Create Radio
int elephant[1];


void setup() {
  // put your setup code here, to run once:
  radio.begin();
  radio.openWritingPipe(pipe);
}


void loop() {
  elephant[0] = 5;
  radio.write(elephant, sizeof(elephant));
}
