#pragma once

#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned short word;

typedef struct Cpu {
    // Ram, ig
    byte mem[0xffff];

    // where the code is
    byte code[0xffff];
    word pc;

    // Stack
    byte stack[0xff];
    byte sp;

    // Regs
    byte a;
    byte b;
    byte c;

    long instReg;
    byte flagReg; 
} CPU;

void reset(CPU* cpu) {
    cpu->sp = cpu->a = cpu->b = cpu-> c = 0;

    for (int i = 0; i < 0xff; i++) {
        cpu->stack[i] = 0;
    }

    for (int i = 0; i < 0xffff; i++) {
        cpu->mem[i] = 0;
    }
}

void ld(CPU* cpu, char reg, byte val) {
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

void st(CPU* cpu, char reg, word addr) {
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

void poke(CPU* cpu, word addr, byte val) {
    cpu->mem[addr] = val;
}

void peek(CPU* cpu, word addr) {
    cpu->a = cpu->mem[addr];
}

void push(CPU* cpu, byte val) {
    cpu->stack[cpu->sp] = val;
    cpu->sp++;
}

void pop(CPU* cpu, char reg) {
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

// Math & Logic

void add(CPU* cpu) {
    cpu->c = cpu->a + cpu->b;
}

void sub(CPU* cpu) {
    cpu->c = cpu->a - cpu->b;
}

void mul(CPU* cpu) {
    cpu->c = cpu->a * cpu->b;
}

void div(CPU* cpu) {
    cpu->c = cpu->a / cpu->b;
}

void and(CPU* cpu) {
    cpu->c = cpu->a & cpu->b;
}

void or(CPU* cpu) {
    cpu->c = cpu->a | cpu->b;
}

void xor(CPU* cpu) {
    cpu->c = cpu->a ^ cpu->b;
}

void not(CPU* cpu) {
    cpu->c = ~cpu->a;
}

// execution
void execute(CPU* cpu) {
    cpu->pc = 0;
    for (; cpu->pc < 0xffff; cpu->pc++) {
        switch (cpu->code[cpu->pc]) {
            case 0x00:{
                break;
            } case 0x01:{
                switch (cpu->code[cpu->pc + 1]) {
                    case 0x1:{
                        ld(cpu, 'a', cpu->code[cpu->pc + 2]);
                        printf("A REG: 0x%x\n", cpu->a);
                        break;
                    } case 0x2:{
                        ld(cpu, 'b', cpu->code[cpu->pc + 2]);
                        break;
                    } case 0x3:{
                        ld(cpu, 'c', cpu->code[cpu->pc + 2]);
                        break;
                    }
                }
                cpu->pc += 3;
                break;

            }

        }
    }
}