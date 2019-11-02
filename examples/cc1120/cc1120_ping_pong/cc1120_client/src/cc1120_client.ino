// cc1120_client.ino
// -*- mode: C++ -*-

#include <SPI.h>
#include <RH_CC1120.h>

#define PIN_CS 15
#define PIN_IRQ 4 // Connect it to CC1120's GPO2
#define PIN_RST 5

#define RHAL_DEBUGGING

RH_CC1120 cc1120(PIN_CS, PIN_RST, PIN_IRQ);

uint8_t data[] = { 0x00 };

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB

#ifdef RHAL_DEBUGGING
  cc1120.setDebug(true);
  cc1120.setPrinter(&Serial);
#endif

  if (!cc1120.init()) {
    Serial.println("init failed");
    return;
  }
}

void loop()
{
  Serial.println("Sending to cc1120_server");

  // Send a message to cc1120_server

  cc1120.send(data, sizeof(data));
  cc1120.waitPacketSent();

  // Now wait for a reply
  uint8_t buf[RH_CC1120_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (cc1120.waitAvailableTimeout(3000)) {
    if (cc1120.recv(buf, &len)) {
      if (len > 0) {
        data[0] = buf[0];
        Serial.println(data[0], DEC);
      }
    } else
      Serial.println("recv failed");
  } else
    Serial.println("No reply, is cc1120_server running?");

  delay(400);
}
