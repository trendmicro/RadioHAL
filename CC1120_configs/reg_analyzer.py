#!/usr/bin/env python3

import sys
import glob

<<<<<<< HEAD
register_values = {
  'RH_CC1120_REG_0000_IOCFG3':         0x58,
  'RH_CC1120_REG_0001_IOCFG2':         0x54,
  'RH_CC1120_REG_0002_IOCFG1':         0x46,
  'RH_CC1120_REG_0008_SYNC_CFG1':      0x0B,
  'RH_CC1120_REG_000A_DEVIATION_M':    0x3A,
  'RH_CC1120_REG_000B_MODCFG_DEV_E':   0x22,
  'RH_CC1120_REG_000C_DCFILT_CFG':     0x1C,
  'RH_CC1120_REG_0010_IQIC':           0xC6,
  'RH_CC1120_REG_0011_CHAN_BW':        0x11,
  'RH_CC1120_REG_0013_MDMCFG0':        0x05,
  'RH_CC1120_REG_0014_SYMBOL_RATE2':   0x67,
  'RH_CC1120_REG_0015_SYMBOL_RATE1':   0x97,
  'RH_CC1120_REG_0016_SYMBOL_RATE0':   0xCC,
  'RH_CC1120_REG_0017_AGC_REF':        0x20,
  'RH_CC1120_REG_0018_AGC_CS_THR':     0x19,
  'RH_CC1120_REG_001C_AGC_CFG1':       0xA9,
  'RH_CC1120_REG_001D_AGC_CFG0':       0xCF,
  'RH_CC1120_REG_001E_FIFO_CFG':       0x00,
  'RH_CC1120_REG_001F_DEV_ADDR':       0xA2,
  'RH_CC1120_REG_0021_FS_CFG':         0x14,
  'RH_CC1120_REG_0023_WOR_CFG0':       0x22,
  'RH_CC1120_REG_0026_PKT_CFG2':       0x00,
  'RH_CC1120_REG_0027_PKT_CFG1':       0x15,
  'RH_CC1120_REG_0028_PKT_CFG0':       0x20,
  'RH_CC1120_REG_002A_RFEND_CFG0':     0x08,
  'RH_CC1120_REG_002B_PA_CFG2':        0x5D,
  'RH_CC1120_REG_002D_PA_CFG0':        0x7E,
  'RH_CC1120_REG_2F00_IF_MIX_CFG':     0x00,
  'RH_CC1120_REG_2F01_FREQOFF_CFG':    0x22,
  'RH_CC1120_REG_2F0C_FREQ2':          0x6C,
  'RH_CC1120_REG_2F0D_FREQ1':          0x8B,
  'RH_CC1120_REG_2F0E_FREQ0':          0x5C,
  'RH_CC1120_REG_2F12_FS_DIG1':        0x00,
  'RH_CC1120_REG_2F13_FS_DIG0':        0x5F,
  'RH_CC1120_REG_2F16_FS_CAL1':        0x40,
  'RH_CC1120_REG_2F17_FS_CAL0':        0x0E,
  'RH_CC1120_REG_2F18_FS_CHP':         0x29,
  'RH_CC1120_REG_2F19_FS_DIVTWO':      0x03,
  'RH_CC1120_REG_2F1B_FS_DSM0':        0x33,
  'RH_CC1120_REG_2F1D_FS_DVC0':        0x17,
  'RH_CC1120_REG_2F1F_FS_PFD':         0x50,
  'RH_CC1120_REG_2F20_FS_PRE':         0x6E,
  'RH_CC1120_REG_2F21_FS_REG_DIV_CML': 0x14,
  'RH_CC1120_REG_2F22_FS_SPARE':       0xAC,
  'RH_CC1120_REG_2F23_FS_VCO4':        0x10,
  'RH_CC1120_REG_2F25_FS_VCO2':        0x4F,
  'RH_CC1120_REG_2F27_FS_VCO0':        0xB4,
  'RH_CC1120_REG_2F32_XOSC5':          0x0E,
  'RH_CC1120_REG_2F36_XOSC1':          0x03,
  }

must_have_registers = {
    'RH_CC1120_REG_0000_IOCFG3': 'D',
    'RH_CC1120_REG_0001_IOCFG2': 'D',
    'RH_CC1120_REG_0002_IOCFG1': 'D',
    'RH_CC1120_REG_0008_SYNC_CFG1': 'D',
    'RH_CC1120_REG_000A_DEVIATION_M': 'M',
    'RH_CC1120_REG_000B_MODCFG_DEV_E': 'M',
    'RH_CC1120_REG_000C_DCFILT_CFG': 'D',
    'RH_CC1120_REG_0010_IQIC': 'D',
    'RH_CC1120_REG_0011_CHAN_BW': 'M',
    'RH_CC1120_REG_0013_MDMCFG0': 'M',
    'RH_CC1120_REG_0014_SYMBOL_RATE2': 'M',
    'RH_CC1120_REG_0015_SYMBOL_RATE1': 'M',
    'RH_CC1120_REG_0016_SYMBOL_RATE0': 'M',
    'RH_CC1120_REG_0017_AGC_REF': 'D',
    'RH_CC1120_REG_0018_AGC_CS_THR': 'D',
    'RH_CC1120_REG_001C_AGC_CFG1': 'D',
    'RH_CC1120_REG_001D_AGC_CFG0': 'D',
    'RH_CC1120_REG_001E_FIFO_CFG': 'D',
    'RH_CC1120_REG_001F_DEV_ADDR': 'D',
    'RH_CC1120_REG_0021_FS_CFG': 'D',
    'RH_CC1120_REG_0023_WOR_CFG0': 'D',
    'RH_CC1120_REG_0026_PKT_CFG2': 'D',
    'RH_CC1120_REG_0027_PKT_CFG1': 'D',
    'RH_CC1120_REG_0028_PKT_CFG0': 'D',
    'RH_CC1120_REG_002A_RFEND_CFG0': 'D',
    'RH_CC1120_REG_002B_PA_CFG2': 'D',
    'RH_CC1120_REG_002D_PA_CFG0': 'D',
    'RH_CC1120_REG_2F00_IF_MIX_CFG': 'D',
    'RH_CC1120_REG_2F01_FREQOFF_CFG': 'M',
    'RH_CC1120_REG_2F0C_FREQ2': 'M',
    'RH_CC1120_REG_2F0D_FREQ1': 'M',
    'RH_CC1120_REG_2F0E_FREQ0': 'M',
    'RH_CC1120_REG_2F12_FS_DIG1': 'D',
    'RH_CC1120_REG_2F13_FS_DIG0': 'D',
    'RH_CC1120_REG_2F16_FS_CAL1': 'D',
    'RH_CC1120_REG_2F17_FS_CAL0': 'D',
    'RH_CC1120_REG_2F18_FS_CHP': 'D',
    'RH_CC1120_REG_2F19_FS_DIVTWO': 'D',
    'RH_CC1120_REG_2F1B_FS_DSM0': 'D',
    'RH_CC1120_REG_2F1D_FS_DVC0': 'D',
    'RH_CC1120_REG_2F1F_FS_PFD': 'D',
    'RH_CC1120_REG_2F20_FS_PRE': 'D',
    'RH_CC1120_REG_2F21_FS_REG_DIV_CML': 'D',
    'RH_CC1120_REG_2F22_FS_SPARE': 'D',
    'RH_CC1120_REG_2F23_FS_VCO4': 'D',
    'RH_CC1120_REG_2F25_FS_VCO2': 'D',
    'RH_CC1120_REG_2F27_FS_VCO0': 'D',
    'RH_CC1120_REG_2F32_XOSC5': 'D',
    'RH_CC1120_REG_2F36_XOSC1': 'D',
  }

=======
>>>>>>> refs/remotes/origin/master
nicks = []
registers = []
files = []
settings = []
changed = []

summary = {
        'Carrier Frequency': 'Fr',
        'Deviation': 'd',
        'Manchester Enable': 'Mc',
        'RX Filter BW': 'Bw',
        'Symbol rate': 'Dr'
        }

"""
Address Config
Bit Rate
Carrier Frequency
Deviation
Device Address
Manchester Enable
Modulation Format
PA Ramping
Packet Bit Length
Packet Length
Packet Length Mode
Performance Mode
RX Filter BW
Symbol rate
TX Power
Whitening
"""


def parse(doc):
    for line in doc.split('\n'):
        if not line.startswith('#'):
            continue

        l, r = line.strip().replace('# ', '').split(' = ')

        if 'Frequency' in l:
            freq1, freq2 = r.split('.')
            freq = 'f{}'.format(freq1)

        if 'Symbol rate' in l:
            try:
                dr1, dr2 = r.split('.')
                dr = 'Dr{}_{}'.format(dr1, dr2[0:1])
            except ValueError:
                dr = 'Dr{}'.format(r)


        if 'Performance' in l:
            if 'High' in r:
                perf = 'HiPerf'
            else:
                perf = 'LowPerf'

        if 'Whitening' in l:
            if 'false' in r:
                w = 'WhitOff'
            else:
                w = 'WhitOn'

        if 'Manchester' in l:
            if 'false' in r:
                manch = 'ManchOff'
            else:
                manch = 'ManchOn'

        if 'TX Power' in l:
            pw = r.replace('.', '_') + 'dBm'

        if 'RX Filter' in l:
            bw1, bw2 = r.split('.')
            bw = 'Bw{}_{}'.format(bw1, bw2[0:1])

        if 'Deviation' in l:
            d1, d2 = r.split('.')
            d = 'd{}_{}'.format(d1, d2[0:1])

        if 'Modulation' in l:
            mod = r.replace('-', '_').replace('/', '_')

    nick = freq + 'MHz_' + mod + d + bw + dr + '_' + pw + '_' + w + '_' + manch

    return nick


def main():
    for i, py in enumerate(glob.glob(sys.argv[1])):
        name, ext = py.split('.')
        imp = __import__(name)

        reg = imp.registers

        if i == 0:
            registers = list(reg.keys())

        files.append(name)
        nicks.append(parse(open(py).read()))
        settings.append(list(reg.values()))

    for i, f in enumerate(files):
        sys.stdout.write('{0: >34} '.format(f))
        for j, r in enumerate(registers):
            v = settings[i][j]
            sys.stdout.write('{0:02X} '.format(v))
        sys.stdout.write('\n')

    print('-' * 80)

    for j, r in enumerate(registers):
        values = list(set([settings[i][j] for i, f in enumerate(files)]))

<<<<<<< HEAD
        if len(values) != 1 or r in must_have_registers:
=======
        if len(values) != 1:
>>>>>>> refs/remotes/origin/master
            changed.append(j)
            sys.stdout.write('{:>34}: {}\n'.format(r, ', '.join(map(lambda x: '{0:02X}'.format(x), values))))

    print('-' * 80)
    print('{} register changed'.format(len(changed)))
    print('-' * 80)
<<<<<<< HEAD

    # print modem registers
    print('typedef struct\n'
            '{')
    for j in changed:
        if must_have_registers.get(registers[j]) == 'M':
            r = registers[j]
            print('\tuint8_t reg_{}; ///< {}'.format(r.split('_')[3].lower(), r))
    print('} ModemConfig;')
    print('-' * 80)

    print('\t// modem configuration')
    for j in changed:
        if must_have_registers.get(registers[j]) == 'M':
            r = registers[j]
            print('\tspiWriteRegister({}, config->reg_{});'.format(r, r.split('_')[3].lower()))

    print('')

    print('\t // must-set registers')
    for j in changed:
        if must_have_registers.get(registers[j]) == 'D':
            r = registers[j]
            v = register_values.get(r)
            print('\tspiWriteRegister({}, 0x{:02X});'.format(r, v))
=======
    print('typedef struct\n'
            '{')
    for j in changed:
        r = registers[j]
        print('\tuint8_t reg_{}; ///< {}'.format(r.split('_')[3].lower(), r))
    print('} ModemConfig;')
    print('-' * 80)

    for j in changed:
        r = registers[j]
        print('\tspiWriteRegister({}, config->reg_{});'.format(r, r.split('_')[3].lower()))
>>>>>>> refs/remotes/origin/master

    print('-' * 80)

    sys.stdout.write('//')
    for j in changed:
<<<<<<< HEAD
        if must_have_registers.get(registers[j]) == 'M':
            sys.stdout.write('{}  '.format(registers[j].split('_')[3]))
=======
        sys.stdout.write('{}  '.format(registers[j].split('_')[3]))
>>>>>>> refs/remotes/origin/master

    sys.stdout.write('\n')

    for i, f in enumerate(files):
        sys.stdout.write('{ ')
<<<<<<< HEAD
        row = ['0x{0:02X}'.format(settings[i][j]) for j in changed if must_have_registers.get(registers[j]) == 'M']
        sys.stdout.write(', '.join(row))
        sys.stdout.write(' }')
=======
        for k, j in enumerate(changed):
            if k > 0:
                sys.stdout.write(', ')
            sys.stdout.write('0x{0:02X}'.format(settings[i][j]))
        sys.stdout.write('}')
>>>>>>> refs/remotes/origin/master
        sys.stdout.write(', // {}\n'.format(nicks[i]))

    print('-' * 80)


if __name__ == '__main__':
    main()
