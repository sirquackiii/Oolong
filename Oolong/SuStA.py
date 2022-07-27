# SuStA (SUper STupid Assembler)
# by SirQ, worst programmer ever

# dont expect anything good, i just dont want to program in hex
# pronounced "sOOs-Tuh", if you say "suhs-tuh" i will break your knees

import sys

# variables
opcodes = {
    "lai": 0x1,
    "laa": 0x2,
    "lbi": 0x3,
    "lba": 0x4,
    "lci": 0x5,
    "lca": 0x6,
    "sai": 0x7,
    "saa": 0x8,
    "sbi": 0x9,
    "sba": 0xA,
    "sci": 0xB,
    "sca": 0xC
}

# CLASSES

class Token:
    def __init__(self, Popcode, Pargs = []) -> None:
        self.opcode = Popcode
        self.args = Pargs

# CODE
code = ""
with open(sys.argv[1], "r") as f:
    code = f.read().split("\n")

# COMPILING
tokens = []
keywrd = ""
idx = 0

for s in code:
    ky = s.split(" ")
    print(ky)
    for k in ky:
        if "." in k:
            print(f'[{k.replace(".", "")}]')
            match k.replace(".", ""):
                case "bytes":
                    print(ky)

        match k:
            case "ld":
                tokens.append(Token("ld", [ky[idx + 1], ky[idx + 2]]))
            case "st":
                tokens.append(Token("st", [ky[idx + 1], ky[idx + 2]]))
            case "poke":
                tokens.append(Token("poke", [ky[idx + 1], ky[idx + 2]]))
            case "halt":
                tokens.append(Token("halt"))

def compileNum(st):
    if len(str(st)) >= 2:
        if str(st)[0] == "$":
            return int(str(st)[1:], 16)
        elif str(st)[0] == "%":
            return int(str(st)[1:], 2)
        elif str(st)[0] == "'":
            if st.replace("'", "") == "\\n":
                return ord("\n")
            return ord(st.replace("'", ""))
        else: return int(str(st))
    else:
        return int(str(st))

def compileAddr(st):
    addr = hex(compileNum(st)).replace("0x","")
    if len(addr) == 1:
        return ("0", "0")
    else: return (addr[0:2], addr[2:4])

    return 

def compileChar(st):
    return st.replace("'", "")

def compileString(st):
    out = []
    for c in st:
        out.append(ord(c))

    print(out)
    return out

compiled = []

for t in tokens:
    match t.opcode:
        case "ld":
            if list(t.args[2])[0] == "@":
                print("ABSOLUTE")
            compiled.append(opcodes["ld"])

            match t.args[0]:
                case "a":
                    compiled.append(1)
                case "b":
                    compiled.append(2)
                case "c":
                    compiled.append(3)

            compiled.append(compileNum(t.args[1]))
        case "st":
            compiled.append(opcodes["st"])

            match t.args[0]:
                case "a":
                    compiled.append(1)
                case "b":
                    compiled.append(2)
                case "c":
                    compiled.append(3)

            compiled.append(int(compileAddr(t.args[1])[0], 16))
            compiled.append(int(compileAddr(t.args[1])[1], 16))
        case "poke":
            compiled.append(opcodes["poke"])
            compiled.append(compileNum(t.args[0]))
            compiled.append(int(compileAddr(t.args[1])[0], 16))
            compiled.append(int(compileAddr(t.args[1])[1], 16))
        case "halt":
            compiled.append(0xB)
    idx += 1

# WRITE
with open(sys.argv[2], "wb") as o:
    o.write(bytearray(compiled))

print(f"Outputted {len(compiled)} bytes to {sys.argv[2]}")
