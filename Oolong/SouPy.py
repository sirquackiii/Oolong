from distutils.dir_util import copy_tree
import opcode
import sys

# variables
opcodes = {
    "ld": 0x01,
    "st": 0x02,
    "poke": 0x03,
    "peek": 0x04,
    "push": 0x05,
    "pop": 0x06,

    "add": 0x07,
    "sub": 0x08,
    "mul": 0x09,
    "div": 0xA,

    "break": 0xB,
    "jmp": 0xC
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
print(code)
tokens = []
keywrd = ""
idx = 0

for s in code:
    ky = s.split(" ")
    for k in ky:
        print(s.split(" "))
        match k:
            case "ld":
                print(s[idx + 1])
                tokens.append(Token("ld", [ky[idx + 1], ky[idx + 2]]))
                print(tokens)
            case "st":
                print(s[idx + 1])
                tokens.append(Token("st", [ky[idx + 1], ky[idx + 2]]))
                print(tokens)
            case "halt":
                tokens.append(Token("halt"))

def compileNum(st):
    if str(st)[1] == "x":

        print(str(st)[2:])
        return int(str(st)[2:], 16)
    elif str(st)[1] == "b":
        return int(str(st)[2:], 2)

def compileAddr(str):
    addr = hex(compileNum(str)).replace("0x","")
    return (addr[0:2], addr[2:4])

compiled = []
for t in tokens:
    match t.opcode:
        case "ld":
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

            print(f"POOP: {compileAddr(str(t.args[1]))[0]}\n{compileAddr(str(t.args[1]))[1]}")
            compiled.append(int(compileAddr(t.args[1])[0], 16))
            compiled.append(int(compileAddr(t.args[1])[1], 16))
        case "halt":
            compiled.append(0xB)
    idx += 1

# WRITE
with open(sys.argv[2], "wb") as o:
    o.write(bytearray(compiled))

print(compiled)