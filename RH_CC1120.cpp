// RH_CC1120.cpp
//
// Driver for Texas Instruments CC1120 transceiver.
//
// Copyright (C) 2019 Trend Micro Incorporated
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

#include <RH_CC1120.h>

// Interrupt vectors for the 3 Arduino interrupt pins
// Each interrupt can be handled by a different instance of RH_CC1120, allowing
// you to have 2 or more LORAs per Arduino
RH_CC1120 *RH_CC1120::_deviceForInterrupt[RH_CC1120_NUM_INTERRUPTS] = {0, 0, 0};
uint8_t RH_CC1120::_interruptCount =
    0; // Index into _deviceForInterrupt for next device

// These are indexed by the values of ModemConfigChoice
// Canned modem configurations generated with the TI SmartRF Studio v7
// version 2.8.0 based on the sample 'Typical settings' Stored in flash
// (program) memory to save SRAM

PROGMEM static const RH_CC1120::ModemConfig
    MODEM_CONFIG_TABLE[] =
{
  //000A  000B  0011  0013  0014  0015  0016  2F01  2F0C  2F0D  2F0E
  { 0x06, 0x03, 0x14, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f868MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x08, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f868MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x08, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x69, 0xA0, 0x00 }, // f169MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x26, 0x1D, 0x03, 0x04, 0x63, 0xA9, 0x2A, 0x00, 0x6C, 0x80, 0x00 }, // f868MHz_ASK_OOKd17_9Bw66_6Dr4_8_12_5dBm_WhitOff_ManchOff
  { 0x53, 0x2F, 0x01, 0x05, 0xA9, 0x99, 0x99, 0x20, 0x76, 0xC0, 0x00 }, // f950MHz_4_GFSKd82_7Bw200_0Dr100_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x14, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f434MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x08, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x76, 0xC0, 0x00 }, // f950MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x48, 0x05, 0x04, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f434MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x99, 0x0D, 0x02, 0x05, 0x99, 0x99, 0x99, 0x20, 0x76, 0xC0, 0x00 }, // f950MHz_2_GFSKd24_9Bw100_0Dr50_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x08, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f434MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x14, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x76, 0xC0, 0x00 }, // f950MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x53, 0x2F, 0x01, 0x05, 0xA9, 0x99, 0x99, 0x20, 0x6C, 0x80, 0x00 }, // f868MHz_4_GFSKd82_7Bw200_0Dr100_15dBm_WhitOff_ManchOff
  { 0x99, 0x0D, 0x02, 0x05, 0x99, 0x99, 0x99, 0x20, 0x6C, 0x80, 0x00 }, // f434MHz_2_GFSKd24_9Bw100_0Dr50_15dBm_WhitOff_ManchOff
  { 0x48, 0x05, 0x04, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x76, 0xC0, 0x00 }, // f950MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x48, 0x05, 0x04, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f868MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x48, 0x05, 0x04, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x69, 0xA0, 0x00 }, // f169MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x48, 0x0D, 0x02, 0x05, 0x93, 0xA9, 0x2A, 0x22, 0x6C, 0x80, 0x00 }, // f868MHz_2_GFSKd20_0Bw100_0Dr38_4_15dBm_WhitOff_ManchOff
  { 0x06, 0x03, 0x14, 0x05, 0x43, 0xA9, 0x2A, 0x22, 0x69, 0xA0, 0x00 }, // f169MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff
  { 0x99, 0x0D, 0x02, 0x05, 0x99, 0x99, 0x99, 0x20, 0x6C, 0x80, 0x00 }  // f868MHz_2_GFSKd24_9Bw100_0Dr50_15dBm_WhitOff_ManchOff
};

// Values for RH_CC112_REG_002B_PA_CFG2
// Caution: this table is indexed by the values of enum TransmitPower
// Do not change one without changing the other.
PROGMEM static const uint8_t paPowerValues[] = {
    0x43, //-11dBm
    0x4f, // -6dBm
    0x56, // -3dBm
    0x5d, //  0dBm
    0x5f, //  1dBm
    0x62, //  2dBm
    0x64, //  3dBm
    0x66, //  4dBm
    0x69, //  5dBm
    0x6b, //  6dBm
    0x6d, //  7dBm
    0x6f, //  8dBm
    0x72, //  9dBm
    0x74, // 10dBm
    0x77, // 11dBm
    0x79, // 12dBm
    0x7b, // 13dBm
    0x7d, // 14dBm
    0x7f  // 15dBm
};

PROGMEM static const uint8_t preambleLenValues[] = {
  0x00, //0 0
  0x08, //1 1
  0x10, //2 2
  0x14, //3 3
  0x18, //4 4
  0x1c, //5 5
  0x20, //6 6
  0x24, //7 7
  0x28, //8 8
  0x2c, //12 9
  0x30, //24 10
  0x34  //30 11
};

PROGMEM static const uint8_t preambleValues[] = {
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  12,
  24,
  30
};

RH_CC1120::RH_CC1120(uint8_t slaveSelectPin, uint8_t resetPin,
                     uint8_t interruptPin, RHGenericSPI &spi)
    : RHNRFSPIDriver(slaveSelectPin, spi), _deviceType(0x0000),
      _rxBufValid(false) {

  _marcStatus1 = RH_CC1120_MARC_STATUS1_NOFAIL; // No failure (see page 106)
  _interruptPin = interruptPin;
  _resetPin = resetPin;
  _myInterruptIndex = 0xff; // Not allocated yet
}

void RH_CC1120::printRadioState() {
#ifdef RHAL_DEBUG
  if (debug()) {
    uint8_t val = spiReadRegister(RH_CC1120_REG_2F94_MARC_STATUS1);
    _printer->print("[RHAL] RH_CC1120_REG_2F94_MARC_STATUS1 = 0x");
    _printer->println(val, HEX);

    val = spiCommand(RH_CC1120_STROBE_3D_SNOP);
    _printer->print("[RHAL] CHIP_RDY = 0x");
    _printer->println(val & RH_CC1120_STATUS_CHIP_RDY_MASK, HEX);

    _printer->print("[RHAL] STATE = 0x");
    _printer->println(val & RH_CC1120_STATUS_STATE_MASK, HEX);
  }
#endif
}

bool RH_CC1120::init() {
  // SPI init start =====================================================
  // The CC1120 has a slightly different init sequence
  pinMode(_slaveSelectPin, OUTPUT);
  digitalWrite(_slaveSelectPin, HIGH);

  pinMode(_resetPin, OUTPUT);

  delay(200);

  digitalWrite(_resetPin, LOW);

  delay(200);

  digitalWrite(_resetPin, HIGH);

  _spi.begin();
  // SPI init done ======================================================


  // CC1120 setup start =================================================
  // Reset the chip
#ifdef RHAL_DEBUG
  if (debug()) _printer->println("[RHAL] SRES");
#endif
  spiCommand(RH_CC1120_STROBE_30_SRES); // Reset

  delay(100);

#ifdef RHAL_DEBUG
  if (debug()) _printer->println("[RHAL] SCAL");
#endif
  spiCommand(RH_CC1120_STROBE_33_SCAL); // Reset

  delay(100);
  setModeIdle();

  waitForMarcState(RH_CC1120_MARC_STATE_IDLE);

  // 0x{PARTNUMBER}{PARTVERSION}
  _deviceType = (uint8_t)spiReadRegister(RH_CC1120_REG_2F8F_PARTNUMBER) << 8;
  _deviceType |= (uint8_t)spiReadRegister(RH_CC1120_REG_2F90_PARTVERSION);

  // radio is now IDLE, we can safely program registers
  setDefaultRegisters();
  setModemConfig(f434MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff);
  // CC1120 setup done ==================================================


  // IRQ setup start ====================================================
  // Determine the interrupt number that corresponds to the interruptPin
  int interruptNumber = digitalPinToInterrupt(_interruptPin);
  if (interruptNumber == NOT_AN_INTERRUPT)
    return false;

#ifdef RH_ATTACHINTERRUPT_TAKES_PIN_NUMBER
  interruptNumber = _interruptPin;
#endif

  // Tell the low level SPI interface we will use SPI within this interrupt
  spiUsingInterrupt(interruptNumber);
  delay(100);

  // Add by Adrien van den Bossche <vandenbo@univ-tlse2.fr> for Teensy
  // ARM M4 requires the below. else pin interrupt doesn't work properly.
  // On all other platforms, its innocuous, belt and braces
  pinMode(_interruptPin, INPUT);

  // Wait for the bus to be clear so we don't get spurious triggers
  for (uint8_t val = LOW; val == LOW; val = digitalRead(_interruptPin));
  // now we can attach the ISRs
#ifdef RHAL_DEBUG
  if (debug()) _printer->println("[RHAL] IRQ bus clear");
#endif

  delay(200);

  // Set up interrupt handler
  // Since there are a limited number of interrupt glue functions isr*()
  // available, we can only support a limited number of devices simultaneously
  // ON some devices, notably most Arduinos, the interrupt pin passed in is
  // actuallt the interrupt number. You have to figure out the
  // interruptnumber-to-interruptpin mapping yourself based on knwledge of what
  // Arduino board you are running on.
  if (_myInterruptIndex == 0xff) {
    // First run, no interrupt allocated yet
    if (_interruptCount <= RH_CC1120_NUM_INTERRUPTS)
      _myInterruptIndex = _interruptCount++;
    else
      return false; // Too many devices, not enough interrupt vectors
  }

  _deviceForInterrupt[_myInterruptIndex] = this;
  if (_myInterruptIndex == 0)
    attachInterrupt(interruptNumber, isr0, RISING);
  else if (_myInterruptIndex == 1)
    attachInterrupt(interruptNumber, isr1, RISING);
  else if (_myInterruptIndex == 2)
    attachInterrupt(interruptNumber, isr2, RISING);
  else
    return false; // Too many devices, not enough interrupt vectors
  // IRQ setup done =====================================================

#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->print("[RHAL] _variablePayloadLen = ");
    _printer->println(_variablePayloadLen);
  }
#endif

  return true;
}

void RH_CC1120::waitForMarcState(uint8_t state) {
#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->println("[RHAL] START MARCSTATE.MARC_STATE ==============================");
    _printer->print("[RHAL] Waiting for MARCSTATE.MARC_STATE == 0b");
    _printer->println(state, BIN);
  }
#endif

  while ((spiReadRegister(RH_CC1120_REG_2F73_MARCSTATE) & RH_CC1120_MARC_STATE_MASK) != state)
    YIELD;

#ifdef RHAL_DEBUG
  if (debug())
    _printer->println("[RHAL] END MARCSTATE.MARC_STATE ==============================");
#endif
}

void RH_CC1120::updateRssi() {
  uint8_t raw_rssi = spiReadRegister(RH_CC1120_REG_2F71_RSSI1); // Was set when sync word was detected

  // Conversion of RSSI value to RX power level in dBm per TI section
  // 5.18.2
  if (raw_rssi >= 128)
    _lastRssi = (((int16_t)raw_rssi - 256) /
        2); // FIXME take care of calibration offset
  else
    _lastRssi =
      ((int16_t)raw_rssi / 2); // FIXME take care of calibration offset

  if (debug()) {
    _printer->print("[RHAL] RSSI = ");
    _printer->println(_lastRssi);
  }
}

// C++ level interrupt handler for this instance
// We use this to get RxDone and TxDone interrupts
void RH_CC1120::handleInterrupt() {
  _marcStatus1 = spiReadRegister(RH_CC1120_REG_2F94_MARC_STATUS1);

#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->println("[RHAL] >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ISR IN");

    _printer->print("[RHAL] _marcStatus1 = 0x");
    _printer->println(_marcStatus1, HEX);
  }
#endif

  /* TX =========================================================================*/
  if (_mode == RHModeTx) {
    /* TXDONE -------------------------------------------------------------------*/
    if (_marcStatus1 == RH_CC1120_MARC_STATUS1_TXDONE) {
      _mode = RHModeIdle; // because of RFEND_CFG0.TXOFF_MODE's default value
      resetTxFifoPointers();
      return;
    }
    /* TXDONE -------------------------------------------------------------------*/

    /* TX ERR -------------------------------------------------------------------*/
    if (_marcStatus1 == RH_CC1120_MARC_STATUS1_TXFIFO_OF ||
        _marcStatus1 == RH_CC1120_MARC_STATUS1_TXFIFO_UF ||
        _marcStatus1 == RH_CC1120_MARC_STATUS1_TX_TOUT ||
        _marcStatus1 == RH_CC1120_MARC_STATUS1_TXON_CCA_FAIL) {

#ifdef RHAL_DEBUG
      if (debug()) _printer->println("[RHAL] Flushing the TXFIFO because of an error");
#endif

      // flush the TX FIFO
      resetTxFifoPointers();
      setModeIdle();

      /* Flushing seems to bring the radio into an unexpected state (i.e., crash) */
      //spiCommand(RH_CC1120_STROBE_3B_SFTX); // flush will IDLE (TX won't be re-tried)
      //_mode = RHModeIdle; // because of RFEND_CFG0.TXOFF_MODE's default value
      return;
    }
    /* TX ERR -------------------------------------------------------------------*/
  }
  /* TX =========================================================================*/


  /* RX =========================================================================*/
  if (_mode == RHModeRx) {
    _bufLen = spiReadRegister(RH_CC1120_REG_2FD7_NUM_RXBYTES);

    /* RXDONE -------------------------------------------------------------------*/
    if (_bufLen > 0 && _bufLen < RH_CC1120_MAX_PAYLOAD_LEN && _marcStatus1 == RH_CC1120_MARC_STATUS1_RXDONE) {
#ifdef RHAL_FIFO_DEBUG
      if (debug()) {
        uint8_t num_rx_bytes = spiReadRegister(RH_CC1120_REG_2FD7_NUM_RXBYTES);
        uint8_t rx_first = spiReadRegister(RH_CC1120_REG_2FD2_RXFIRST);
        uint8_t rx_last = spiReadRegister(RH_CC1120_REG_2FD4_RXLAST);

        _printer->print("[RHAL] found ");
        _printer->print(_bufLen);
        _printer->println(" bytes of data on the RXFIFO");

        _printer->print("[RHAL] found ");
        _printer->print(num_rx_bytes);
        _printer->println(" RXBYTES of data on the RXFIFO");

        _printer->print("[RHAL] RXFIRST = ");
        _printer->println(rx_first);

        _printer->print("[RHAL] RXLAST = ");
        _printer->println(rx_last);
      }
#endif

      // a packet is in the RX FIFO ready to be read: we copy it into _buf
      spiBurstReadRegister((uint16_t)RH_CC1120_REG_003F_FIFO, _buf, _bufLen);

      updateRssi();

      resetRxFifoPointers(); // reset pointers ASAP

#ifdef RHAL_DEBUG
      if (debug() && _bufLen)
        printBuffer("[RHAL] RX: ", _buf, _bufLen);
#endif

      validateRxBuf();

      // because of RFEND_CFG1.RXOFF_MODE's value, the radio will stay in RX
      _mode = RHModeIdle;
      return;
    }
    /* RXDONE -------------------------------------------------------------------*/

    /* RX ERR -------------------------------------------------------------------*/
    if (_marcStatus1 == RH_CC1120_MARC_STATUS1_RXFIFO_OF ||
        _marcStatus1 == RH_CC1120_MARC_STATUS1_RXFIFO_UF) {

#ifdef RHAL_DEBUG
      if (debug()) _printer->println("[RHAL] Flushing the RXFIFO because of an over/underflow error");
#endif

      // flush the RX FIFO
      spiCommand(RH_CC1120_STROBE_3A_SFRX); // flush will IDLE
      _mode = RHModeIdle;
      setModeRx();

      return;
    }
    /* RX ERR -------------------------------------------------------------------*/

    /* RX BAD -------------------------------------------------------------------*/
    if (!_promiscuous && // accept "bad" packets only in promiscuous mode
        (_marcStatus1 == RH_CC1120_MARC_STATUS1_RX_TERM       ||
         _marcStatus1 == RH_CC1120_MARC_STATUS1_PKT_TOO_LONG  ||
         _marcStatus1 == RH_CC1120_MARC_STATUS1_PKT_WROCRC    ||
         _marcStatus1 == RH_CC1120_MARC_STATUS1_PKT_WROADDR )
       ){

#ifdef RHAL_DEBUG
      if (debug()) _printer->println("[RHAL] Flushing the RXFIFO because of a packet that we cannot accept");
#endif

      // flush the RX FIFO
      spiCommand(RH_CC1120_STROBE_3A_SFRX); // flush will IDLE
      _mode = RHModeIdle;
      setModeRx();

      return;
    }
    /* RX BAD -------------------------------------------------------------------*/

    /* RX EXC -------------------------------------------------------------------*/
    if (_marcStatus1 != RH_CC1120_MARC_STATUS1_RXDONE) {
#ifdef RHAL_DEBUG
      if (debug()) _printer->println("[RHAL] Flushing the RXFIFO because of an unexpected RX condition");
#endif

      // flush the RX FIFO
      spiCommand(RH_CC1120_STROBE_3A_SFRX); // flush will IDLE
      _mode = RHModeIdle;
      setModeRx();

      return;
    }
    /* RX EXC -------------------------------------------------------------------*/
  }
  /* RX =========================================================================*/

#ifdef RHAL_DEBUG
  if (debug())
    _printer->println("[RHAL] Unhandled IRQ");
#endif
}

void RH_CC1120::printBuffer(const char* prompt, const uint8_t* buf, uint8_t len)
{
  if (!debug())
    return;

  _printer->print(prompt);
  uint8_t i;
  for (i = 0; i < len; i++)
  {
    if (i % 16 == 15)
      _printer->println(buf[i], HEX);
    else
    {
      _printer->print(buf[i], HEX);
      _printer->print(' ');
    }
  }
  _printer->println("");
}

void RH_CC1120::resetRxFifoPointers() {
  spiWriteRegister(RH_CC1120_REG_2FD2_RXFIRST, 0x00);
  spiWriteRegister(RH_CC1120_REG_2FD4_RXLAST, 0x00);
}

void RH_CC1120::resetTxFifoPointers() {
  spiWriteRegister(RH_CC1120_REG_2FD3_TXFIRST, 0x00);
  spiWriteRegister(RH_CC1120_REG_2FD5_TXLAST, 0x00);
}

// These are low level functions that call the interrupt handler for the correct
// instance of RH_CC1120.
// 3 interrupts allows us to have 3 different devices
void RH_CC1120::isr0() {
  if (_deviceForInterrupt[0])
    _deviceForInterrupt[0]->handleInterrupt();
}
void RH_CC1120::isr1() {
  if (_deviceForInterrupt[1])
    _deviceForInterrupt[1]->handleInterrupt();
}
void RH_CC1120::isr2() {
  if (_deviceForInterrupt[2])
    _deviceForInterrupt[2]->handleInterrupt();
}

void RH_CC1120::spiGenericRegAccess(uint8_t addr, uint8_t *data, uint16_t len) {
  uint16_t i;

#ifdef RHAL_SPI_DEBUG
  if (debug()) {
    _printer->print("[RHAL] spiGenericRegAccess(addr = ");
    _printer->print(addr, HEX);
    _printer->print(", len = ");
    _printer->print(len);
    _printer->println(")");
  }
#endif

  if (addr & RH_CC1120_SPI_READ_MASK) {
    if (addr & RH_CC1120_SPI_BURST_MASK) {
      for (i = 0; i < len; i++) {
        *data = _spi.transfer(0);
        data++;
      }
    } else
      *data = _spi.transfer(0);
  } else {
    if (addr & RH_CC1120_SPI_BURST_MASK) {
      for (i = 0; i < len; i++) {
        _spi.transfer(*data);
        data++;
      }
    } else
      _spi.transfer(*data);
  }

  return;
}

uint8_t RH_CC1120::shortRegAccess(uint8_t accessType, uint8_t addrByte,
                                  uint8_t *data, uint16_t len) {
  uint8_t readValue;

  ATOMIC_BLOCK_START;
  _spi.beginTransaction();
  digitalWrite(_slaveSelectPin, LOW);

  readValue = _spi.transfer(accessType | addrByte);
  spiGenericRegAccess(accessType | addrByte, data, len);

  digitalWrite(_slaveSelectPin, HIGH);
  _spi.endTransaction();
  ATOMIC_BLOCK_END;

#ifdef RHAL_SPI_DEBUG
  if (debug()) {
    _printer->print("[RHAL] shortRegAccess(accessType = ");
    _printer->print(accessType, HEX);
    _printer->print(", addrByte = ");
    _printer->print(addrByte, HEX);
    _printer->print(", len = ");
    _printer->print(len);
    _printer->print(") = ");
    _printer->println(readValue);
  }
#endif

  return readValue;
}

uint8_t RH_CC1120::longRegAccess(uint8_t accessType, uint8_t extAddr,
                                 uint8_t regAddr, uint8_t *data, uint8_t len) {
  uint8_t readValue;

  ATOMIC_BLOCK_START;
  _spi.beginTransaction();
  digitalWrite(_slaveSelectPin, LOW);

  readValue = _spi.transfer(accessType | extAddr);
  _spi.transfer(regAddr);

  spiGenericRegAccess(accessType | extAddr, data, len);

  digitalWrite(_slaveSelectPin, HIGH);
  _spi.endTransaction();
  ATOMIC_BLOCK_END;

#ifdef RHAL_SPI_DEBUG
  if (debug()) {
    _printer->print("[RHAL] longRegAccess(accessType = ");
    _printer->print(accessType, HEX);
    _printer->print(", extAddr = ");
    _printer->print(extAddr, HEX);
    _printer->print(", regAddr = ");
    _printer->print(regAddr, HEX);
    _printer->print(", len = ");
    _printer->print(len);
    _printer->print(") = ");
    _printer->println(readValue);
  }
#endif

  return readValue;
}

uint8_t RH_CC1120::spiReadRegisterWrapper(uint16_t reg, uint8_t *data,
                                          uint8_t len) {

  uint8_t tempExt = (uint8_t)(reg >> 8);
  uint8_t tempAddr = (uint8_t)(reg & 0x00FF);
  uint8_t rc = 0x00;

  if (!tempExt) {
    rc = shortRegAccess((RH_CC1120_SPI_READ_MASK | RH_CC1120_SPI_BURST_MASK),
                        tempAddr, data, len);
  } else if (tempExt == 0x2F) {
    rc = longRegAccess((RH_CC1120_SPI_READ_MASK | RH_CC1120_SPI_BURST_MASK),
                       tempExt, tempAddr, data, len);
  }

#ifdef RHAL_SPI_DEBUG
  if (debug()) {
    _printer->print("[RHAL] spiReadRegisterWrapper(reg = ");
    _printer->print(reg, HEX);
    _printer->print(", len = ");
    _printer->print(len);
    _printer->print(") = ");
    _printer->println(rc);
  }
#endif

  return rc;
}

uint8_t RH_CC1120::spiWriteRegisterWrapper(uint16_t reg, const uint8_t *data,
                                           uint8_t len) {
  uint8_t tempExt = (uint8_t)(reg >> 8);
  uint8_t tempAddr = (uint8_t)(reg & 0x00FF);
  uint8_t rc = 0x00;

  if (!tempExt) {
    rc = shortRegAccess((RH_CC1120_SPI_WRITE_MASK | RH_CC1120_SPI_BURST_MASK),
                        tempAddr, (uint8_t *)data, len);
  } else if (tempExt == 0x2F) {
    rc = longRegAccess((RH_CC1120_SPI_WRITE_MASK | RH_CC1120_SPI_BURST_MASK),
                       tempExt, tempAddr, (uint8_t *)data, len);
  }

  return rc;
}

uint8_t RH_CC1120::spiReadRegister(uint16_t reg) {
  uint8_t data = 0x00;
  uint8_t len = 1;
  spiReadRegisterWrapper(reg, &data, len);

#ifdef RHAL_SPI_DEBUG
  if (debug()) {
    _printer->print("[RHAL] spiReadRegister(reg = ");
    _printer->print(reg, HEX);
    _printer->print(") = ");
    _printer->println(data);
  }
#endif

  return data;
}

uint8_t RH_CC1120::spiWriteRegister(uint16_t reg, uint8_t val) {
#ifdef RHAL_SPI_DEBUG
  if (debug()) {
    _printer->print("[RHAL] spiWriteRegister(reg = ");
    _printer->print(reg, HEX);
    _printer->print(", val = ");
    _printer->print(val, HEX);
    _printer->println(");");
  }
#endif

  return spiWriteRegisterWrapper(reg, &val, 1);
}

uint8_t RH_CC1120::spiBurstReadRegister(uint16_t reg, uint8_t *dst,
                                        uint8_t len) {
  return spiReadRegisterWrapper(reg, dst, len);
}

uint8_t RH_CC1120::spiBurstWriteRegister(uint16_t reg, const uint8_t *src,
                                         uint8_t len) {
  return spiWriteRegisterWrapper(reg, src, len);
}

bool RH_CC1120::printRegisters() {
  if (!debug())
    return false;

  uint8_t i;
  for (i = 0; i <= 0x2f; i++) {
    _printer->print(i, HEX);
    _printer->print(": ");
    _printer->println(spiReadRegister(i), HEX);
  }

  // Burst registers
  for (i = 0x30; i <= 0x3e; i++) {
    _printer->print(i, HEX);
    _printer->print(": ");
    _printer->println(spiReadRegister(i),
                      HEX); // burst access to 1 byte makes little sense
  }

  return true;
}

// RadioHAL makes no assumptions on the payload content: all messages are good
void RH_CC1120::validateRxBuf() {
  // if variable payload len mode, we expect at least 1 byte in the buffer
  if (_variablePayloadLen) {
    if (_bufLen < 1) return; // there's not the length byte

    // _bufLen >= 1
    if (_buf[0] < 1) return; // length byte is there, but it's < 1
  }

  // fixed payload len mode: anything is good (we assume the user knows what
  // they're doing)

  _rxGood++;
  _rxBufValid = true;
}

bool RH_CC1120::available() {
  if (_mode == RHModeTx)
    return false;

  if (_rxBufValid) // Will be set by the interrupt handler when a good message
                   // is received
    return true;

  setModeRx(); // Make sure we are receiving

  return false; // Nothing yet
}

void RH_CC1120::clearRxBuf() {
  ATOMIC_BLOCK_START;
  _rxBufValid = false;
  _bufLen = 0;
  ATOMIC_BLOCK_END;
}

bool RH_CC1120::recv(uint8_t *buf, uint8_t *len) {
  if (!available())
    return false;

  uint8_t skip = 0;

  if (buf && len) {
    ATOMIC_BLOCK_START;
    if (*len > _bufLen)
      *len = _bufLen;

    // if in variable payload mode, we skip `_sizeOfPayloadLen` bytes, which
    // hold the encoded length; we validate that, and copy the data

    // FIXME: instead of reading the len as 1 byte, read it as `_sizeOfPayloadLen` bytes

    if (_variablePayloadLen && _buf[0] > 0 && _buf[0] <= RH_CC1120_MAX_PAYLOAD_LEN - 1) {
      *len = _buf[0];                    // set the length as the encoded length
      skip += _sizeOfPayloadLen;

#ifdef RHAL_DEBUG
      if (debug()) {
        _printer->print("[RHAL] The variable len encoded in the packet is ");
        _printer->println(_buf[0], DEC);
      }
#endif
    }

    memcpy(buf, &_buf[skip], *len);
    ATOMIC_BLOCK_END;
  }

  clearRxBuf(); // This message accepted and cleared

#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->print("[RHAL] RX successful: ");
    _printer->print(*len);
    _printer->println(" bytes copied");
  }
#endif

  return true;
}

bool RH_CC1120::checkPayloadLen(uint8_t len) {
  if (_variablePayloadLen)
    return (len + _sizeOfPayloadLen) <= RH_CC1120_MAX_PAYLOAD_LEN;

  return len <= RH_CC1120_MAX_MESSAGE_LEN;
}

bool RH_CC1120::send(const uint8_t *data, uint8_t len) {
  if (!checkPayloadLen(len))
    return false;

#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->print("[RHAL] sending ");
    _printer->print(len);
    _printer->println(" bytes of data");
  }
#endif

  waitPacketSent(); // Make sure we dont interrupt an outgoing message

  if (!waitCAD())
    return false; // Check channel activity

  // write data length
  if (_variablePayloadLen)
    spiWriteRegister(RH_CC1120_REG_003F_FIFO, len);

  // write the data in burst mode
  spiBurstWriteRegister(RH_CC1120_REG_003F_FIFO, data, len);

#ifdef RHAL_FIFO_DEBUG
  if (debug()) {
    uint8_t val = spiReadRegister(RH_CC1120_REG_2FD6_NUM_TXBYTES);
    uint8_t tx_first = spiReadRegister(RH_CC1120_REG_2FD3_TXFIRST);
    uint8_t tx_last = spiReadRegister(RH_CC1120_REG_2FD5_TXLAST);

    _printer->print("[RHAL] wrote ");
    _printer->print(len);
    _printer->println(" bytes of data on the TXFIFO (+1 byte for the length)");

    _printer->print("[RHAL] found ");
    _printer->print(val);
    _printer->println(" TXBYTES of data on the TXFIFO");

    _printer->print("[RHAL] TXFIRST = ");
    _printer->println(tx_first);

    _printer->print("[RHAL] TXLAST = ");
    _printer->println(tx_last);
  }
#endif

#ifdef RHAL_DEBUG
  if (debug()) printBuffer("[RHAL] TX: ", data, len);
#endif

  setModeTx();

  return true;
}

uint8_t RH_CC1120::maxMessageLength() { return RH_CC1120_MAX_MESSAGE_LEN; }

void RH_CC1120::setModeIdle() {
  if (_mode != RHModeIdle) {
#ifdef RHAL_DEBUG
    if (debug()) _printer->println("[RHAL] SIDLE");
#endif

    resetRxFifoPointers();
    resetTxFifoPointers();

    spiCommand(RH_CC1120_STROBE_36_SIDLE);
    _mode = RHModeIdle;
  }
}

bool RH_CC1120::sleep() {
  if (_mode != RHModeSleep) {
    spiCommand(RH_CC1120_STROBE_36_SIDLE); // preceeding sleep IDLE first
    spiCommand(RH_CC1120_STROBE_39_SPWD);
    _mode = RHModeSleep;
  }

  return true;
}

void RH_CC1120::setModeRx() {
  if (_mode != RHModeRx) {
    // Radio is configuewd to stay in RX mode

    spiCommand(RH_CC1120_STROBE_34_SRX);
#ifdef RHAL_DEBUG
    if (debug()) _printer->println("[RHAL] Radio in RX mode");
#endif
    _mode = RHModeRx;
  }
}

void RH_CC1120::setModeTx() {
  if (_mode != RHModeTx) {
    spiCommand(RH_CC1120_STROBE_35_STX);
    _mode = RHModeTx;

#ifdef RHAL_DEBUG
    if (debug())
      _printer->println("[RHAL] Mode TX");
#endif
  }
}

uint8_t RH_CC1120::statusRead() { return spiCommand(RH_CC1120_STROBE_3D_SNOP); }

bool RH_CC1120::waitPacketSent() {
  // If we are not currently in transmit mode, there is no packet to wait for
  if (_mode != RHModeTx)
    return false;

#ifdef RHAL_DEBUG
  if (debug())
    _printer->println("[RHAL] Waiting for TXDONE");
#endif

  // _marcState1 is updated via interrupts, but we need to block anyways
  while (_marcStatus1 != RH_CC1120_MARC_STATUS1_TXDONE)
    YIELD;

#ifdef RHAL_DEBUG
  if (debug()) {
    _printer->print("[RHAL] TXDONE received: _marcStatus1 = 0x");
    _printer->println(_marcStatus1, HEX);
  }
#endif

  _marcStatus1 = RH_CC1120_MARC_STATUS1_NOFAIL;
  return true;
}

void RH_CC1120::setPreambleLength(uint16_t bytes) {
  for (uint8_t i = 0; i < sizeof(preambleValues); i++)
    if (preambleValues[i] == bytes)
      setPreambleLength(i);
}

void RH_CC1120::setPreambleLength(PreambleLen preambleLenIndex) {
  if (preambleLenIndex > sizeof(preambleLenValues) || preambleLenIndex < 0)
    return;

  spiWriteRegister(
      RH_CC1120_REG_000D_PREAMBLE_CFG1 & RH_CC1120_NUM_PREAMBLE_MASK,
      preambleLenValues[preambleLenIndex]);
}

bool RH_CC1120::setTxPower(TransmitPower powerIndex) {
  setTxPower((uint32_t)powerIndex);
}

bool RH_CC1120::setTxPower(uint32_t powerIndex) {
  if (powerIndex > sizeof(paPowerValues) || powerIndex < 0)
    return false;

  spiWriteRegister(RH_CC1120_REG_002B_PA_CFG2, paPowerValues[powerIndex]);

  return true;
}

// frequency calculation on the CC1120 is way too complicated: just use SmartRF
// and set registers
bool RH_CC1120::setFrequency(float centre) { return false; }

void RH_CC1120::setDefaultRegisters() {
  // must-set registers (values suggested by SmartRF 2.8.0)
  spiWriteRegister(RH_CC1120_REG_0000_IOCFG3, 0x58);
  spiWriteRegister(RH_CC1120_REG_0001_IOCFG2, 0x54); // connect GPO2 to MCU's interrupt pin
  spiWriteRegister(RH_CC1120_REG_0002_IOCFG1, 0x46);
  spiWriteRegister(RH_CC1120_REG_0008_SYNC_CFG1, 0x0B);
  spiWriteRegister(RH_CC1120_REG_000C_DCFILT_CFG, 0x1C);
  spiWriteRegister(RH_CC1120_REG_0010_IQIC, 0xC6);
  spiWriteRegister(RH_CC1120_REG_0017_AGC_REF, 0x20);
  spiWriteRegister(RH_CC1120_REG_0018_AGC_CS_THR, 0x19);
  spiWriteRegister(RH_CC1120_REG_001C_AGC_CFG1, 0xA9);
  spiWriteRegister(RH_CC1120_REG_001D_AGC_CFG0, 0xCF);
  spiWriteRegister(RH_CC1120_REG_001E_FIFO_CFG, 0x00);
  spiWriteRegister(RH_CC1120_REG_001F_DEV_ADDR, 0xA2);
  spiWriteRegister(RH_CC1120_REG_0021_FS_CFG, 0x14);
  //spiWriteRegister(RH_CC1120_REG_0023_WOR_CFG0, 0x22); // not sure if we want to use WOR/eWOR
  spiWriteRegister(RH_CC1120_REG_0026_PKT_CFG2, 0x00);
  spiWriteRegister(RH_CC1120_REG_0027_PKT_CFG1, 0x05); // check CRC in RX and add CRC in TX, but don't check address
  spiWriteRegister(RH_CC1120_REG_0028_PKT_CFG0, 0x20); // variable packet length
  spiWriteRegister(RH_CC1120_REG_002A_RFEND_CFG0, 0x38); // stay in RX upon receiving a good packet
  spiWriteRegister(RH_CC1120_REG_002B_PA_CFG2, 0x5D);
  spiWriteRegister(RH_CC1120_REG_002D_PA_CFG0, 0x7E);
  spiWriteRegister(RH_CC1120_REG_2F00_IF_MIX_CFG, 0x00);
  spiWriteRegister(RH_CC1120_REG_2F12_FS_DIG1, 0x00);
  spiWriteRegister(RH_CC1120_REG_2F13_FS_DIG0, 0x5F);
  spiWriteRegister(RH_CC1120_REG_2F16_FS_CAL1, 0x40);
  spiWriteRegister(RH_CC1120_REG_2F17_FS_CAL0, 0x0E);
  spiWriteRegister(RH_CC1120_REG_2F18_FS_CHP, 0x29);
  spiWriteRegister(RH_CC1120_REG_2F19_FS_DIVTWO, 0x03);
  spiWriteRegister(RH_CC1120_REG_2F1B_FS_DSM0, 0x33);
  spiWriteRegister(RH_CC1120_REG_2F1D_FS_DVC0, 0x17);
  spiWriteRegister(RH_CC1120_REG_2F1F_FS_PFD, 0x50);
  spiWriteRegister(RH_CC1120_REG_2F20_FS_PRE, 0x6E);
  spiWriteRegister(RH_CC1120_REG_2F21_FS_REG_DIV_CML, 0x14);
  spiWriteRegister(RH_CC1120_REG_2F22_FS_SPARE, 0xAC);
  spiWriteRegister(RH_CC1120_REG_2F23_FS_VCO4, 0x10);
  spiWriteRegister(RH_CC1120_REG_2F25_FS_VCO2, 0x4F);
  spiWriteRegister(RH_CC1120_REG_2F27_FS_VCO0, 0xB4);
  spiWriteRegister(RH_CC1120_REG_2F32_XOSC5, 0x0E);
  spiWriteRegister(RH_CC1120_REG_2F36_XOSC1, 0x03);

  if (_variablePayloadLen) {
    spiWriteRegister(RH_CC1120_REG_0028_PKT_CFG0, 0x20); // variable len
    spiWriteRegister(RH_CC1120_REG_002E_PKT_LEN, 0xFF);  //   max = 256 bytes enforced by the CC1120
  } else {
    spiWriteRegister(RH_CC1120_REG_0028_PKT_CFG0, 0x00); // fixed len
    spiWriteRegister(RH_CC1120_REG_002E_PKT_LEN, 0x00);  //   len = 256 bytes enforced by the CC1120
  }
}

// Sets registers from a canned modem configuration structure
void RH_CC1120::setModemRegisters(const ModemConfig *config) {
  // modem configuration
  spiWriteRegister(RH_CC1120_REG_000A_DEVIATION_M, config->reg_000a);
  spiWriteRegister(RH_CC1120_REG_000B_MODCFG_DEV_E, config->reg_000b);
  spiWriteRegister(RH_CC1120_REG_0011_CHAN_BW, config->reg_0011);
  spiWriteRegister(RH_CC1120_REG_0013_MDMCFG0, config->reg_0013);
  spiWriteRegister(RH_CC1120_REG_0014_SYMBOL_RATE2, config->reg_0014);
  spiWriteRegister(RH_CC1120_REG_0015_SYMBOL_RATE1, config->reg_0015);
  spiWriteRegister(RH_CC1120_REG_0016_SYMBOL_RATE0, config->reg_0016);
  spiWriteRegister(RH_CC1120_REG_2F01_FREQOFF_CFG, config->reg_2f01);
  spiWriteRegister(RH_CC1120_REG_2F0C_FREQ2, config->reg_2f0c);
  spiWriteRegister(RH_CC1120_REG_2F0D_FREQ1, config->reg_2f0d);
  spiWriteRegister(RH_CC1120_REG_2F0E_FREQ0, config->reg_2f0e);
}

// Set one of the canned Modem configs
// Returns true if its a valid choice
bool RH_CC1120::setModemConfig(ModemConfigChoice index) {
  if (index > (signed int)(sizeof(MODEM_CONFIG_TABLE) / sizeof(ModemConfig)))
    return false;

  const RH_CC1120::ModemConfig *p = MODEM_CONFIG_TABLE;
  RH_CC1120::ModemConfig cfg;
  memcpy_P(&cfg, p + index, sizeof(RH_CC1120::ModemConfig));
  setModemRegisters(&cfg);

  return true;
}

void RH_CC1120::setSyncWords(const uint8_t *syncWords, uint8_t len) {
  if (!syncWords || len > 4)
    return; // Up to 4 byte sync words are supported

  spiBurstWriteRegister(RH_CC1120_REG_0004_SYNC3, syncWords, len);
}
