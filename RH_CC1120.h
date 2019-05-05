// RH_CC120.h
//
// Definitions for Texas Instruments CC1120 transceiver.
// http://www.ti.com/lit/ug/swru295e/swru295e.pdf
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

#ifndef RH_CC1120_h
#define RH_CC1120_h

#include <RHNRFSPIDriver.h>

// This is the maximum number of interrupts the driver can support
// Most Arduinos can handle 2, Megas can handle more
#define RH_CC1120_NUM_INTERRUPTS 3

// Max number of octets the FIFO can hold
#define RH_CC1120_FIFO_SIZE 128

// This is the maximum number of bytes that can be carried by the chip
// We use some for headers, keeping fewer for RadioHead messages
#define RH_CC1120_MAX_PAYLOAD_LEN RH_CC1120_FIFO_SIZE

// This is the maximum message length that can be supported by this driver.
// Can be pre-defined to a smaller size (to save SRAM) prior to including this header
#ifndef RH_CC1120_MAX_MESSAGE_LEN
 #define RH_CC1120_MAX_MESSAGE_LEN RH_CC1120_MAX_PAYLOAD_LEN
#endif

// Read access mask
#define RH_CC1120_SPI_WRITE_MASK              0x00
#define RH_CC1120_SPI_READ_MASK               0x80
#define RH_CC1120_SPI_BURST_MASK              0x40

// Register definitions exported from TI SmartRF Studio v7 version 2.8.0
#define RH_CC1120_REG_0000_IOCFG3             0x00     //GPIO3 IO Pin Configuration
#define RH_CC1120_REG_0001_IOCFG2             0x01     //GPIO2 IO Pin Configuration
#define RH_CC1120_REG_0002_IOCFG1             0x02     //GPIO1 IO Pin Configuration
#define RH_CC1120_REG_0003_IOCFG0             0x03     //GPIO0 IO Pin Configuration
#define RH_CC1120_REG_0004_SYNC3              0x04     //Sync Word Configuration [31:24]
#define RH_CC1120_REG_0005_SYNC2              0x05     //Sync Word Configuration [23:16]
#define RH_CC1120_REG_0006_SYNC1              0x06     //Sync Word Configuration [15:8]
#define RH_CC1120_REG_0007_SYNC0              0x07     //Sync Word Configuration [7:0]
#define RH_CC1120_REG_0008_SYNC_CFG1          0x08     //Sync Word Detection Configuration Reg. 1
#define RH_CC1120_REG_0009_SYNC_CFG0          0x09     //Sync Word Length Configuration Reg. 0
#define RH_CC1120_REG_000A_DEVIATION_M        0x0A     //Frequency Deviation Configuration
#define RH_CC1120_REG_000B_MODCFG_DEV_E       0x0B     //Modulation Format and Frequency Deviation Configur..
#define RH_CC1120_REG_000C_DCFILT_CFG         0x0C     //Digital DC Removal Configuration
#define RH_CC1120_REG_000D_PREAMBLE_CFG1      0x0D     //Preamble Length Configuration Reg. 1
#define RH_CC1120_REG_000E_PREAMBLE_CFG0      0x0E     //Preamble Detection Configuration Reg. 0
#define RH_CC1120_REG_000F_FREQ_IF_CFG        0x0F     //RX Mixer Frequency Configuration
#define RH_CC1120_REG_0010_IQIC               0x10     //Digital Image Channel Compensation Configuration
#define RH_CC1120_REG_0011_CHAN_BW            0x11     //Channel Filter Configuration
#define RH_CC1120_REG_0012_MDMCFG1            0x12     //General Modem Parameter Configuration Reg. 1
#define RH_CC1120_REG_0013_MDMCFG0            0x13     //General Modem Parameter Configuration Reg. 0
#define RH_CC1120_REG_0014_SYMBOL_RATE2       0x14     //Symbol Rate Configuration Exponent and Mantissa [1..
#define RH_CC1120_REG_0015_SYMBOL_RATE1       0x15     //Symbol Rate Configuration Mantissa [15:8]
#define RH_CC1120_REG_0016_SYMBOL_RATE0       0x16     //Symbol Rate Configuration Mantissa [7:0]
#define RH_CC1120_REG_0017_AGC_REF            0x17     //AGC Reference Level Configuration
#define RH_CC1120_REG_0018_AGC_CS_THR         0x18     //Carrier Sense Threshold Configuration
#define RH_CC1120_REG_0019_AGC_GAIN_ADJUST    0x19     //RSSI Offset Configuration
#define RH_CC1120_REG_001A_AGC_CFG3           0x1A     //Automatic Gain Control Configuration Reg. 3
#define RH_CC1120_REG_001B_AGC_CFG2           0x1B     //Automatic Gain Control Configuration Reg. 2
#define RH_CC1120_REG_001C_AGC_CFG1           0x1C     //Automatic Gain Control Configuration Reg. 1
#define RH_CC1120_REG_001D_AGC_CFG0           0x1D     //Automatic Gain Control Configuration Reg. 0
#define RH_CC1120_REG_001E_FIFO_CFG           0x1E     //FIFO Configuration
#define RH_CC1120_REG_001F_DEV_ADDR           0x1F     //Device Address Configuration
#define RH_CC1120_REG_0020_SETTLING_CFG       0x20     //Frequency Synthesizer Calibration and Settling Con..
#define RH_CC1120_REG_0021_FS_CFG             0x21     //Frequency Synthesizer Configuration
#define RH_CC1120_REG_0022_WOR_CFG1           0x22     //eWOR Configuration Reg. 1
#define RH_CC1120_REG_0023_WOR_CFG0           0x23     //eWOR Configuration Reg. 0
#define RH_CC1120_REG_0024_WOR_EVENT0_MSB     0x24     //Event 0 Configuration MSB
#define RH_CC1120_REG_0025_WOR_EVENT0_LSB     0x25     //Event 0 Configuration LSB
#define RH_CC1120_REG_0026_PKT_CFG2           0x26     //Packet Configuration Reg. 2
#define RH_CC1120_REG_0027_PKT_CFG1           0x27     //Packet Configuration Reg. 1
#define RH_CC1120_REG_0028_PKT_CFG0           0x28     //Packet Configuration Reg. 0
#define RH_CC1120_REG_0029_RFEND_CFG1         0x29     //RFEND Configuration Reg. 1
#define RH_CC1120_REG_002A_RFEND_CFG0         0x2A     //RFEND Configuration Reg. 0
#define RH_CC1120_REG_002B_PA_CFG2            0x2B     //Power Amplifier Configuration Reg. 2
#define RH_CC1120_REG_002C_PA_CFG1            0x2C     //Power Amplifier Configuration Reg. 1
#define RH_CC1120_REG_002D_PA_CFG0            0x2D     //Power Amplifier Configuration Reg. 0
#define RH_CC1120_REG_002E_PKT_LEN            0x2E     //Packet Length Configuration

// Extended registers
#define RH_CC1120_REG_2F00_IF_MIX_CFG         0x2F00     //IF Mix Configuration
#define RH_CC1120_REG_2F01_FREQOFF_CFG        0x2F01     //Frequency Offset Correction Configuration
#define RH_CC1120_REG_2F02_TOC_CFG            0x2F02     //Timing Offset Correction Configuration
#define RH_CC1120_REG_2F03_MARC_SPARE         0x2F03     //MARC Spare
#define RH_CC1120_REG_2F04_ECG_CFG            0x2F04     //External Clock Frequency Configuration
#define RH_CC1120_REG_2F05_CFM_DATA_CFG       0x2F05     //Custom frequency modulation enable
#define RH_CC1120_REG_2F06_EXT_CTRL           0x2F06     //External Control Configuration
#define RH_CC1120_REG_2F07_RCCAL_FINE         0x2F07     //RC Oscillator Calibration Fine
#define RH_CC1120_REG_2F08_RCCAL_COARSE       0x2F08     //RC Oscillator Calibration Coarse
#define RH_CC1120_REG_2F09_RCCAL_OFFSET       0x2F09     //RC Oscillator Calibration Clock Offset
#define RH_CC1120_REG_2F0A_FREQOFF1           0x2F0A     //Frequency Offset MSB
#define RH_CC1120_REG_2F0B_FREQOFF0           0x2F0B     //Frequency Offset LSB
#define RH_CC1120_REG_2F0C_FREQ2              0x2F0C     //Frequency Configuration [23:16]
#define RH_CC1120_REG_2F0D_FREQ1              0x2F0D     //Frequency Configuration [15:8]
#define RH_CC1120_REG_2F0E_FREQ0              0x2F0E     //Frequency Configuration [7:0]
#define RH_CC1120_REG_2F0F_IF_ADC2            0x2F0F     //Analog to Digital Converter Configuration Reg. 2
#define RH_CC1120_REG_2F10_IF_ADC1            0x2F10     //Analog to Digital Converter Configuration Reg. 1
#define RH_CC1120_REG_2F11_IF_ADC0            0x2F11     //Analog to Digital Converter Configuration Reg. 0
#define RH_CC1120_REG_2F12_FS_DIG1            0x2F12     //Frequency Synthesizer Digital Reg. 1
#define RH_CC1120_REG_2F13_FS_DIG0            0x2F13     //Frequency Synthesizer Digital Reg. 0
#define RH_CC1120_REG_2F14_FS_CAL3            0x2F14     //Frequency Synthesizer Calibration Reg. 3
#define RH_CC1120_REG_2F15_FS_CAL2            0x2F15     //Frequency Synthesizer Calibration Reg. 2
#define RH_CC1120_REG_2F16_FS_CAL1            0x2F16     //Frequency Synthesizer Calibration Reg. 1
#define RH_CC1120_REG_2F17_FS_CAL0            0x2F17     //Frequency Synthesizer Calibration Reg. 0
#define RH_CC1120_REG_2F18_FS_CHP             0x2F18     //Frequency Synthesizer Charge Pump Configuration
#define RH_CC1120_REG_2F19_FS_DIVTWO          0x2F19     //Frequency Synthesizer Divide by 2
#define RH_CC1120_REG_2F1A_FS_DSM1            0x2F1A     //FS Digital Synthesizer Module Configuration Reg. 1
#define RH_CC1120_REG_2F1B_FS_DSM0            0x2F1B     //FS Digital Synthesizer Module Configuration Reg. 0
#define RH_CC1120_REG_2F1C_FS_DVC1            0x2F1C     //Frequency Synthesizer Divider Chain Configuration ..
#define RH_CC1120_REG_2F1D_FS_DVC0            0x2F1D     //Frequency Synthesizer Divider Chain Configuration ..
#define RH_CC1120_REG_2F1E_FS_LBI             0x2F1E     //Frequency Synthesizer Local Bias Configuration
#define RH_CC1120_REG_2F1F_FS_PFD             0x2F1F     //Frequency Synthesizer Phase Frequency Detector Con..
#define RH_CC1120_REG_2F20_FS_PRE             0x2F20     //Frequency Synthesizer Prescaler Configuration
#define RH_CC1120_REG_2F21_FS_REG_DIV_CML     0x2F21     //Frequency Synthesizer Divider Regulator Configurat..
#define RH_CC1120_REG_2F22_FS_SPARE           0x2F22     //Frequency Synthesizer Spare
#define RH_CC1120_REG_2F23_FS_VCO4            0x2F23     //FS Voltage Controlled Oscillator Configuration Reg..
#define RH_CC1120_REG_2F24_FS_VCO3            0x2F24     //FS Voltage Controlled Oscillator Configuration Reg..
#define RH_CC1120_REG_2F25_FS_VCO2            0x2F25     //FS Voltage Controlled Oscillator Configuration Reg..
#define RH_CC1120_REG_2F26_FS_VCO1            0x2F26     //FS Voltage Controlled Oscillator Configuration Reg..
#define RH_CC1120_REG_2F27_FS_VCO0            0x2F27     //FS Voltage Controlled Oscillator Configuration Reg..
#define RH_CC1120_REG_2F28_GBIAS6             0x2F28     //Global Bias Configuration Reg. 6
#define RH_CC1120_REG_2F29_GBIAS5             0x2F29     //Global Bias Configuration Reg. 5
#define RH_CC1120_REG_2F2A_GBIAS4             0x2F2A     //Global Bias Configuration Reg. 4
#define RH_CC1120_REG_2F2B_GBIAS3             0x2F2B     //Global Bias Configuration Reg. 3
#define RH_CC1120_REG_2F2C_GBIAS2             0x2F2C     //Global Bias Configuration Reg. 2
#define RH_CC1120_REG_2F2D_GBIAS1             0x2F2D     //Global Bias Configuration Reg. 1
#define RH_CC1120_REG_2F2E_GBIAS0             0x2F2E     //Global Bias Configuration Reg. 0
#define RH_CC1120_REG_2F2F_IFAMP              0x2F2F     //Intermediate Frequency Amplifier Configuration
#define RH_CC1120_REG_2F30_LNA                0x2F30     //Low Noise Amplifier Configuration
#define RH_CC1120_REG_2F31_RXMIX              0x2F31     //RX Mixer Configuration
#define RH_CC1120_REG_2F32_XOSC5              0x2F32     //Crystal Oscillator Configuration Reg. 5
#define RH_CC1120_REG_2F33_XOSC4              0x2F33     //Crystal Oscillator Configuration Reg. 4
#define RH_CC1120_REG_2F34_XOSC3              0x2F34     //Crystal Oscillator Configuration Reg. 3
#define RH_CC1120_REG_2F35_XOSC2              0x2F35     //Crystal Oscillator Configuration Reg. 2
#define RH_CC1120_REG_2F36_XOSC1              0x2F36     //Crystal Oscillator Configuration Reg. 1
#define RH_CC1120_REG_2F37_XOSC0              0x2F37     //Crystal Oscillator Configuration Reg. 0
#define RH_CC1120_REG_2F38_ANALOG_SPARE       0x2F38     //Analog Spare
#define RH_CC1120_REG_2F39_PA_CFG3            0x2F39     //Power Amplifier Configuration Reg. 3
#define RH_CC1120_REG_2F64_WOR_TIME1          0x2F64     //eWOR Timer Counter Value MSB
#define RH_CC1120_REG_2F65_WOR_TIME0          0x2F65     //eWOR Timer Counter Value LSB
#define RH_CC1120_REG_2F66_WOR_CAPTURE1       0x2F66     //eWOR Timer Capture Value MSB
#define RH_CC1120_REG_2F67_WOR_CAPTURE0       0x2F67     //eWOR Timer Capture Value LSB
#define RH_CC1120_REG_2F68_BIST               0x2F68     //MARC Built-In Self-Test
#define RH_CC1120_REG_2F69_DCFILTOFFSET_I1    0x2F69     //DC Filter Offset I MSB
#define RH_CC1120_REG_2F6A_DCFILTOFFSET_I0    0x2F6A     //DC Filter Offset I LSB
#define RH_CC1120_REG_2F6B_DCFILTOFFSET_Q1    0x2F6B     //DC Filter Offset Q MSB
#define RH_CC1120_REG_2F6C_DCFILTOFFSET_Q0    0x2F6C     //DC Filter Offset Q LSB
#define RH_CC1120_REG_2F6D_IQIE_I1            0x2F6D     //IQ Imbalance Value I MSB
#define RH_CC1120_REG_2F6E_IQIE_I0            0x2F6E     //IQ Imbalance Value I LSB
#define RH_CC1120_REG_2F6F_IQIE_Q1            0x2F6F     //IQ Imbalance Value Q MSB
#define RH_CC1120_REG_2F70_IQIE_Q0            0x2F70     //IQ Imbalance Value Q LSB
#define RH_CC1120_REG_2F71_RSSI1              0x2F71     //Received Signal Strength Indicator Reg. 1
#define RH_CC1120_REG_2F72_RSSI0              0x2F72     //Received Signal Strength Indicator Reg.0
#define RH_CC1120_REG_2F73_MARCSTATE          0x2F73     //MARC State
#define RH_CC1120_REG_2F74_LQI_VAL            0x2F74     //Link Quality Indicator Value
#define RH_CC1120_REG_2F75_PQT_SYNC_ERR       0x2F75     //Preamble and Sync Word Error
#define RH_CC1120_REG_2F76_DEM_STATUS         0x2F76     //Demodulator Status
#define RH_CC1120_REG_2F77_FREQOFF_EST1       0x2F77     //Frequency Offset Estimate MSB
#define RH_CC1120_REG_2F78_FREQOFF_EST0       0x2F78     //Frequency Offset Estimate LSB
#define RH_CC1120_REG_2F79_AGC_GAIN3          0x2F79     //Automatic Gain Control Reg. 3
#define RH_CC1120_REG_2F7A_AGC_GAIN2          0x2F7A     //Automatic Gain Control Reg. 2
#define RH_CC1120_REG_2F7B_AGC_GAIN1          0x2F7B     //Automatic Gain Control Reg. 1
#define RH_CC1120_REG_2F7C_AGC_GAIN0          0x2F7C     //Automatic Gain Control Reg. 0
#define RH_CC1120_REG_2F7D_CFM_RX_DATA_OUT    0x2F7D     //Custom Frequency Modulation RX Data
#define RH_CC1120_REG_2F7E_CFM_TX_DATA_IN     0x2F7E     //Custom Frequency Modulation TX Data
#define RH_CC1120_REG_2F7F_ASK_SOFT_RX_DATA   0x2F7F     //ASK Soft Decision Output
#define RH_CC1120_REG_2F80_RNDGEN             0x2F80     //Random Number Generator Value
#define RH_CC1120_REG_2F81_MAGN2              0x2F81     //Signal Magnitude after CORDIC [16]
#define RH_CC1120_REG_2F82_MAGN1              0x2F82     //Signal Magnitude after CORDIC [15:8]
#define RH_CC1120_REG_2F83_MAGN0              0x2F83     //Signal Magnitude after CORDIC [7:0]
#define RH_CC1120_REG_2F84_ANG1               0x2F84     //Signal Angular after CORDIC [9:8]
#define RH_CC1120_REG_2F85_ANG0               0x2F85     //Signal Angular after CORDIC [7:0]
#define RH_CC1120_REG_2F86_CHFILT_I2          0x2F86     //Channel Filter Data Real Part [18:16]
#define RH_CC1120_REG_2F87_CHFILT_I1          0x2F87     //Channel Filter Data Real Part [15:8]
#define RH_CC1120_REG_2F88_CHFILT_I0          0x2F88     //Channel Filter Data Real Part [7:0]
#define RH_CC1120_REG_2F89_CHFILT_Q2          0x2F89     //Channel Filter Data Imaginary Part [18:16]
#define RH_CC1120_REG_2F8A_CHFILT_Q1          0x2F8A     //Channel Filter Data Imaginary Part [15:8]
#define RH_CC1120_REG_2F8B_CHFILT_Q0          0x2F8B     //Channel Filter Data Imaginary Part [7:0]
#define RH_CC1120_REG_2F8C_GPIO_STATUS        0x2F8C     //General Purpose Input/Output Status
#define RH_CC1120_REG_2F8D_FSCAL_CTRL         0x2F8D     //Frequency Synthesizer Calibration Control
#define RH_CC1120_REG_2F8E_PHASE_ADJUST       0x2F8E     //Frequency Synthesizer Phase Adjust
#define RH_CC1120_REG_2F8F_PARTNUMBER         0x2F8F     //Part Number
#define RH_CC1120_REG_2F90_PARTVERSION        0x2F90     //Part Revision
#define RH_CC1120_REG_2F91_SERIAL_STATUS      0x2F91     //Serial Status
#define RH_CC1120_REG_2F92_MODEM_STATUS1      0x2F92     //Modem Status Reg. 1
#define RH_CC1120_REG_2F93_MODEM_STATUS0      0x2F93     //Modem Status Reg. 0
#define RH_CC1120_REG_2F94_MARC_STATUS1       0x2F94     //MARC Status Reg. 1
#define RH_CC1120_REG_2F95_MARC_STATUS0       0x2F95     //MARC Status Reg. 0
#define RH_CC1120_REG_2F96_PA_IFAMP_TEST      0x2F96     //Power Amplifier Intermediate Frequency Amplifier T..
#define RH_CC1120_REG_2F97_FSRF_TEST          0x2F97     //Frequency Synthesizer Test
#define RH_CC1120_REG_2F98_PRE_TEST           0x2F98     //Frequency Synthesizer Prescaler Test
#define RH_CC1120_REG_2F99_PRE_OVR            0x2F99     //Frequency Synthesizer Prescaler Override
#define RH_CC1120_REG_2F9A_ADC_TEST           0x2F9A     //Analog to Digital Converter Test
#define RH_CC1120_REG_2F9B_DVC_TEST           0x2F9B     //Digital Divider Chain Test
#define RH_CC1120_REG_2F9C_ATEST              0x2F9C     //Analog Test
#define RH_CC1120_REG_2F9D_ATEST_LVDS         0x2F9D     //Analog Test LVDS
#define RH_CC1120_REG_2F9E_ATEST_MODE         0x2F9E     //Analog Test Mode
#define RH_CC1120_REG_2F9F_XOSC_TEST1         0x2F9F     //Crystal Oscillator Test Reg. 1
#define RH_CC1120_REG_2FA0_XOSC_TEST0         0x2FA0     //Crystal Oscillator Test Reg. 0

// Status registers
#define RH_CC1120_STATUS_CHIP_RDY_MASK        0x80 // select leftmost bit (7) -> 0b10000000
#define RH_CC1120_STATUS_STATE_MASK           0x70 // select bits 6:4 ->         0b01110000

// Preamble mask
#define RH_CC1120_NUM_PREAMBLE_MASK           0x3c // select bits 5:2 ->         0b00111100

// Status byte
#define RH_CC1120_STATUS_IDLE                 0x00
#define RH_CC1120_STATUS_RX                   0x10
#define RH_CC1120_STATUS_TX                   0x20
#define RH_CC1120_STATUS_FSTXON               0x30
#define RH_CC1120_STATUS_CALIBRATE            0x40
#define RH_CC1120_STATUS_SETTLING             0x50
#define RH_CC1120_STATUS_RXFIFO_OVERFLOW      0x60
#define RH_CC1120_STATUS_TXFIFO_UNDERFLOW     0x70
#define RH_CC1120_STATUS_FIFOBYTES_AVAILABLE  0x0f

// MARC_STATUS1
#define RH_CC1120_MARC_STATUS1_NOFAIL         0x00
#define RH_CC1120_MARC_STATUS1_TX_TOUT        0x01
#define RH_CC1120_MARC_STATUS1_RX_TERM        0x02
#define RH_CC1120_MARC_STATUS1_EWOR_SLOST     0x03
#define RH_CC1120_MARC_STATUS1_PKT_TOO_LONG   0x04
#define RH_CC1120_MARC_STATUS1_PKT_WROADDR    0x05
#define RH_CC1120_MARC_STATUS1_PKT_WROCRC     0x06
#define RH_CC1120_MARC_STATUS1_TXFIFO_OF      0x07
#define RH_CC1120_MARC_STATUS1_TXFIFO_UF      0x08
#define RH_CC1120_MARC_STATUS1_RXFIFO_OF      0x09
#define RH_CC1120_MARC_STATUS1_RXFIFO_UF      0x0A
#define RH_CC1120_MARC_STATUS1_TXON_CCA_FAIL  0x0B
#define RH_CC1120_MARC_STATUS1_TXDONE         0x40
#define RH_CC1120_MARC_STATUS1_RXDONE         0x80

// MARCSTATE
#define RH_CC1120_MARC_STATE_MASK             0x1f // select bits 4:0 ->         0b00011111
#define RH_CC1120_MARC_2PIN_STATE_MASK        0x60 // select bits 6:5 ->         0b01100000

// MARCSTATE.MARC_STATE
#define RH_CC1120_MARC_STATE_IDLE             0x01
#define RH_CC1120_MARC_STATE_FSTXON           0x12

// MARCSTATE.MARC_2PIN_STATE
#define RH_CC1120_MARC_STATE_TX               0x13
#define RH_CC1120_MARC_2PIN_STATE_SETTLING    0x00
#define RH_CC1120_MARC_2PIN_STATE_TX          0x20
#define RH_CC1120_MARC_2PIN_STATE_IDLE        0x40
#define RH_CC1120_MARC_2PIN_STATE_RX          0x60

// TX/RX FIFO registers
// 0x00FF
#define RH_CC1120_REG_003F_FIFO               0x3F       //FIFO Pointer
#define RH_CC1120_REG_2FD2_RXFIRST            0x2FD2     //RX FIFO Pointer First Entry
#define RH_CC1120_REG_2FD3_TXFIRST            0x2FD3     //TX FIFO Pointer First Entry
#define RH_CC1120_REG_2FD4_RXLAST             0x2FD4     //RX FIFO Pointer Last Entry
#define RH_CC1120_REG_2FD5_TXLAST             0x2FD5     //TX FIFO Pointer Last Entry
#define RH_CC1120_REG_2FD6_NUM_TXBYTES        0x2FD6     //TX FIFO Status
#define RH_CC1120_REG_2FD7_NUM_RXBYTES        0x2FD7     //RX FIFO Status
#define RH_CC1120_REG_2FD8_FIFO_NUM_TXBYTES   0x2FD8     //TX FIFO Status
#define RH_CC1120_REG_2FD9_FIFO_NUM_RXBYTES   0x2FD9     //RX FIFO Status

// Command strobes
#define RH_CC1120_STROBE_30_SRES              0x30      // Reset chip. 
#define RH_CC1120_STROBE_31_SFSTXON           0x31      // Enable and calibrate frequency synthesizer. 
#define RH_CC1120_STROBE_32_SXOFF             0x32      // Turn off crystal oscillator. 
#define RH_CC1120_STROBE_33_SCAL              0x33      // Calibrate frequency synthesizer and turn it off. 
#define RH_CC1120_STROBE_34_SRX               0x34      // Enable RX. Perform calibration if enabled. 
#define RH_CC1120_STROBE_35_STX               0x35      // Enable TX. If in RX state, only enable TX if CCA passes. 
#define RH_CC1120_STROBE_36_SIDLE             0x36      // Exit RX / TX, turn off frequency synthesizer. 
#define RH_CC1120_STROBE_38_SWOR              0x38      // Start automatic RX polling sequence (Wake-on-Radio) 
#define RH_CC1120_STROBE_39_SPWD              0x39      // Enter power down mode when CSn goes high. 
#define RH_CC1120_STROBE_3A_SFRX              0x3A      // Flush the RX FIFO buffer. 
#define RH_CC1120_STROBE_3B_SFTX              0x3B      // Flush the TX FIFO buffer. 
#define RH_CC1120_STROBE_3C_SWORRST           0x3C      // Reset real time clock. 
#define RH_CC1120_STROBE_3D_SNOP              0x3D      // No operation. Returns status byte. 

// Not a command strobe
#define RH_CC1120_REG_0037_AFC                0x37      // Automatic Frequency Correction 

// Chip states returned in status byte
#define RH_CC1120_STATE_IDLE                  0x00
#define RH_CC1120_STATE_RX                    0x10
#define RH_CC1120_STATE_TX                    0x20
#define RH_CC1120_STATE_FSTXON                0x30
#define RH_CC1120_STATE_CALIBRATE             0x40
#define RH_CC1120_STATE_SETTLING              0x50
#define RH_CC1120_STATE_RXFIFO_ERROR          0x60
#define RH_CC1120_STATE_TXFIFO_ERROR          0x70

/////////////////////////////////////////////////////////////////////
/// \class RH_CC1120 RH_CC1120.h <RH_CC1120.h>
/// \brief Send and receive unaddressed, unreliable, datagrams by Texas
/// Instruments CC1120 and compatible transceivers and modules.
///
/// The CC1120 device is a fully integrated single-chip radio transceiver
/// designed for high performance at very low-power and low-voltage operation in
/// cost-effective wireless systems. All filters are integrated, thus removing
/// the need for costly external SAW and IF filters. The device is mainly
/// intended for Industrial, Scientific, and Medical (ISM) applications and Short
/// Range Device (SRD) frequency bands at 164 to 192 MHz, 274 to 320 MHz, 410 to
/// 480 MHz, and 820 to 960 MHz.
///
/// The CC1120 device provides extensive hardware support for packet handling,
/// data buffering, burst transmissions, clear channel assessment, link quality
/// indication, and wake-on-radio. The main operating parameters of the CC1120
/// device can be controlled through an SPI interface. In a typical system, the
/// CC1120 device is used with a microcontroller and only a few external passive
/// components.
///
/// This base class provides basic functions for sending and receiving
/// unaddressed, unreliable datagrams / of arbitrary length to 63 octets per
/// packet at a selected data rate and modulation type. / Use one of the Manager
/// classes to get addressing and acknowledgement reliability, routing, meshes
/// etc.
///
/// Naturally, for any 2 radios to communicate that must be configured to use
/// the same frequency and / data rate, and with identical sync words.
///
/// Several CC1120 modules can be connected to an Arduino, permitting the
/// construction of translators / and frequency changers, etc.
///
/// Several GFSK modulation schemes are provided and may be selected by calling
/// setModemConfig(). No FSK or OOK / modulation schemes are provided though the
/// implementor may configure the modem characteristics directly / by calling
/// setModemRegisters().
///
/// Implementation based on:
/// https://github.com/HydroSense/HydroSense_cc1120
/// \par Crystal Frequency
///
/// \par Packet Format
///
/// The "standard" packet format is documented at page 45 of
/// http://www.ti.com/lit/ug/swru295e/swru295e.pdf
///
/// In summary, it consists of:
///
/// - A programmable number of preamble bytes (usually 4)
/// - An 11, 16, 18, 24 or 32 bit synchronization word
/// - 1 octet message length (optional, only used in variable length mode)
/// - 1 octet device address (optional, enforced by the CC1120 if set)
/// - up to 126 octets of payload (128 if no lenght and address are used)
/// - A 2 byte CRC checksum computed over the data field (checked in RX)
///
/// Optionally, two status bytes (see Table 23 and Table 24) with RSSI value,
/// Link Quality Indication, and CRC status can be appended in the RX FIFO by
/// setting PKT_CFG1.APPEND_STATUS = 1.
///
/// \par Connecting CC1120 to Arduino
/// 
/// Warning: the CC1120 is a 3.3V part, and exposing it to 5V on any pin will
/// damage it.
///
/// \par Radio operating strategy and defaults
///
/// The radio is enabled at all times and switched between RX, TX and IDLE
/// modes. / When RX is enabled (by calling available() or setModeRx()) the radio
/// will stay in RX mode until a / valid CRC correct message addressed to thiis
/// node is received, when it will transition to IDLE. / When TX is enabled (by
/// calling send()) it will stay in TX mode until the message has ben sent / and
/// waitPacketSent() is called when it wil transition to IDLE /(this radio has no
/// 'packet sent' interrupt that could be used, so polling / with
/// waitPacketSent() is required
///
/// The modulation schemes supported include the GFSK schemes provided by
/// default in the TI SmartRF Suite. / This software allows you to get the
/// correct register values for diferent modulation schemes. All the modulation /
/// schemes prvided in the driver are based on the recommended register values
/// given by SmartRF. / Other schemes such a 2-FSK, 4-FSK and OOK are suported by
/// the chip, but canned configurations are not provided with this driver. / The
/// implementer may choose to create their own modem configurations and pass them
/// to setModemRegisters().
///
class RH_CC1120 : public RHNRFSPIDriver
{
public:

    /// \brief Defines register configuration values for a desired modulation
    ///
    /// Defines values for various configuration fields and registers to 
    /// achieve a desired modulation speed and frequency deviation.
  typedef struct
  {
    uint8_t reg_000a; ///< RH_CC1120_REG_000A_DEVIATION_M
    uint8_t reg_000b; ///< RH_CC1120_REG_000B_MODCFG_DEV_E
    uint8_t reg_0011; ///< RH_CC1120_REG_0011_CHAN_BW
    uint8_t reg_0013; ///< RH_CC1120_REG_0013_MDMCFG0
    uint8_t reg_0014; ///< RH_CC1120_REG_0014_SYMBOL_RATE2
    uint8_t reg_0015; ///< RH_CC1120_REG_0015_SYMBOL_RATE1
    uint8_t reg_0016; ///< RH_CC1120_REG_0016_SYMBOL_RATE0
    uint8_t reg_2f01; ///< RH_CC1120_REG_2F01_FREQOFF_CFG
    uint8_t reg_2f0c; ///< RH_CC1120_REG_2F0C_FREQ2
    uint8_t reg_2f0d; ///< RH_CC1120_REG_2F0D_FREQ1
    uint8_t reg_2f0e; ///< RH_CC1120_REG_2F0E_FREQ0
  } ModemConfig;

    /// Choices for setModemConfig() for a selected subset of common modulation types,
    /// and data rates. If you need another configuration, use the register calculator.
    /// and call setModemRegisters() with your desired settings.
    /// These are indexes into MODEM_CONFIG_TABLE. We strongly recommend you use these symbolic
    /// definitions and not their integer equivalents: its possible that new values will be
    /// introduced in later versions (though we will try to avoid it).
  typedef enum
  {
    f868MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff = 0,
    f868MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff,
    f169MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff,
    f868MHz_ASK_OOKd17_9Bw66_6Dr4_8_12_5dBm_WhitOff_ManchOff,
    f950MHz_4_GFSKd82_7Bw200_0Dr100_15dBm_WhitOff_ManchOff,
    f434MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff,
    f950MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff,
    f434MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff,
    f950MHz_2_GFSKd24_9Bw100_0Dr50_15dBm_WhitOff_ManchOff,
    f434MHz_2_FSKd3_9Bw25_0Dr1_2_15dBm_WhitOff_ManchOff,
    f950MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff,
    f868MHz_4_GFSKd82_7Bw200_0Dr100_15dBm_WhitOff_ManchOff,
    f434MHz_2_GFSKd24_9Bw100_0Dr50_15dBm_WhitOff_ManchOff,
    f950MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff,
    f868MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff,
    f169MHz_2_FSKd20_0Bw50_0Dr1_2_15dBm_WhitOff_ManchOff,
    f868MHz_2_GFSKd20_0Bw100_0Dr38_4_15dBm_WhitOff_ManchOff,
    f169MHz_2_FSKd3_9Bw10_0Dr1_2_15dBm_WhitOff_ManchOff,
    f868MHz_2_GFSKd24_9Bw100_0Dr50_15dBm_WhitOff_ManchOff
  } ModemConfigChoice;

    /// Caution: these enum values are indexes into PaPowerValues. 
    /// Do not change one without changing the other. Use the symbolic names, not the integer values
    typedef enum
    {
	    TransmitPowerM11dBm = 0,     ///< -11dBm
	    TransmitPowerM6dBm,          ///<  -6dBm
	    TransmitPowerM3dBm,          ///<  -3dBm
	    TransmitPower0dBm,           ///<   0dBm
	    TransmitPower1dBm,           ///<   1dBm
	    TransmitPower2dBm,           ///<   2dBm
	    TransmitPower3dBm,           ///<   3dBm
	    TransmitPower4dBm,           ///<   4dBm
	    TransmitPower5dBm,           ///<   5dBm
	    TransmitPower6dBm,           ///<   6dBm
	    TransmitPower7dBm,           ///<   7dBm
	    TransmitPower8dBm,           ///<   8dBm
	    TransmitPower9dBm,           ///<   9dBm
	    TransmitPower10dBm,          ///<  10dBm
	    TransmitPower11dBm,          ///<  11dBm
	    TransmitPower12dBm,          ///<  12dBm
	    TransmitPower13dBm,          ///<  13dBm
	    TransmitPower14dBm,          ///<  14dBm
	    TransmitPower15dBm,          ///<  15dBm
    } TransmitPower;

    typedef enum
    {
      PreambleLen0 = 0,
      PreambleLen1,
      PreambleLen2,
      PreambleLen3,
      PreambleLen4,
      PreambleLen5,
      PreambleLen6,
      PreambleLen7,
      PreambleLen8,
      PreambleLen12,
      PreambleLen24,
      PreambleLen30
    } PreambleLen;

    /// Constructor. You can have multiple instances, but each instance must have its own
    /// interrupt and slave select pin. After constructing, you must call init() to initialise the interface
    /// and the radio module. A maximum of 3 instances can co-exist on one processor, provided there are sufficient
    /// distinct interrupt lines, one for each instance.
    /// \param[in] slaveSelectPin the Arduino pin number of the output to use to select the CC1120 before
    /// accessing it. Defaults to the normal SS pin for your Arduino (D10 for Diecimila, Uno etc, D53 for Mega, D10 for Maple)
    /// \param[in] resetPin The reset Pin number that is connected to the CC1120 RST line.
    /// Defaults to pin 4.
    /// \param[in] interruptPin The interrupt Pin number that is connected to the CC1120 GDO0 interrupt line. 
    /// Defaults to pin 2.
    /// Caution: You must specify an interrupt capable pin.
    /// On many Arduino boards, there are limitations as to which pins may be used as interrupts.
    /// On Leonardo pins 0, 1, 2 or 3. On Mega2560 pins 2, 3, 18, 19, 20, 21. On Due and Teensy, any digital pin.
    /// On other Arduinos pins 2 or 3. 
    /// See http://arduino.cc/en/Reference/attachInterrupt for more details.
    /// On Chipkit Uno32, pins 38, 2, 7, 8, 35.
    /// On other boards, any digital pin may be used.
    /// \param[in] spi Pointer to the SPI interface object to use. 
    ///                Defaults to the standard Arduino hardware SPI interface
    RH_CC1120(uint8_t slaveSelectPin = SS, uint8_t resetPin = 4, uint8_t interruptPin = 2, RHGenericSPI& spi = hardware_spi);

    /// Initialise the Driver transport hardware and software.
    /// Make sure the Driver is properly configured before calling init().
    /// \return true if initialisation succeeded.
    virtual bool init();

    /// Prints the value of all chip registers
    /// to the Serial device if RH_HAVE_SERIAL is defined for the current platform
    /// For debugging purposes only.
    /// \return true on success
    bool printRegisters();

    /// Prints debugging information about the internal CC1120 state
    void printRadioState();

    /// Blocks until the current message (if any) 
    /// has been transmitted
    /// \return true on success, false if the chip is not in transmit mode or other transmit failure
    virtual bool waitPacketSent();

    /// Tests whether a new message is available
    /// from the Driver. 
    /// On most drivers, this will also put the Driver into RHModeRx mode until
    /// a message is actually received by the transport, when it will be returned to RHModeIdle
    /// and available() will return true.
    /// This can be called multiple times in a timeout loop
    /// \return true if a new, complete, error-free uncollected message is available to be retreived by recv()
    virtual bool available();

    /// Turns the receiver on if it not already on (after wiaint gor any currenly transmitting message to complete).
    /// If there is a valid message available, copy it to buf and return true
    /// else return false.
    /// If a message is copied, *len is set to the length (Caution, 0 length messages are permitted).
    /// You should be sure to call this function frequently enough to not miss any messages
    /// It is recommended that you call it in your main loop.
    /// \param[in] buf Location to copy the received message
    /// \param[in,out] len Pointer to available space in buf. Set to the actual number of octets copied.
    /// \return true if a valid message was copied to buf. The message cannot be retreived again.
    virtual bool recv(uint8_t* buf, uint8_t* len);

    /// Waits until any previous transmit packet is finished being transmitted with waitPacketSent().
    /// Then loads a message into the transmitter and starts the transmitter. Note that a message length
    /// of 0 is permitted. 
    /// \param[in] data Array of data to be sent
    /// \param[in] len Number of bytes of data to send
    /// \return true if the message length was valid and it was correctly queued for transmit
    virtual bool send(const uint8_t* data, uint8_t len);

    /// Returns the maximum message length 
    /// available in this Driver.
    /// \return The maximum legal message length
    virtual uint8_t maxMessageLength();

    /// If current mode is Sleep, Rx or Tx changes it to Idle. If the transmitter or receiver is running, 
    /// disables them.
    void setModeIdle();

    /// If current mode is Tx or Idle, changes it to Rx. 
    /// Starts the receiver. The radio will stay in Rx mode until a CRC correct message addressed to this node
    /// is received, or the ode is changed to Tx, Idle or Sleep.
    void setModeRx();

    /// If current mode is Rx or Idle, changes it to Tx.
    /// Starts the transmitter sending the current message.
    void setModeTx();

    /// Sets the radio into low-power sleep mode.
    /// If successful, the transport will stay in sleep mode until woken by 
    /// changing mode to idle, transmit or receive (eg by calling send(), recv(), available() etc)
    /// Caution: there is a time penalty as the radio takes a finite time to wake from sleep mode.
    /// Caution: waking up from sleep loses values from registers 0x29 through 0x2e
    /// \return true if sleep mode was successfully entered.
    virtual bool sleep();

    /// Set the Power Amplifier power setting.
    /// Caution: be a good neighbour and use the lowest power setting compatible with your application.
    /// Caution: Permissable power settings for your area may depend on frequency and modulation characteristics: 
    /// consult local authorities.
    /// param[in] power One of TransmitPower enum values as an unsigned integer
    bool setTxPower(uint32_t power);

    /// Set the Power Amplifier power setting.
    /// Caution: be a good neighbour and use the lowest power setting compatible with your application.
    /// Caution: Permissable power settings for your area may depend on frequency and modulation characteristics: 
    /// consult local authorities.
    /// param[in] power One of TransmitPower enum values 
    bool setTxPower(TransmitPower powerIndex);

    /// Sets the length of the preamble
    /// in bytes. Default is 4.
    /// Sets the message preamble length in PREAMBLE_CFG1.NUM_PREAMBLE
    /// \param[in] bytes Preamble length in bytes.
    void setPreambleLength(uint16_t bytes);

    /// Sets the length of the preamble
    /// in PreambleLen. Default is PreambleLen4
    /// Sets the message preamble length in PREAMBLE_CFG1.NUM_PREAMBLE
    /// \param[in] preambleLenIndex in PreambleLen
    void setPreambleLength(PreambleLen preambleLenIndex);

    /// Sets the transmitter and receiver centre frequency.
    /// Caution: permissable frequency bands will depend on you country and area: consult local authorities.
    /// \param[in] centre Frequency in MHz. 300.0 to 928.0
    /// \return true if the selected frquency centre is within range
    bool setFrequency(float centre);

    /// Sets all the registers required to configure the data modem in the CC1120, including the data rate, 
    /// bandwidths etc. You cas use this to configure the modem with custom configuraitons if none of the 
    /// canned configurations in ModemConfigChoice suit you.
    /// \param[in] config A ModemConfig structure containing values for the modem configuration registers.
    void setModemRegisters(const ModemConfig* config);

    /// Select one of the predefined modem configurations. If you need a modem configuration not provided 
    /// here, use setModemRegisters() with your own ModemConfig.
    /// \param[in] index The configuration choice.
    /// \return true if index is a valid choice.
    bool setModemConfig(ModemConfigChoice index);

    /// Sets the sync words for transmit and receive in registers RH_CC1120_REG_04_SYNC*
    /// Caution: SyncWords should be set to the same
    /// value on all nodes in your network. Nodes with different SyncWords set will never receive
    /// each others messages, so different SyncWords can be used to isolate different
    /// networks from each other. Default is { 0xde, 0x51, 0x0b, 0x93 }.
    /// \param[in] syncWords Array of sync words, up to 4 octets long
    /// \param[in] len Number of sync words to set. Up to 4.
    void setSyncWords(const uint8_t* syncWords, uint8_t len);

    /// Return the integer value of the device type
    /// as read from the device in from RH_CC1120_REG_2F8F_PARTNUMBER
    // Expect 0x48 (CC1120) 
    /// \return The 16bits integer device type
    uint16_t deviceType() {return _deviceType;};

    /// Reads a single value from the memory
    /// \param[in] addr Address
    /// \return The value at address
    uint8_t spiRead(uint16_t addr) { return spiReadRegister(addr); }

    /// Writes to a single value into memory
    /// \param[in] addr Address
    /// \param[in] val The value to write
    /// \return the chip status byte
    uint8_t spiWrite(uint16_t addr, uint8_t val) { return spiWriteRegister(addr, val); }

    /// Check if the payload length is OK
    bool checkPayloadLen(uint8_t len);

protected:
    /// This is a low level function to handle the interrupts for one instance of RH_RF95.
    /// Called automatically by isr*()
    /// Should not need to be called by user code.
    void handleInterrupt();

    /// Reads a single register from the CC1120
    /// \param[in] reg Register number, one of RH_CC1120_REG
    /// \return The value of the register
    uint8_t spiReadRegister(uint16_t reg);

    /// Reads a single register in burst mode.
    /// On the CC1120, some registers yield different data when read in burst mode
    /// as opposed to single byte mode.
    /// \param[in] reg Register number, one of RH_CC1120_REG (burst mode readable)
    /// \param[in] dst Pointer to buffer to where the register content will be written
    /// \param[in] len Number of octects to write off the register from the pointer on
    /// \return the chip status byte
    uint8_t spiBurstReadRegister(uint16_t reg, uint8_t *dst, uint8_t len);

    /// Writes to a single register on the CC1120
    /// \param[in] reg Register number, one of RH_CC1120_REG_*
    /// \param[in] val The value to write
    /// \return the chip status byte
    uint8_t spiWriteRegister(uint16_t reg, uint8_t val);

    /// Write a number of bytes to a burst capable register
    /// \param[in] reg Register number of the first register, one of RH_CC1120_REG_*
    /// \param[in] src Array of new register values to write. Must be at least len bytes
    /// \param[in] len Number of bytes to write
    /// \return the chip status byte
    uint8_t spiBurstWriteRegister(uint16_t reg, const uint8_t* src, uint8_t len);

    /// Examine the receive buffer to determine whether the message is for this node
    /// Sets _rxBufValid.
    void validateRxBuf();

    /// Clear our local receive buffer
    void clearRxBuf();

    /// Reads and returns the status byte by issuing the SNOP strobe
    /// \return The value of the status byte per Table 2 (page 9)
    uint8_t statusRead();


private:
    /// Low level interrupt service routine for device connected to interrupt 0
    static void isr0();

    /// Low level interrupt service routine for device connected to interrupt 1
    static void isr1();

    /// Low level interrupt service routine for device connected to interrupt 1
    static void isr2();

    /// HAL methods to access the registers in a generic way
    void spiGenericRegAccess(uint8_t addr, uint8_t *data, uint16_t len);
    uint8_t shortRegAccess(uint8_t accessType, uint8_t addrByte, uint8_t *data, uint16_t len);
    uint8_t longRegAccess(uint8_t accessType, uint8_t extAddr, uint8_t regAddr, uint8_t *data, uint8_t len);
    uint8_t spiReadRegisterWrapper(uint16_t reg, uint8_t *data, uint8_t len);
    uint8_t spiWriteRegisterWrapper(uint16_t reg, const uint8_t *data, uint8_t len);

    /// Various RX packet handling functions used internally
    void updateRssi();
    void printBuffer(const char* prompt, const uint8_t* buf, uint8_t len);

    /// Set default (non-modem-related) registers
    void setDefaultRegisters();

    /// Reset RX FIFO pointers
    void resetRxFifoPointers();

    /// Reset TX FIFO pointers
    void resetTxFifoPointers();

    /// Poll and block until MARCSTATE.MARC_STATE equals state
    void waitForMarcState(uint8_t state);

    /// Array of instances connected to interrupts 0 and 1
    static RH_CC1120* _deviceForInterrupt[];

    /// Index of next interrupt number to use in _deviceForInterrupt
    static uint8_t _interruptCount;

    /// MARC_STATUS1
    uint8_t _marcStatus1;

    /// The configured interrupt pin connected to this instance
    uint8_t _interruptPin;

    /// The reset pin
    uint8_t _resetPin;

    /// The reported device type (PARTNUMBER and PARTVERSION)
    uint16_t _deviceType;

    /// The index into _deviceForInterrupt[] for this device (if an interrupt is already allocated)
    /// else 0xff
    uint8_t _myInterruptIndex;

    /// Number of octets in the buffer
    volatile uint8_t _bufLen;

    /// The receiver/transmitter buffer
    uint8_t _buf[RH_CC1120_MAX_PAYLOAD_LEN];

    /// True when there is a valid message in the buffer
    volatile bool _rxBufValid;
};
#endif
