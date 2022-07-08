#pragma once

typedef unsigned char byte;
typedef unsigned short word;

typedef struct Cpu {
    // Ram, ig
    byte mem[0xffff];

    // where the code is
    byte code[0xffff];

    // Stack
    byte stack[0xff];
    byte sp;

    // Regs
    byte a;
    byte b;
    byte c;
} cpu;

void reset(cpu* cpu) {
    cpu->sp = cpu->a = cpu->b = cpu-> c = 0;

    for (int i = 0; i < 0xff; i++) {
        cpu->stack[i] = 0;
    }

    for (int i = 0; i < 0xffff; i++) {
        cpu->mem[i] = 0;
    }
}

void ld(cpu* cpu, char reg, byte val) {
    switch (reg) {
        case 'a':{
            cpu->a = val;
            break;
        } case 'b':{
            cpu->b = val;
            break;
        } case 'c':{
            cpu->c = val;
            break;
        }
    }
}

void st(cpu* cpu, char reg, word addr) {
    switch (reg) {
        case 'a':{
            cpu->mem[addr] = cpu->a;
            break;
        } case 'b':{
            cpu->mem[addr] = cpu->b;
            break;
        } case 'c':{
            cpu->mem[addr] = cpu->c;
            break;
        }
    }
}

void poke(cpu* cpu, word addr, byte val) {
    cpu->mem[addr] = val;
}

void peek(cpu* cpu, word addr) {
    cpu->a = cpu->mem[addr];
}

void push(cpu* cpu, byte val) {
    cpu->stack[cpu->sp] = val;
    cpu->sp++;
}

void pop(cpu* cpu, char reg) {
    switch (reg) {
        case 'a':{
            cpu->sp--;
            cpu->a = cpu->stack[cpu->sp];
            cpu->stack[cpu->sp] = 0;
            break;
        } case 'b':{
            cpu->sp--;
            cpu->b = cpu->stack[cpu->sp];
            cpu->stack[cpu->sp] = 0;
            break;
        } case 'c':{
            cpu->sp--;
            cpu->c = cpu->stack[cpu->sp];
            cpu->stack[cpu->sp] = 0;
            break;
        }
    }
}
