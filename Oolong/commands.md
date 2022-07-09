# COMMAnds
`0x00`: nop
`ld reg, val`, `0x01, reg, val`, 3 bytes
`st reg, addr`, `0x02, reg, addr`, 4 bytes
`poke val, addr`, `0x03, val, addr`, 4 bytes
`peek addr`, `0x04, addr`, 3 bytes (stores value at a reg)
`push val`, `0x05, val`, 2 bytes
`pop reg`, `0x06, reg`, 2 bytes

Adding: c = a OP b
`add`, `0x07`, 1 byte
`sub`, `0x08`, 1 byte
`mul`, `0x09`, 1 byte
`div`, `0xA`, 1 byte

`break`, `0xB`, 1 bytes
`jmp addr`, `0xC, addr`, 3 bytes
