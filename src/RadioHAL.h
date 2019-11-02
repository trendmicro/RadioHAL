// RadioHAL is Copyright (C) 2019 Trend Micro Incorporated
// RadioHead is Copyright (C) 2008 Mike McCauley

/*!
  \mainpage

RadioHAL is a generic radio abstraction library used by the [RFQuack
framework](https://github.com/trendmicro/rfquack).

RadioHAL is based on RadioHead and, as a matter of fact, it retains most of its
code as it's now in a very initial stage. As of now, it's been tested on RF69-
and CC1120-based modules.

The reason of the fork is beacause we'd like to create a library with very few
assumption on the packet structure.  For instance, we're not interested in
addressing, broadcasting, and all the other useful features that are necessary
if you need to run a sensor network.

For RF analysis, these features could be useful, but are not necessary and most
of the times would make payload analysis harder if not impossible. As we needed
a generic radio abstraction for the [RFQuack
framework](https://github.com/trendmicro/RFQuack), I've thought to re-use
RadioHead and fork it under GPLv2.

RadioHAL is not compatible with RadioHead.

# Radio Drivers

The following drivers are provided:

- **RH_RF69:**
Works with Hope-RF RF69B based radio modules, such as the RFM69 module, (as
used on the excellent Moteino and [Moteino-USB boards from
LowPowerLab](http://lowpowerlab.com/moteino/) and compatible chips and modules
such as RFM69W, RFM69HW, RFM69CW, RFM69HCW (Semtech SX1231, SX1231H).  Also
works with [Anarduino MiniWireless -CW and -HW
boards](http://www.anarduino.com/miniwireless/) including the marvellous high
powered MinWireless-HW (with 20dBm output for excellent range). Supports GFSK,
FSK.

- **RH_CC1120:**
Works with Texas Instruments CC1120 transceivers and compatible modules such as
Anaren AIR BoosterPack 430BOOST-CC110L

We welcome contributions of well tested and well documented code to support
other transports.

# Untested Radio Drivers

These radio drivers are part of the original RadioHead library and are
currently being ported to RadioHAL, following the no-packet-structure
principle. They're still untested, so we leave them out of the `src/`
folder on purpose, to avoid confusion.

- **RH_RF22:**
Works with Hope-RF RF22B and RF23B based transceivers, and compatible chips and
modules, including the RFM22B transceiver module such as [this bare
module](http://www.sparkfun.com/products/10153) and [this
shield](http://www.sparkfun.com/products/11018) and [this
board](http://www.anarduino.com/miniwireless) and RF23BP modules [such as
this](http://www.anarduino.com/details.jsp?pid=130). Supports GFSK, FSK and
OOK. Access to other chip features such as on-chip temperature measurement,
analog-digital converter, transmitter power control etc is also provided.

- **RH_RF24:**
Works with Silicon Labs Si4460/4461/4463/4464 family of transceivers chip, and
the equivalent HopeRF RF24/26/27 family of chips and the HopeRF RFM24W/26W/27W
modules.  Supports GFSK, FSK and OOK. Access to other chip features such as
on-chip temperature measurement, analog-digital converter, transmitter power
control etc is also provided.

- **RH_NRF24:**
Works with Nordic nRF24 based 2.4GHz radio modules, such as nRF24L01 and
others.  Also works with Hope-RF RFM73 and compatible devices (such as BK2423).
nRF24L01 and RFM73 can interoperate with each other.

- **RH_NRF905:**
Works with Nordic nRF905 based 433/868/915 MHz radio modules.

- **RH_NRF51:**
Works with Nordic nRF51 compatible 2.4 GHz SoC/devices such as the nRF51822.
Also works with Sparkfun nRF52832 breakout board, with Arduino 1.6.13 and
Sparkfun nRF52 boards manager 0.2.3

- **RH_RF95:**
Works with Semtech SX1276/77/78/79, Modtronix inAir4 and inAir9, and HopeRF
RFM95/96/97/98 and other similar LoRa capable radios.  Supports Long Range
(LoRa) with spread spectrum frequency hopping, large payloads etc.
FSK/GFSK/OOK modes are not (yet) supported.

- **RH_MRF89:**
Works with Microchip MRF89XA and compatible transceivers.  and modules such as
MRF89XAM9A.

- **RH_CC110:**
Works with Texas Instruments CC110L transceivers and compatible modules such as
Anaren AIR BoosterPack 430BOOST-CC110L

- **RH_E32:**
Works with EBYTE E32-TTL-1W serial radio transceivers (and possibly other
    transceivers in the same family).


# Platforms

The original RadioHead has been tested on range of platforms. RadioHAL assumes
that modern and powerful boards are used, which are very convenient nowadays.
So, we don't feel like we should support boards that do not expose enough PINs
to use the hardware SPI (and would force us to support a software SPI).

Given the modularity, openness, and ease of use of the Adafruit Feather system,
we can't hide we like to use RadioHAL on Feather-supported boards.

- Arduino and the Arduino IDE (version 1.0 to 1.8.1 and later)
Including Diecimila, Uno, Mega, Leonardo, Yun, Due, Zero etc.
http://arduino.cc/, Also similar boards such as
 - Moteino http://lowpowerlab.com/moteino/
 - Anarduino Mini http://www.anarduino.com/mini/
 - RedBearLab Blend V1.0 http://redbearlab.com/blend/ (with Arduino 1.0.5 and
RedBearLab Blend Add-On version 20140701)
 -  MoteinoMEGA https://lowpowerlab.com/shop/moteinomega
    (with Arduino 1.0.5 and the MoteinoMEGA Arduino Core
    https://github.com/LowPowerLab/Moteino/tree/master/MEGA/Core)
 - ESP8266 on Arduino IDE and Boards Manager per
https://github.com/esp8266/Arduino Tested using Arduino 1.6.8 with esp8266 by
ESP8266 Community version 2.1.0 Examples serial_reliable_datagram_* and ask_*
are shown to work. CAUTION: The GHz radio included in the ESP8266 is not yet
supported.
 - Various Talk2 Whisper boards eg
https://wisen.com.au/store/products/whisper-node-lora. Use Arduino Board Manager
to install the Talk2 code support.
 - etc.

- STM32 F4 Discover board, using Arduino 1.8.2 or later and
   Roger Clarkes Arduino_STM from
https://github.com/rogerclarkmelbourne/Arduino_STM32 Caution: with this library
and board, sending text to Serial causes the board to hang in mysterious ways.
   Serial2 emits to PA2. The default SPI pins are SCK: PB3, MOSI PB5, MISO PB4.
   We tested with PB0 as slave select and PB1 as interrupt pin for various
radios. RH_ASK and RH_Serial also work.

- ChipKIT Core with Arduino IDE on any ChipKIT Core supported Digilent processor
(tested on Uno32) http://chipkit.net/wiki/index.php?title=ChipKIT_core

- Maple and Flymaple boards with libmaple and the Maple-IDE development
environment http://leaflabs.com/devices/maple/ and
http://www.open-drone.org/flymaple

- Teensy including Teensy 3.1 and earlier built using Arduino IDE 1.0.5 to 1.6.4
and later with teensyduino addon 1.18 to 1.23 and later.
  http://www.pjrc.com/teensy

- Particle Photon https://store.particle.io/collections/photon and ARM3 based
CPU with built-in Wi-Fi transceiver and extensive IoT software suport. RadioHAL
does not support the built-in transceiver but can be used to control other SPI
based radios, Serial ports etc. See below for details on how to build RadioHAL
for Photon

- ATtiny built using Arduino IDE 1.0.5 with the arduino-tiny support from
https://code.google.com/p/arduino-tiny/ and Digispark built with Arduino 1.6.5.
  (Caution: these are very small processors and not all RadioHAL features may be
available, depending on memory requirements)

- nRF51 compatible Arm chips such as nRF51822 with Arduino 1.6.4 and later using
the procedures in http://redbearlab.com/getting-started-nrf51822/

- nRF52 compatible Arm chips such as as Adafruit BLE Feather board
  https://www.adafruit.com/product/3406

- Adafruit Feather. These are excellent boards that are available with a variety
of radios. We tested with the Feather 32u4 with RFM69HCW radio, with Arduino
IDE 1.6.8 and the Adafruit AVR Boards board manager version 1.6.10.
  https://www.adafruit.com/products/3076

- Adafruit Feather M0 boards with Arduino 1.8.1 and later, using the Arduino and
Adafruit SAMD board support.
  https://learn.adafruit.com/adafruit-feather-m0-basic-proto/using-with-arduino-ide

- ESP32 built using Arduino IDE 1.8.1 or later using the ESP32 toolchain
installed per
  https://diyprojects.io/programming-esp32-board-arduino-ide-macos-windows-linux-arm-raspberrypi-orangepi/
  The internal 2.4GHz radio is not yet supported. Tested with RFM22 using SPI
interfcace

- Raspberry Pi
  Uses BCM2835 library for GPIO http://www.airspayce.com/mikem/bcm2835/
  Currently works only with RH_NRF24 driver or other drivers that do not require
interrupt support. Contributed by Mike Poublon.

- Linux and OSX
  Using the RHutil/HardwareSerial class, the RH_Serial driver and any manager
will build and run on Linux and OSX. These can be used to build programs that
talk securely and reliably to Arduino and other processors or to other Linux or
OSX hosts on a reliable, error detected datagram protocol over various types of
serial line.

Other platforms are partially supported, such as Generic AVR 8 bit processors,
MSP430. We welcome contributions that will expand the range of supported
platforms.

# Coding Style

RadioHAL is designed so it can run on small processors with very
limited resources and strict timing contraints.  As a result, we
tend only to use the simplest and least demanding (in terms of memory and CPU)
C++ facilities. In particular we avoid as much as possible dynamic memory
allocation, and the use of complex objects like C++ strings, IO and buffers. We
are happy with this, but we are aware that some people may think we are leaving
useful tools on the table. You should not use this code as an example of how to
do generalised C++ programming on well resourced processors.

# Trademarks

RadioHead is a trademark of AirSpayce Pty Ltd. The RadioHead mark was first used
on April 12 2014 for international trade, and is used only in relation to data
communications hardware and software and related services. It is not to be
confused with any other similar marks covering other goods and services.

# Copyright

RadioHAL is Copyright (C) 2019 Trend Micro Incorporated

RadioHead is Copyright (C) 2008 Mike McCauley under GPLv2 and Commercial
License.

# Open Source Licensing

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA  02110-1301, USA.

This is the appropriate option if you want to share the source code of your
application with everyone you distribute it to, and you also want to give them
the right to share who uses it. If you wish to use this software under Open
Source Licensing, you must contribute all your source code to the open source
community in accordance with the GPL Version 2 when your application is
distributed. See https://www.gnu.org/licenses/gpl-2.0.html

# Revision History

- 0.1 (2018-05-08): Initial public release after forking from RadioHead

*/

#ifndef RadioHAL_h
#define RadioHAL_h

#define RHAL_DEBUG // do (not) compile debugging code
// #define RHAL_SPI_DEBUG  // do (not) compile SPI debugging code
// #define RHAL_FIFO_DEBUG // do (not) compile FIFO debugging code

#if defined(RHAL_DEBUG) || defined(RHAL_SPI_DEBUG) || defined(RHAL_FIFO_DEBUG)
#define RHAL_DEBUGGING
#endif

// Official version numbers are maintained automatically by Makefile:
#define RH_VERSION_MAJOR 1
#define RH_VERSION_MINOR 0

// Symbolic names for currently supported platform types
#define RH_PLATFORM_ARDUINO 1
#define RH_PLATFORM_MSP430 2
#define RH_PLATFORM_STM32 3
#define RH_PLATFORM_GENERIC_AVR8 4
#define RH_PLATFORM_UNO32 5
#define RH_PLATFORM_UNIX 6
#define RH_PLATFORM_STM32STD 7
#define RH_PLATFORM_STM32F4_HAL 8
#define RH_PLATFORM_RASPI 9
#define RH_PLATFORM_NRF51 10
#define RH_PLATFORM_ESP8266 11
#define RH_PLATFORM_STM32F2 12
#define RH_PLATFORM_CHIPKIT_CORE 13
#define RH_PLATFORM_ESP32 14
#define RH_PLATFORM_NRF52 15

////////////////////////////////////////////////////
// Select platform automatically, if possible
#ifndef RH_PLATFORM
#if (MPIDE >= 150 && defined(ARDUINO))
// Using ChipKIT Core on Arduino IDE
#define RH_PLATFORM RH_PLATFORM_CHIPKIT_CORE
#elif defined(MPIDE)
// Uno32 under old MPIDE, which has been discontinued:
#define RH_PLATFORM RH_PLATFORM_UNO32
#elif defined(NRF51)
#define RH_PLATFORM RH_PLATFORM_NRF51
#elif defined(NRF52)
#define RH_PLATFORM RH_PLATFORM_NRF52
#elif defined(ESP8266)
#define RH_PLATFORM RH_PLATFORM_ESP8266
#elif defined(ESP32)
#define RH_PLATFORM RH_PLATFORM_ESP32
#elif defined(ARDUINO)
#define RH_PLATFORM RH_PLATFORM_ARDUINO
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__)
#define RH_PLATFORM RH_PLATFORM_MSP430
#elif defined(MCU_STM32F103RE)
#define RH_PLATFORM RH_PLATFORM_STM32
#elif defined(STM32F2XX)
#define RH_PLATFORM RH_PLATFORM_STM32F2
#elif defined(USE_STDPERIPH_DRIVER)
#define RH_PLATFORM RH_PLATFORM_STM32STD
#elif defined(RASPBERRY_PI)
#define RH_PLATFORM RH_PLATFORM_RASPI
#elif defined(__unix__) // Linux
#define RH_PLATFORM RH_PLATFORM_UNIX
#elif defined(__APPLE__) // OSX
#define RH_PLATFORM RH_PLATFORM_UNIX
#else
#error Platform not defined!
#endif
#endif

#if defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny85__) ||                  \
    defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) ||                  \
    defined(__AVR_ATtiny45__) || defined(__AVR_ATtinyX4__) ||                  \
    defined(__AVR_ATtinyX5__) || defined(__AVR_ATtiny2313__) ||                \
    defined(__AVR_ATtiny4313__) || defined(__AVR_ATtinyX313__)
#define RH_PLATFORM_ATTINY
#endif

////////////////////////////////////////////////////
// Platform specific headers:
#if (RH_PLATFORM == RH_PLATFORM_ARDUINO)
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wiring.h>
#endif
#ifdef RH_PLATFORM_ATTINY
#warning Arduino TinyCore does not support hardware SPI. Use software SPI instead.
#else
#include <SPI.h>
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL
#endif
#if defined(ARDUINO_ARCH_STM32F4)
// output to Serial causes hangs on STM32 F4 Discovery board
// There seems to be no way to output text to the USB connection
#define Serial Serial2
#endif

#elif (RH_PLATFORM == RH_PLATFORM_ESP8266) // ESP8266 processor on Arduino IDE
#include <Arduino.h>
#include <SPI.h>
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL

#elif (RH_PLATFORM == RH_PLATFORM_ESP32) // ESP32 processor on Arduino IDE
#include <Arduino.h>
#include <SPI.h>
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL

#elif (RH_PLATFORM == RH_PLATFORM_MSP430) // LaunchPad specific
#include "Energia.h"
#include "legacymsp430.h"
#include <SPI.h>
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL

#elif (RH_PLATFORM == RH_PLATFORM_UNO32 ||                                     \
       RH_PLATFORM == RH_PLATFORM_CHIPKIT_CORE)
#include <SPI.h>
#include <WProgram.h>
#include <string.h>
#define RH_HAVE_HARDWARE_SPI
#define memcpy_P memcpy
#define RH_HAVE_SERIAL

#elif (RH_PLATFORM == RH_PLATFORM_STM32) // Maple, Flymaple etc
#include <STM32ArduinoCompat/HardwareSPI.h>
#include <STM32ArduinoCompat/wirish.h>
#include <stdint.h>
#include <string.h>
#define RH_HAVE_HARDWARE_SPI
// Defines which timer to use on Maple
#define MAPLE_TIMER 1
#define PROGMEM
#define memcpy_P memcpy
#define Serial SerialUSB
#define RH_HAVE_SERIAL

#elif (RH_PLATFORM ==                                                          \
       RH_PLATFORM_STM32F2) // Particle Photon with firmware-develop
#include <application.h>
#include <math.h> // floor
#include <stm32f2xx.h>
#define RH_HAVE_SERIAL
#define RH_HAVE_HARDWARE_SPI

#elif (RH_PLATFORM ==                                                          \
       RH_PLATFORM_STM32STD) // STM32 with STM32F4xx_StdPeriph_Driver
#include <HardwareSPI.h>
#include <math.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include <string.h>
#include <wirish.h>
#define RH_HAVE_HARDWARE_SPI
#define Serial SerialUSB
#define RH_HAVE_SERIAL

#elif (RH_PLATFORM == RH_PLATFORM_GENERIC_AVR8)
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#define RH_HAVE_HARDWARE_SPI
#include <SPI.h>

// For Steve Childress port to ARM M4 w/CMSIS with STM's Hardware Abstraction
// lib. See ArduinoWorkarounds.h (not supplied)
#elif (RH_PLATFORM == RH_PLATFORM_STM32F4_HAL)
#include <ArduinoWorkarounds.h>
#include <math.h>
#include <stdint.h>
#include <stm32f4xx.h> // Also using ST's CubeMX to generate I/O and CPU setup source code for IAR/EWARM, not GCC ARM.
#include <string.h>
#define RH_HAVE_HARDWARE_SPI // using HAL (Hardware Abstraction Libraries from
                             // ST along with CMSIS, not arduino libs or pins
                             // concept.

#elif (RH_PLATFORM == RH_PLATFORM_RASPI)
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL
#define PROGMEM
#include <RHutil/RasPi.h>
#include <string.h>
// Define SS for CS0 or pin 24
#define SS 8

#elif (RH_PLATFORM == RH_PLATFORM_NRF51)
#define RH_HAVE_SERIAL
#define PROGMEM
#include <Arduino.h>

#elif (RH_PLATFORM == RH_PLATFORM_NRF52)
#include <SPI.h>
#define RH_HAVE_HARDWARE_SPI
#define RH_HAVE_SERIAL
#define PROGMEM
#include <Arduino.h>

#elif (RH_PLATFORM == RH_PLATFORM_UNIX)
// Simulate the sketch on Linux and OSX
#include <RHutil/simulator.h>
#define RH_HAVE_SERIAL
#include <netinet/in.h> // For htons and friends

#else
#error Platform unknown!
#endif

////////////////////////////////////////////////////
// This is an attempt to make a portable atomic block
#if (RH_PLATFORM == RH_PLATFORM_ARDUINO)
#if defined(__arm__)
#include <RHutil/atomic.h>
#else
#include <util/atomic.h>
#endif
#define ATOMIC_BLOCK_START ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#define ATOMIC_BLOCK_END }
#elif (RH_PLATFORM == RH_PLATFORM_CHIPKIT_CORE)
// UsingChipKIT Core on Arduino IDE
#define ATOMIC_BLOCK_START                                                     \
  unsigned int __status = disableInterrupts();                                 \
  {
#define ATOMIC_BLOCK_END                                                       \
  }                                                                            \
  restoreInterrupts(__status);
#elif (RH_PLATFORM == RH_PLATFORM_UNO32)
// Under old MPIDE, which has been discontinued:
#include <peripheral/int.h>
#define ATOMIC_BLOCK_START                                                     \
  unsigned int __status = INTDisableInterrupts();                              \
  {
#define ATOMIC_BLOCK_END                                                       \
  }                                                                            \
  INTRestoreInterrupts(__status);
#elif (RH_PLATFORM ==                                                          \
       RH_PLATFORM_STM32F2) // Particle Photon with firmware-develop
#define ATOMIC_BLOCK_START                                                     \
  {                                                                            \
    int __prev = HAL_disable_irq();
#define ATOMIC_BLOCK_END                                                       \
  HAL_enable_irq(__prev);                                                      \
  }
#elif (RH_PLATFORM == RH_PLATFORM_ESP8266)
// See hardware/esp8266/2.0.0/cores/esp8266/Arduino.h
#define ATOMIC_BLOCK_START                                                     \
  {                                                                            \
    uint32_t __savedPS = xt_rsil(15);
#define ATOMIC_BLOCK_END                                                       \
  xt_wsr_ps(__savedPS);                                                        \
  }
#else
// TO BE DONE:
#define ATOMIC_BLOCK_START
#define ATOMIC_BLOCK_END
#endif

////////////////////////////////////////////////////
// Try to be compatible with systems that support yield() and multitasking
// instead of spin-loops
// Recent Arduino IDE or Teensy 3 has yield()
#if (RH_PLATFORM == RH_PLATFORM_ARDUINO && ARDUINO >= 155 &&                   \
     !defined(RH_PLATFORM_ATTINY)) ||                                          \
    (TEENSYDUINO && defined(__MK20DX128__))
#define YIELD yield();
#elif (RH_PLATFORM == RH_PLATFORM_ESP8266)
// ESP8266 also has it
#define YIELD yield();
#else
#define YIELD
#endif

////////////////////////////////////////////////////
// digitalPinToInterrupt is not available prior to Arduino 1.5.6 and 1.0.6
// See http://arduino.cc/en/Reference/attachInterrupt
#ifndef NOT_AN_INTERRUPT
#define NOT_AN_INTERRUPT -1
#endif
#ifndef digitalPinToInterrupt
#if (RH_PLATFORM == RH_PLATFORM_ARDUINO) && !defined(__arm__)

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// Arduino Mega, Mega ADK, Mega Pro
// 2->0, 3->1, 21->2, 20->3, 19->4, 18->5
#define digitalPinToInterrupt(p)                                               \
  ((p) == 2                                                                    \
       ? 0                                                                     \
       : ((p) == 3 ? 1                                                         \
                   : ((p) >= 18 && (p) <= 21 ? 23 - (p) : NOT_AN_INTERRUPT)))

#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
// Arduino 1284 and 1284P - See Manicbug and Optiboot
// 10->0, 11->1, 2->2
#define digitalPinToInterrupt(p)                                               \
  ((p) == 10 ? 0 : ((p) == 11 ? 1 : ((p) == 2 ? 2 : NOT_AN_INTERRUPT)))

#elif defined(__AVR_ATmega32U4__)
// Leonardo, Yun, Micro, Pro Micro, Flora, Esplora
// 3->0, 2->1, 0->2, 1->3, 7->4
#define digitalPinToInterrupt(p)                                               \
  ((p) == 0                                                                    \
       ? 2                                                                     \
       : ((p) == 1                                                             \
              ? 3                                                              \
              : ((p) == 2                                                      \
                     ? 1                                                       \
                     : ((p) == 3 ? 0 : ((p) == 7 ? 4 : NOT_AN_INTERRUPT)))))

#else
// All other arduino except Due:
// Serial Arduino, Extreme, NG, BT, Uno, Diecimila, Duemilanove, Nano, Menta,
// Pro, Mini 04, Fio, LilyPad, Ethernet etc 2->0, 3->1
#define digitalPinToInterrupt(p)                                               \
  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#endif

#elif (RH_PLATFORM == RH_PLATFORM_UNO32) ||                                    \
    (RH_PLATFORM == RH_PLATFORM_CHIPKIT_CORE)
// Hmmm, this is correct for Uno32, but what about other boards on ChipKIT Core?
#define digitalPinToInterrupt(p)                                               \
  ((p) == 38                                                                   \
       ? 0                                                                     \
       : ((p) == 2                                                             \
              ? 1                                                              \
              : ((p) == 7                                                      \
                     ? 2                                                       \
                     : ((p) == 8 ? 3 : ((p) == 735 ? 4 : NOT_AN_INTERRUPT)))))

#else
// Everything else (including Due and Teensy) interrupt number the same as the
// interrupt pin number
#define digitalPinToInterrupt(p) (p)
#endif
#endif

// On some platforms, attachInterrupt() takes a pin number, not an interrupt
// number
#if (RH_PLATFORM == RH_PLATFORM_ARDUINO) && defined(__arm__) &&                \
    (defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_SAM_DUE))
#define RH_ATTACHINTERRUPT_TAKES_PIN_NUMBER
#endif

// Slave select pin, some platforms such as ATTiny do not define it.
#ifndef SS
#define SS 10
#endif

// These defs cause trouble on some versions of Arduino
#undef abs
#undef round
#undef double

// Sigh: there is no widespread adoption of htons and friends in the base code,
// only in some WiFi headers etc that have a lot of excess baggage
#if RH_PLATFORM != RH_PLATFORM_UNIX && !defined(htons)
// #ifndef htons
// These predefined macros available on modern GCC compilers
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
// Atmel processors
#define htons(x) (((x) << 8) | (((x) >> 8) & 0xFF))
#define ntohs(x) htons(x)
#define htonl(x)                                                               \
  (((x) << 24 & 0xFF000000UL) | ((x) << 8 & 0x00FF0000UL) |                    \
   ((x) >> 8 & 0x0000FF00UL) | ((x) >> 24 & 0x000000FFUL))
#define ntohl(x) htonl(x)

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
// Others
#define htons(x) (x)
#define ntohs(x) (x)
#define htonl(x) (x)
#define ntohl(x) (x)

#else
#error "Dont know how to define htons and friends for this processor"
#endif
#endif

// This is the address that indicates a broadcast
#define RH_BROADCAST_ADDRESS 0xff

/**
 * @brief Defines the supported modulation types
 */
typedef struct {
  bool mod_ASK;
  bool mod_OOK;
  bool mod_2FSK;
  bool mod_4FSK;
  bool mod_2GFSK;
  bool mod_4GFSK;
  bool mod_PSK;
  bool mod_MSK;
  bool mod_GMSK;
} ModulationSchemes;

// Uncomment this is to enable Encryption (see RHEncryptedDriver):
// But ensure you have installed the Crypto directory from arduinolibs first:
// http://rweather.github.io/arduinolibs/index.html
//#define RH_ENABLE_ENCRYPTION_MODULE

typedef void (*printfunction)(Print *);

#endif
