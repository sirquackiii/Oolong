#pragma once

#include <stdint.h>

typedef struct Cpu {
    // Ram, ig
    uint8_t mem[0xffff];

    // where the code is
    uint8_t code[0xffff];
    uint16_t pc;

    // Stack
    uint8_t stack[0xff];
    uint8_t sp;

    // Regs
    uint8_t a;
    uint8_t b;
    uint8_t c;

    long instReg;
    uint8_t flagReg; 
} CPU;

void reset(CPU* cpu);
void ld(CPU* cpu, char reg, uint8_t val);
void st(CPU* cpu, char reg, uint16_t addr);
void poke(CPU* cpu, uint16_t addr, uint8_t val);
void peek(CPU* cpu, uint16_t addr);
void push(CPU* cpu, uint8_t val);
void pop(CPU* cpu, char reg);

// Math & Logic

void add(CPU* cpu);
void sub(CPU* cpu);
void mul(CPU* cpu);
void div(CPU* cpu);
void and(CPU* cpu);
void or(CPU* cpu);
void xor(CPU* cpu);
void not(CPU* cpu);
void execute(CPU* cpu);