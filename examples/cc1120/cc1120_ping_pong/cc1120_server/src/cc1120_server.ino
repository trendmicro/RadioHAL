// cc1120_server.ino
// -*- mode: C++ -*-

#include <RH_CC1120.h>
#include <SPI.h>

#define PIN_CS 15
#define PIN_IRQ 4 // Connect it to CC1120's GPO2
#define PIN_RST 5

RH_CC1120 cc1120(PIN_CS, PIN_RST, PIN_IRQ);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB

  cc1120.setDebug(true);
  cc1120.setPrinter(&Serial);

  if (!cc1120.init()) {
    Serial.println("init failed");
    return;
  }
}

void loop() {
  if (cc1120.available()) {
    uint8_t buf[RH_CC1120_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (cc1120.recv(buf, &len)) {
      buf[0]++;
      Serial.println(buf[0], DEC);
      cc1120.send(buf, 1);
      cc1120.waitPacketSent();
    } else
      Serial.println("recv failed");
  }
}
