#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

RF24 radio(9, 10);  // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

int DetectorLight = 3;   // LED pin (PWM)
unsigned long lastWindow = 0;
int packetCount = 0;


void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  pinMode(DetectorLight, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.display();
}

void loop() {
  while (radio.available()) {
    int data = 0;
    radio.read(&data, sizeof(data));
    packetCount++;
  }

  if (millis() - lastWindow >= 200) {
    int LEDval = map(packetCount, 0, 100, 0, 255); 
    analogWrite(DetectorLight, LEDval);

    Serial.print("Packets: ");
    Serial.print(packetCount);
    lcd.setCursor(0, 0);
    lcd.print("Packets: ");
    lcd.print(packetCount);
    lcd.print("   "); 

    packetCount = 0;
    lastWindow = millis();
  }
}
