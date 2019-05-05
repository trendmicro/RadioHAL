// cc1120_server.ino
// -*- mode: C++ -*-

#include <RH_CC1120.h>
#include <SPI.h>

#define PIN_CS 15
#define PIN_IRQ 4 // Connect it to CC1120's GPO2
#define PIN_RST 5

RH_CC1120 cc1120(PIN_CS, PIN_RST, PIN_IRQ);
unsigned long starttime = millis();

void printBuffer(const char* prompt, const uint8_t* buf, uint8_t len)
{
  Serial.print(prompt);
  uint8_t i;
  for (i = 0; i < len; i++)
  {
    if (i % 16 == 15)
      Serial.println(buf[i], HEX);
    else
    {
      Serial.print(buf[i], HEX);
      Serial.print(' ');
    }
  }
  Serial.println("");
}

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

  RH_CC1120::ModemConfig
      regs =
          {0x3A, 0x22, 0x11, 0x05, 0x67, 0x97, 0xCC, 0x22, 0x6C, 0x8A, 0xE1}; // f434MHz_4_FSKd2_3Bw11_7Dr5_7_0dBm_WhitOff_ManchOff

      cc1120.setModemRegisters(&regs);
}

void state_loop() {
  if ((millis() - starttime) >= 3000)
  {
    cc1120.printRadioState();
    starttime = millis();
  }
}

void loop() {

  state_loop();


  if (cc1120.available()) {
    uint8_t buf[RH_CC1120_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (cc1120.recv(buf, &len)) {
      printBuffer("RX: ", buf, len);
    } else
      Serial.println("recv failed");
  }
}
