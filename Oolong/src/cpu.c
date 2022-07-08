#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cpu.h"

void reset(CPU* cpu) {
    cpu->sp = cpu->a = cpu->b = cpu-> c = 0;

    for (int i = 0; i < 0xff; i++) {
        cpu->stack[i] = 0;
    }

    for (int i = 0; i < 0xffff; i++) {
        cpu->mem[i] = 0;
    }
}

void ld(CPU* cpu, char reg, uint8_t val) {
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

void st(CPU* cpu, char reg, uint16_t addr) {
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

void poke(CPU* cpu, uint16_t addr, uint8_t val) {
    cpu->mem[addr] = val;
}

void peek(CPU* cpu, uint16_t addr) {
    cpu->a = cpu->mem[addr];
}

void push(CPU* cpu, uint8_t val) {
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