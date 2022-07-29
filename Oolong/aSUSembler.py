# aSUSembler, i dont know what to call it
# fuck you
# by SirQ, worst programmer ever

# dont expect anything good, i just dont want to program in hex= 

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
    "sca": 0xC,
    "pki": 0x10,
    "pka": 0x11
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
    astr = st.replace("$", "")
    low = astr[0:2]
    high = astr[2:4]
    return (int(low, 16), int(high, 16))

def compileChar(st):
    return st.replace("'", "")

def compileString(st):
    out = []
    for c in st:
        out.append(ord(c))

    print(out)
    return out

def checkImmediate(st):
    if st[0] == "@":
        return True
    else: return False

def compileReg(reg, imm):
    if imm:
        match reg:
            case "a":
                return "lai"
            case "b":
                return "lbi"
            case "c":
                return "lci"
            case "x":
                return "lxi"
            case "y":
                return "lyi"
    else:
        match reg:
            case "a":
                return "laa"
            case "b":
                return "lba"
            case "c":
                return "lca"
            case "x":
                return "lxa"
            case "y":
                return "lya"

compiled = []

for t in tokens:
    match t.opcode:
        case "ld":
            immediate = False # immediate or absolute

            if list(t.args[1])[0] == "@":
                immediate = False
                compiled.append(opcodes[compileReg(t.args[0], immediate)])
                compiled.append(compileAddr(t.args[1].replace("@", ""))[0])
                compiled.append(compileAddr(t.args[1].replace("@", ""))[1])
            else:
                immediate = True
                compiled.append(opcodes[compileReg(t.args[0], immediate)])
                compiled.append(int(compileNum(t.args[1])))
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
            print(t.args)
            if list(t.args[0])[0] == "@":
                compiled.append(opcodes["pka"])
                compiled.append(int(compileAddr(t.args[0].replace("@", ""))[0], 16))
                compiled.append(int(compileAddr(t.args[0].replace("@", ""))[1], 16))
            else:
                compiled.append(opcodes["pki"])
                compiled.append(compileNum(t.args[0]))
            
            compiled.append(int(compileAddr(t.args[1])[0], 16))
            compiled.append(int(compileAddr(t.args[1])[1], 16))
        case "halt":
            compiled.append(0xB)
    idx += 1

# WRITE
with open(sys.argv[2], "wb") as o:
    o.write(bytearray(compiled))

print(compiled)
print(f"Outputted {len(compiled)} bytes to {sys.argv[2]}")

