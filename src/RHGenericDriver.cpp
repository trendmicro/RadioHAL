// RHGenericDriver.cpp
//
// Copyright (C) 2014 Mike McCauley
// $Id: RHGenericDriver.cpp,v 1.23 2018/02/11 23:57:18 mikem Exp $

#include <RHGenericDriver.h>

RHGenericDriver::RHGenericDriver()
    : _mode(RHModeInitialising), _variablePayloadLen(true),
      _fixedPayloadLen(0),  // usually means "maximum payload size"
      _sizeOfPayloadLen(1), // usually one byte
      _rxBad(0), _rxGood(0), _txGood(0), _cad_timeout(0), _debugEnabled(false),
      _printer(
#ifdef RH_HAVE_SERIAL
          &Serial
#else
          NULL
#endif
      ) {
}

bool RHGenericDriver::init() { return true; }

void RHGenericDriver::printSupportedModulationSchemes() {
    _printer->print("Supported modulation schemes: ");
    _printer->print("ASK: ");
    _printer->print(_supportedModulationSchemes.mod_ASK);
    _printer->print(", OOK: ");
    _printer->print(_supportedModulationSchemes.mod_OOK);
    _printer->print(", 2FSK: ");
    _printer->print(_supportedModulationSchemes.mod_2FSK);
    _printer->print(", 4FSK: ");
    _printer->print(_supportedModulationSchemes.mod_4FSK);
    _printer->print(", 2GFSK: ");
    _printer->print(_supportedModulationSchemes.mod_2GFSK);
    _printer->print(", 4GFSK: ");
    _printer->print(_supportedModulationSchemes.mod_4GFSK);
    _printer->print(", PSK: ");
    _printer->print(_supportedModulationSchemes.mod_PSK);
    _printer->print(", MSK: ");
    _printer->println(_supportedModulationSchemes.mod_MSK);
}

// Blocks until a valid message is received
void RHGenericDriver::waitAvailable() {
  while (!available())
    YIELD;
}

// Blocks until a valid message is received or timeout expires
// Return true if there is a message available
// Works correctly even on millis() rollover
bool RHGenericDriver::waitAvailableTimeout(uint16_t timeout) {
#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->print("Waiting in RX for ");
    _printer->print(timeout);
    _printer->println("ms");
  }
#endif

  unsigned long starttime = millis();
  while ((millis() - starttime) < timeout) {
    if (available())
      return true;

    YIELD;
  }

  return false;
}

bool RHGenericDriver::waitPacketSent() {
  while (_mode == RHModeTx)
    YIELD; // Wait for any previous transmit to finish
  return true;
}

bool RHGenericDriver::waitPacketSent(uint16_t timeout) {
  unsigned long starttime = millis();
  while ((millis() - starttime) < timeout) {
    if (_mode != RHModeTx) // Any previous transmit finished?
      return true;
    YIELD;
  }
  return false;
}

// Wait until no channel activity detected or timeout
bool RHGenericDriver::waitCAD() {
  if (!_cad_timeout)
    return true;

  // Wait for any channel activity to finish or timeout
  // Sophisticated DCF function...
  // DCF : BackoffTime = random() x aSlotTime
  // 100 - 1000 ms
  // 10 sec timeout
  unsigned long t = millis();
  while (isChannelActive()) {
    if (millis() - t > _cad_timeout)
      return false;
#if (RH_PLATFORM == RH_PLATFORM_STM32) // stdlib on STMF103 gets confused if
                                       // random is redefined
    delay(_random(1, 10) * 100);
#else
    delay(random(1, 10) * 100); // Should these values be configurable? Macros?
#endif
  }

  return true;
}

// subclasses are expected to override if CAD is available for that radio
bool RHGenericDriver::isChannelActive() { return false; }

void RHGenericDriver::setPromiscuous(bool promiscuous) {
  _promiscuous = promiscuous;
}

int16_t RHGenericDriver::lastRssi() { return _lastRssi; }

RHGenericDriver::RHMode RHGenericDriver::mode() { return _mode; }

void RHGenericDriver::setMode(RHMode mode) { _mode = mode; }

bool RHGenericDriver::sleep() { return false; }

uint16_t RHGenericDriver::rxBad() { return _rxBad; }

uint16_t RHGenericDriver::rxGood() { return _rxGood; }

uint16_t RHGenericDriver::txGood() { return _txGood; }

void RHGenericDriver::setCADTimeout(unsigned long cad_timeout) {
  _cad_timeout = cad_timeout;
}

void RHGenericDriver::_printTimestamp() {
#ifdef RHAL_DEBUGGING
  char c[20];
  sprintf(c, "%10lu ", millis());
  _printer->print(c);
#endif
}

void RHGenericDriver::setPrinter(Stream *printer) { _printer = printer; }

void RHGenericDriver::setDebug(bool enable) { _debugEnabled = enable; }

bool RHGenericDriver::debug() {
#ifdef RHAL_DEBUGGING
  if (_debugEnabled && _printer != nullptr) {
    _printer->print("[RHAL] ");
    _printTimestamp();
    return true;
  }
#endif
  return false;
}

void RHGenericDriver::printBuffer(const char *prompt, const uint8_t *buf,
                                  uint8_t len) {
#ifdef RHAL_DEBUGGING
  if (!debug())
    return;

  _printer->print("[RHAL] ");
  _printer->print(prompt);
  uint8_t i;
  for (i = 0; i < len; i++) {
    if (i % 16 == 15)
      _printer->println(buf[i], HEX);
    else {
      _printer->print(buf[i], HEX);
      _printer->print(' ');
    }
  }
  _printer->println("");
#endif
}

#if (RH_PLATFORM == RH_PLATFORM_ARDUINO) && defined(RH_PLATFORM_ATTINY)
// Tinycore does not have __cxa_pure_virtual, so without this we
// get linking complaints from the default code generated for pure virtual
// functions
extern "C" void __cxa_pure_virtual() {
  while (1)
    ;
}
#endif
