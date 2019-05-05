# Address Config = No address check 
# Bit Rate = 1.2 
# Carrier Frequency = 950.000000 
# Deviation = 3.997803 
# Device Address = 0 
# Manchester Enable = false 
# Modulation Format = 2-FSK 
# PA Ramping = true 
# Packet Bit Length = 0 
# Packet Length = 255 
# Packet Length Mode = Variable 
# Performance Mode = High Performance 
# RX Filter BW = 10.000000 
# Symbol rate = 1.2 
# TX Power = 15 
# Whitening = false 

registers = {
  'RH_CC1120_REG_0000_IOCFG3':           0xB0,
  'RH_CC1120_REG_0001_IOCFG2':           0x06,
  'RH_CC1120_REG_0002_IOCFG1':           0xB0,
  'RH_CC1120_REG_0003_IOCFG0':           0x40,
  'RH_CC1120_REG_0004_SYNC3':            0x93,
  'RH_CC1120_REG_0005_SYNC2':            0x0B,
  'RH_CC1120_REG_0006_SYNC1':            0x51,
  'RH_CC1120_REG_0007_SYNC0':            0xDE,
  'RH_CC1120_REG_0008_SYNC_CFG1':        0x0B,
  'RH_CC1120_REG_0009_SYNC_CFG0':        0x17,
  'RH_CC1120_REG_000A_DEVIATION_M':      0x06,
  'RH_CC1120_REG_000B_MODCFG_DEV_E':     0x03,
  'RH_CC1120_REG_000C_DCFILT_CFG':       0x1C,
  'RH_CC1120_REG_000D_PREAMBLE_CFG1':    0x14,
  'RH_CC1120_REG_000E_PREAMBLE_CFG0':    0x2A,
  'RH_CC1120_REG_000F_FREQ_IF_CFG':      0x40,
  'RH_CC1120_REG_0010_IQIC':             0xC6,
  'RH_CC1120_REG_0011_CHAN_BW':          0x14,
  'RH_CC1120_REG_0012_MDMCFG1':          0x46,
  'RH_CC1120_REG_0013_MDMCFG0':          0x05,
  'RH_CC1120_REG_0014_SYMBOL_RATE2':     0x43,
  'RH_CC1120_REG_0015_SYMBOL_RATE1':     0xA9,
  'RH_CC1120_REG_0016_SYMBOL_RATE0':     0x2A,
  'RH_CC1120_REG_0017_AGC_REF':          0x20,
  'RH_CC1120_REG_0018_AGC_CS_THR':       0x19,
  'RH_CC1120_REG_0019_AGC_GAIN_ADJUST':  0x00,
  'RH_CC1120_REG_001A_AGC_CFG3':         0x91,
  'RH_CC1120_REG_001B_AGC_CFG2':         0x20,
  'RH_CC1120_REG_001C_AGC_CFG1':         0xA9,
  'RH_CC1120_REG_001D_AGC_CFG0':         0xCF,
  'RH_CC1120_REG_001E_FIFO_CFG':         0x00,
  'RH_CC1120_REG_001F_DEV_ADDR':         0x00,
  'RH_CC1120_REG_0020_SETTLING_CFG':     0x0B,
  'RH_CC1120_REG_0021_FS_CFG':           0x12,
  'RH_CC1120_REG_0022_WOR_CFG1':         0x08,
  'RH_CC1120_REG_0023_WOR_CFG0':         0x21,
  'RH_CC1120_REG_0024_WOR_EVENT0_MSB':   0x00,
  'RH_CC1120_REG_0025_WOR_EVENT0_LSB':   0x00,
  'RH_CC1120_REG_0026_PKT_CFG2':         0x04,
  'RH_CC1120_REG_0027_PKT_CFG1':         0x05,
  'RH_CC1120_REG_0028_PKT_CFG0':         0x20,
  'RH_CC1120_REG_0029_RFEND_CFG1':       0x0F,
  'RH_CC1120_REG_002A_RFEND_CFG0':       0x00,
  'RH_CC1120_REG_002B_PA_CFG2':          0x7F,
  'RH_CC1120_REG_002C_PA_CFG1':          0x56,
  'RH_CC1120_REG_002D_PA_CFG0':          0x7C,
  'RH_CC1120_REG_002E_PKT_LEN':          0xFF,
  'RH_CC1120_REG_2F00_IF_MIX_CFG':       0x00,
  'RH_CC1120_REG_2F01_FREQOFF_CFG':      0x22,
  'RH_CC1120_REG_2F02_TOC_CFG':          0x0B,
  'RH_CC1120_REG_2F03_MARC_SPARE':       0x00,
  'RH_CC1120_REG_2F04_ECG_CFG':          0x00,
  'RH_CC1120_REG_2F05_CFM_DATA_CFG':     0x00,
  'RH_CC1120_REG_2F06_EXT_CTRL':         0x01,
  'RH_CC1120_REG_2F07_RCCAL_FINE':       0x00,
  'RH_CC1120_REG_2F08_RCCAL_COARSE':     0x00,
  'RH_CC1120_REG_2F09_RCCAL_OFFSET':     0x00,
  'RH_CC1120_REG_2F0A_FREQOFF1':         0x00,
  'RH_CC1120_REG_2F0B_FREQOFF0':         0x00,
  'RH_CC1120_REG_2F0C_FREQ2':            0x76,
  'RH_CC1120_REG_2F0D_FREQ1':            0xC0,
  'RH_CC1120_REG_2F0E_FREQ0':            0x00,
  'RH_CC1120_REG_2F0F_IF_ADC2':          0x02,
  'RH_CC1120_REG_2F10_IF_ADC1':          0xA6,
  'RH_CC1120_REG_2F11_IF_ADC0':          0x04,
  'RH_CC1120_REG_2F12_FS_DIG1':          0x00,
  'RH_CC1120_REG_2F13_FS_DIG0':          0x5F,
  'RH_CC1120_REG_2F14_FS_CAL3':          0x00,
  'RH_CC1120_REG_2F15_FS_CAL2':          0x20,
  'RH_CC1120_REG_2F16_FS_CAL1':          0x40,
  'RH_CC1120_REG_2F17_FS_CAL0':          0x0E,
  'RH_CC1120_REG_2F18_FS_CHP':           0x28,
  'RH_CC1120_REG_2F19_FS_DIVTWO':        0x03,
  'RH_CC1120_REG_2F1A_FS_DSM1':          0x00,
  'RH_CC1120_REG_2F1B_FS_DSM0':          0x33,
  'RH_CC1120_REG_2F1C_FS_DVC1':          0xFF,
  'RH_CC1120_REG_2F1D_FS_DVC0':          0x17,
  'RH_CC1120_REG_2F1E_FS_LBI':           0x00,
  'RH_CC1120_REG_2F1F_FS_PFD':           0x50,
  'RH_CC1120_REG_2F20_FS_PRE':           0x6E,
  'RH_CC1120_REG_2F21_FS_REG_DIV_CML':   0x14,
  'RH_CC1120_REG_2F22_FS_SPARE':         0xAC,
  'RH_CC1120_REG_2F23_FS_VCO4':          0x14,
  'RH_CC1120_REG_2F24_FS_VCO3':          0x00,
  'RH_CC1120_REG_2F25_FS_VCO2':          0x00,
  'RH_CC1120_REG_2F26_FS_VCO1':          0x00,
  'RH_CC1120_REG_2F27_FS_VCO0':          0xB4,
  'RH_CC1120_REG_2F28_GBIAS6':           0x00,
  'RH_CC1120_REG_2F29_GBIAS5':           0x02,
  'RH_CC1120_REG_2F2A_GBIAS4':           0x00,
  'RH_CC1120_REG_2F2B_GBIAS3':           0x00,
  'RH_CC1120_REG_2F2C_GBIAS2':           0x10,
  'RH_CC1120_REG_2F2D_GBIAS1':           0x00,
  'RH_CC1120_REG_2F2E_GBIAS0':           0x00,
  'RH_CC1120_REG_2F2F_IFAMP':            0x01,
  'RH_CC1120_REG_2F30_LNA':              0x01,
  'RH_CC1120_REG_2F31_RXMIX':            0x01,
  'RH_CC1120_REG_2F32_XOSC5':            0x0E,
  'RH_CC1120_REG_2F33_XOSC4':            0xA0,
  'RH_CC1120_REG_2F34_XOSC3':            0x03,
  'RH_CC1120_REG_2F35_XOSC2':            0x04,
  'RH_CC1120_REG_2F36_XOSC1':            0x03,
  'RH_CC1120_REG_2F37_XOSC0':            0x00,
  'RH_CC1120_REG_2F38_ANALOG_SPARE':     0x00,
  'RH_CC1120_REG_2F39_PA_CFG3':          0x00,
  'RH_CC1120_REG_2F64_WOR_TIME1':        0x00,
  'RH_CC1120_REG_2F65_WOR_TIME0':        0x00,
  'RH_CC1120_REG_2F66_WOR_CAPTURE1':     0x00,
  'RH_CC1120_REG_2F67_WOR_CAPTURE0':     0x00,
  'RH_CC1120_REG_2F68_BIST':             0x00,
  'RH_CC1120_REG_2F69_DCFILTOFFSET_I1':  0x00,
  'RH_CC1120_REG_2F6A_DCFILTOFFSET_I0':  0x00,
  'RH_CC1120_REG_2F6B_DCFILTOFFSET_Q1':  0x00,
  'RH_CC1120_REG_2F6C_DCFILTOFFSET_Q0':  0x00,
  'RH_CC1120_REG_2F6D_IQIE_I1':          0x00,
  'RH_CC1120_REG_2F6E_IQIE_I0':          0x00,
  'RH_CC1120_REG_2F6F_IQIE_Q1':          0x00,
  'RH_CC1120_REG_2F70_IQIE_Q0':          0x00,
  'RH_CC1120_REG_2F71_RSSI1':            0x80,
  'RH_CC1120_REG_2F72_RSSI0':            0x00,
  'RH_CC1120_REG_2F73_MARCSTATE':        0x41,
  'RH_CC1120_REG_2F74_LQI_VAL':          0x00,
  'RH_CC1120_REG_2F75_PQT_SYNC_ERR':     0xFF,
  'RH_CC1120_REG_2F76_DEM_STATUS':       0x00,
  'RH_CC1120_REG_2F77_FREQOFF_EST1':     0x00,
  'RH_CC1120_REG_2F78_FREQOFF_EST0':     0x00,
  'RH_CC1120_REG_2F79_AGC_GAIN3':        0x00,
  'RH_CC1120_REG_2F7A_AGC_GAIN2':        0xD1,
  'RH_CC1120_REG_2F7B_AGC_GAIN1':        0x00,
  'RH_CC1120_REG_2F7C_AGC_GAIN0':        0x3F,
  'RH_CC1120_REG_2F7D_CFM_RX_DATA_OUT':  0x00,
  'RH_CC1120_REG_2F7E_CFM_TX_DATA_IN':   0x00,
  'RH_CC1120_REG_2F7F_ASK_SOFT_RX_DATA': 0x30,
  'RH_CC1120_REG_2F80_RNDGEN':           0x7F,
  'RH_CC1120_REG_2F81_MAGN2':            0x00,
  'RH_CC1120_REG_2F82_MAGN1':            0x00,
  'RH_CC1120_REG_2F83_MAGN0':            0x00,
  'RH_CC1120_REG_2F84_ANG1':             0x00,
  'RH_CC1120_REG_2F85_ANG0':             0x00,
  'RH_CC1120_REG_2F86_CHFILT_I2':        0x08,
  'RH_CC1120_REG_2F87_CHFILT_I1':        0x00,
  'RH_CC1120_REG_2F88_CHFILT_I0':        0x00,
  'RH_CC1120_REG_2F89_CHFILT_Q2':        0x00,
  'RH_CC1120_REG_2F8A_CHFILT_Q1':        0x00,
  'RH_CC1120_REG_2F8B_CHFILT_Q0':        0x00,
  'RH_CC1120_REG_2F8C_GPIO_STATUS':      0x00,
  'RH_CC1120_REG_2F8D_FSCAL_CTRL':       0x01,
  'RH_CC1120_REG_2F8E_PHASE_ADJUST':     0x00,
  'RH_CC1120_REG_2F8F_PARTNUMBER':       0x00,
  'RH_CC1120_REG_2F90_PARTVERSION':      0x00,
  'RH_CC1120_REG_2F91_SERIAL_STATUS':    0x00,
  'RH_CC1120_REG_2F92_MODEM_STATUS1':    0x01,
  'RH_CC1120_REG_2F93_MODEM_STATUS0':    0x00,
  'RH_CC1120_REG_2F94_MARC_STATUS1':     0x00,
  'RH_CC1120_REG_2F95_MARC_STATUS0':     0x00,
  'RH_CC1120_REG_2F96_PA_IFAMP_TEST':    0x00,
  'RH_CC1120_REG_2F97_FSRF_TEST':        0x00,
  'RH_CC1120_REG_2F98_PRE_TEST':         0x00,
  'RH_CC1120_REG_2F99_PRE_OVR':          0x00,
  'RH_CC1120_REG_2F9A_ADC_TEST':         0x00,
  'RH_CC1120_REG_2F9B_DVC_TEST':         0x0B,
  'RH_CC1120_REG_2F9C_ATEST':            0x40,
  'RH_CC1120_REG_2F9D_ATEST_LVDS':       0x00,
  'RH_CC1120_REG_2F9E_ATEST_MODE':       0x00,
  'RH_CC1120_REG_2F9F_XOSC_TEST1':       0x3C,
  'RH_CC1120_REG_2FA0_XOSC_TEST0':       0x00,
  'RH_CC1120_REG_2FD2_RXFIRST':          0x00,
  'RH_CC1120_REG_2FD3_TXFIRST':          0x00,
  'RH_CC1120_REG_2FD4_RXLAST':           0x00,
  'RH_CC1120_REG_2FD5_TXLAST':           0x00,
  'RH_CC1120_REG_2FD6_NUM_TXBYTES':      0x00,
  'RH_CC1120_REG_2FD7_NUM_RXBYTES':      0x00,
  'RH_CC1120_REG_2FD8_FIFO_NUM_TXBYTES': 0x0F,
  'RH_CC1120_REG_2FD9_FIFO_NUM_RXBYTES': 0x00,
}