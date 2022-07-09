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
    uint8_t flagReg; // Zero, Carry, Overflow, Equal, Parity, Custom, Negative
} CPU;

void cpu_reset(CPU* cpu);
void cpu_ld(CPU* cpu, char reg, uint8_t val);
void cpu_st(CPU* cpu, char reg, uint16_t addr);
void cpu_poke(CPU* cpu, uint16_t addr, uint8_t val);
void cpu_peek(CPU* cpu, uint16_t addr);
void cpu_push(CPU* cpu, uint8_t val);
void cpu_pop(CPU* cpu, char reg);

// Math & Logic
void cpu_add(CPU* cpu);
void cpu_sub(CPU* cpu);
void cpu_mul(CPU* cpu);
void cpu_div(CPU* cpu);
void cpu_and(CPU* cpu);
void cpu_or(CPU* cpu);
void cpu_xor(CPU* cpu);
void cpu_not(CPU* cpu);
void cpu_execute(CPU* cpu);

// other stuff
void cpu_cmp(CPU* cpu);

// other utils
int cpu_intcat(int a, int b);