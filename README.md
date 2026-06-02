https://sites.google.com/frisch.org/tricorder/home

RF24 Packet Activity Monitor
This project uses an nRF24L01+ radio module to measure incoming packet activity and display it using:

A PWM LED to indicate packet rate

A 16×2 I2C LCD to show packet count

A 200 ms rolling window for measurement

The receiver drains the NRF24 RX FIFO to ensure accurate packet counts with no lingering or stale packets.

Hardware
Arduino (Uno/Nano/etc.)

nRF24L01+ module

16×2 I2C LCD (0x27)

LED + resistor

Jumper wires

Connections
NRF24 → Arduino
NRF24	Arduino
VCC	3.3 V
GND	GND
CE	9
CSN	10
SCK	13
MOSI	11
MISO	12


LCD
SDA → A4

SCL → A5

LED
Pin 3 (PWM) → LED → resistor → GND

How It Works
The receiver continuously checks radio.available() and reads all packets in the FIFO.
Every 200 ms, the packet count is used to update:
LED brightness (higher = more packets)
LCD display
Serial output (packet count + RPD)
Packet count resets each window.
Transmitter Requirements
Must send 4‑byte fixed‑size payloads
Must use the same pipe address as the receiver
No dynamic payloads unless enabled on both ends

Purpose
This acts as a simple 2.4 GHz activity monitor for NRF24 traffic, useful for testing, scanning, and directional experiments.
