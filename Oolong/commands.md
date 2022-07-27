# COMMAnds

ld a $ff:
01 01 FF

ld a @$ff:
02 01 00 FF

lda #$ff

-- 00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F
00 nop lai laa lbi lba lci lca sai saa sbi sba sci sca
10 pki pka phi pha ppi ppa
20 add sub mul div and or  xor not
30 cmp jmp jeq jgr jle jze jca jov jpa jcu
40 brk
50
60
70
80
90
A0
B0
C0
D0
E0
F0

flag reg:
EQUAL
GREATER
LESS
ZERO
CARRY
OVERFLOW
PARITY
CUSTOM

escape codes:
`00`: clear screen

`0x00`: nop
load immediate: `ld reg, val`, `0x01, reg, val`, 3 bytes
store immediate: `st reg, addr`, `0x02, reg, addr`, 4 bytes
`poke val, addr`, `0x03, val, addr`, 4 bytes
`peek addr`, `0x04, addr`, 3 bytes (stores value at a reg)
`push val`, `0x05, val`, 2 bytes
`pop reg`, `0x06, reg`, 2 bytes (stores value at a reg)

Operations: c = a OP b
`add`, `0x07`, 1 byte
`sub`, `0x08`, 1 byte
`mul`, `0x09`, 1 byte
`div`, `0xA`, 1 byte

`halt`, `0xB`, 1 bytes
`jmp addr`, `0xC, addr`, 3 bytes

Logic:
`and`, `0x0D`, 1 byte
`or`, `0x0E`, 1 byte
`xor`, `0x0F`, 1 byte
`not`, `0x1F`, 1 byte
