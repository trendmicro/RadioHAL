// RHGenericDriver.h
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2014 Mike McCauley
// $Id: RHGenericDriver.h,v 1.22 2017/10/03 06:04:59 mikem Exp $

#ifndef RHGenericDriver_h
#define RHGenericDriver_h

#include <RadioHAL.h>

// Defines bits of the FLAGS header reserved for use by the RadioHead library
// and the flags available for use by applications
#define RH_FLAGS_RESERVED 0xf0
#define RH_FLAGS_APPLICATION_SPECIFIC 0x0f
#define RH_FLAGS_NONE 0

// Default timeout for waitCAD() in ms
#define RH_CAD_DEFAULT_TIMEOUT 10000

/////////////////////////////////////////////////////////////////////
/// \class RHGenericDriver RHGenericDriver.h <RHGenericDriver.h>
/// \brief Abstract base class for a RadioHead driver.
///
/// This class defines the functions that must be provided by any RadioHead
/// driver. Different types of driver will implement all the abstract functions,
/// and will perhaps override other functions in this subclass, or perhaps add
/// new functions specifically required by that driver. Do not directly
/// instantiate this class: it is only to be subclassed by driver classes.
///
/// Subclasses are expected to implement a half-duplex, unreliable, error
/// checked, unaddressed packet transport. They are expected to carry a message
/// payload with an appropriate maximum length for the transport hardware and to
/// also carry unaltered 4 message headers: TO, FROM, ID, FLAGS
///
/// \par Headers
///
/// Each message sent and received by a RadioHead driver includes 4 headers:
/// -TO The node address that the message is being sent to (broadcast
/// RH_BROADCAST_ADDRESS (255) is permitted) -FROM The node address of the
/// sending node -ID A message ID, distinct (over short time scales) for each
/// message sent by a particilar node -FLAGS A bitmask of flags. The most
/// significant 4 bits are reserved for use by RadioHead. The least significant
/// 4 bits are reserved for applications.
class RHGenericDriver {
public:
  /// \brief Defines different operating modes for the transport hardware
  ///
  /// These are the different values that can be adopted by the _mode variable
  /// and returned by the mode() member function,
  typedef enum {
    RHModeInitialising = 0, ///< Transport is initialising. Initial default
                            ///< value until init() is called..
    RHModeSleep, ///< Transport hardware is in low power sleep mode (if
                 ///< supported)
    RHModeIdle,  ///< Transport is idle.
    RHModeTx,    ///< Transport is in the process of transmitting a message.
    RHModeRx,    ///< Transport is in the process of receiving a message.
    RHModeCad ///< Transport is in the process of detecting channel activity (if
              ///< supported)
  } RHMode;

  /// Constructor
  RHGenericDriver();

  /// Initialise the Driver transport hardware and software.
  /// Make sure the Driver is properly configured before calling init().
  /// \return true if initialisation succeeded.
  virtual bool init();

  /// Tests whether a new message is available
  /// from the Driver.
  /// On most drivers, if there is an uncollected received message, and there is
  /// no message currently bing transmitted, this will also put the Driver into
  /// RHModeRx mode until a message is actually received by the transport, when
  /// it will be returned to RHModeIdle. This can be called multiple times in a
  /// timeout loop. \return true if a new, complete, error-free uncollected
  /// message is available to be retreived by recv().
  virtual bool available() = 0;

  /// Turns the receiver on if it not already on.
  /// If there is a valid message available, copy it to buf and return true
  /// else return false.
  /// If a message is copied, *len is set to the length (Caution, 0 length
  /// messages are permitted). You should be sure to call this function
  /// frequently enough to not miss any messages It is recommended that you call
  /// it in your main loop. \param[in] buf Location to copy the received message
  /// \param[in,out] len Pointer to available space in buf. Set to the actual
  /// number of octets copied. \return true if a valid message was copied to buf
  virtual bool recv(uint8_t *buf, uint8_t *len) = 0;

  /// Waits until any previous transmit packet is finished being transmitted
  /// with waitPacketSent(). Then optionally waits for Channel Activity
  /// Detection (CAD) to show the channnel is clear (if the radio supports CAD)
  /// by calling waitCAD(). Then loads a message into the transmitter and starts
  /// the transmitter. Note that a message length of 0 is NOT permitted. If the
  /// message is too long for the underlying radio technology, send() will
  /// return false and will not send the message.
  /// \param[in] data Array of data to be sent
  /// \param[in] len Number of bytes of data to send (> 0)
  /// specify the maximum time in ms to wait. If 0 (the default) do not wait for
  /// CAD before transmitting. \return true if the message length was valid and
  /// it was correctly queued for transmit. Return false if CAD was requested
  /// and the CAD timeout timed out before clear channel was detected.
  virtual bool send(const uint8_t *data, uint8_t len) = 0;

  /// Returns the maximum message length
  /// available in this Driver.
  /// \return The maximum legal message length
  virtual uint8_t maxMessageLength() = 0;

  /// Starts the receiver and blocks until a valid received
  /// message is available.
  virtual void waitAvailable();

  /// Blocks until the transmitter
  /// is no longer transmitting.
  virtual bool waitPacketSent();

  /// Blocks until the transmitter is no longer transmitting.
  /// or until the timeout occuers, whichever happens first
  /// \param[in] timeout Maximum time to wait in milliseconds.
  /// \return true if the radio completed transmission within the timeout
  /// period. False if it timed out.
  virtual bool waitPacketSent(uint16_t timeout);

  /// Starts the receiver and blocks until a received message is available or a
  /// timeout \param[in] timeout Maximum time to wait in milliseconds. \return
  /// true if a message is available
  virtual bool waitAvailableTimeout(uint16_t timeout);

  // Bent G Christensen (bentor@gmail.com), 08/15/2016
  /// Channel Activity Detection (CAD).
  /// Blocks until channel activity is finished or CAD timeout occurs.
  /// Uses the radio's CAD function (if supported) to detect channel activity.
  /// Implements random delays of 100 to 1000ms while activity is detected and
  /// until timeout. Caution: the random() function is not seeded. If you want
  /// non-deterministic behaviour, consider using something like
  /// randomSeed(analogRead(A0)); in your sketch. Permits the implementation of
  /// listen-before-talk mechanism (Collision Avoidance). Calls the
  /// isChannelActive() member function for the radio (if supported) to
  /// determine if the channel is active. If the radio does not support
  /// isChannelActive(), always returns true immediately \return true if the
  /// radio-specific CAD (as returned by isChannelActive()) shows the channel is
  /// clear within the timeout period (or the timeout period is 0), else returns
  /// false.
  virtual bool waitCAD();

  /// Sets the Channel Activity Detection timeout in milliseconds to be used by
  /// waitCAD(). The default is 0, which means do not wait for CAD detection.
  /// CAD detection depends on support for isChannelActive() by your particular
  /// radio.
  void setCADTimeout(unsigned long cad_timeout);

  /// Determine if the currently selected radio channel is active.
  /// This is expected to be subclassed by specific radios to implement their
  /// Channel Activity Detection if supported. If the radio does not support
  /// CAD, returns true immediately. If a RadioHead radio supports
  /// isChannelActive() it will be documented in the radio specific
  /// documentation. This is called automatically by waitCAD(). \return true if
  /// the radio-specific CAD (as returned by override of isChannelActive())
  /// shows the current radio channel as active, else false. If there is no
  /// radio-specific CAD, returns false.
  virtual bool isChannelActive();

  /// Tells the receiver to accept anything past the preamble (no radio-side
  /// filtering). Will automatically set the sync words to null and disable
  /// any packet-filtering features that may be active on the radio,
  /// including CRC, if available.
  /// \param[in] promiscuous true if you wish to receive packets with any
  /// content
  virtual void setPromiscuous(bool promiscuous);

  /// Returns the most recent RSSI (Receiver Signal Strength Indicator).
  /// Usually it is the RSSI of the last received message, which is measured
  /// when the preamble is received. If you called readRssi() more recently, it
  /// will return that more recent value. \return The most recent RSSI
  /// measurement in dBm.
  virtual int16_t lastRssi();

  /// Returns the operating mode of the library.
  /// \return the current mode, one of RF69_MODE_*
  virtual RHMode mode();

  /// Sets the operating mode of the transport.
  virtual void setMode(RHMode mode);

  /// Sets the transport hardware into low-power sleep mode
  /// (if supported). May be overridden by specific drivers to initialte sleep
  /// mode. If successful, the transport will stay in sleep mode until woken by
  /// changing mode it idle, transmit or receive (eg by calling send(), recv(),
  /// available() etc) \return true if sleep mode is supported by transport
  /// hardware and the RadioHead driver, and if sleep mode
  ///         was successfully entered. If sleep mode is not suported, return
  ///         false.
  virtual bool sleep();

  /// Prints a data buffer in HEX.
  /// For diagnostic use
  /// \param[in] prompt string to preface the print
  /// \param[in] buf Location of the buffer to print
  /// \param[in] len Length of the buffer in octets.
  void printBuffer(const char *prompt, const uint8_t *buf, uint8_t len);

  /// Returns the count of the number of bad received packets (ie packets with
  /// bad lengths, checksum etc) which were rejected and not delivered to the
  /// application. Caution: not all drivers can correctly report this count.
  /// Some underlying hardware only report good packets. \return The number of
  /// bad packets received.
  virtual uint16_t rxBad();

  /// Returns the count of the number of
  /// good received packets
  /// \return The number of good packets received.
  virtual uint16_t rxGood();

  /// Returns the count of the number of
  /// packets successfully transmitted (though not necessarily received by the
  /// destination) \return The number of packets successfully transmitted
  virtual uint16_t txGood();

  /// Sets the printer for debug and logging
  void setPrinter(Stream *printer);

  /// Enables or disables debug logging
  void setDebug(bool enable);

  /// Tells whether debugging is enabled and a printer is set
  bool debug();

  /// Check if the payload length is OK
  bool checkPayloadLen(uint8_t len) { return len < 32; }

  /// Set the packet format (variable or fixed length mode) and (max) length
  void setPacketFormat(bool fixed, uint8_t len);

  /// Set the fixed payload len (ignored when _variablePayloadLen = true). When
  /// called with a `fixedLength > 0`, it automatically switches to fixed payload
  /// length mode, that is, it will set `_variablePayloadLen` to `true`.
  /// \param[in] len The fixed payload length
  void setFixedPayloadLen(uint8_t len);

  /// When in variable payload length mode, set the number of octects to use to
  /// encode the length of the payload. Normally, this is set to 1.
  /// \param[in] size Number of octects that encode the payload length
  void setSizeOfPayloadLen(uint8_t size) { _sizeOfPayloadLen = size; }

protected:
  /// The current transport operating mode
  volatile RHMode _mode;

  /// Variable payload len mode
  bool _variablePayloadLen;

  /// Fixed payload len (ignored when _variablePayloadLen = true)
  bool _fixedPayloadLen;

  /// Size (in bytes) of the payload len on the packet
  uint8_t _sizeOfPayloadLen;

  /// Whether the transport is in promiscuous mode
  bool _promiscuous;

  /// Supported modulation schemes
  ModulationSchemes _supportedModulationSchemes;

  /// The value of the last received RSSI value, in some transport specific
  /// units
  volatile int16_t _lastRssi;

  /// Count of the number of bad messages (eg bad checksum etc) received
  volatile uint16_t _rxBad;

  /// Count of the number of successfully transmitted messaged
  volatile uint16_t _rxGood;

  /// Count of the number of bad messages (correct checksum etc) received
  volatile uint16_t _txGood;

  /// Channel activity detected
  volatile bool _cad;

  /// Channel activity timeout in ms
  unsigned int _cad_timeout;

  /// Debug status
  bool _debugEnabled;

  /// Printer for log messages
  Stream *_printer;

  /// Prints timestamp (used for logging and debugging purposes)
  void _printTimestamp();

  /// Print list of supported modulation schemes
  void printSupportedModulationSchemes();

private:
};

#endif
