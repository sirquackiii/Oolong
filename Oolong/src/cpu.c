#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cpu.h"

uint8_t cpu_intcat(uint8_t a, uint8_t b) {
    char s1[20];
    char s2[20];
 
    // Convert both the integers to string
    sprintf(s1, "%x", a);
    sprintf(s2, "%x", b);
 
    // Concatenate both strings
    strcat(s1, s2);
    printf("CAT: %s\n", s1);
 
    // Convert the concatenated string
    // to integer
    int num = (int)strtol(s1, NULL, 16);
 
    printf("intcat out: 0x%x\n", (uint16_t)num);
    // return the formed integer
    return (uint16_t)num;
}

void cpu_reset(CPU* cpu) {
    cpu->sp = cpu->a = cpu->b = cpu->c = 0;

    for (int i = 0; i < 0xff; i++) {
        cpu->stack[i] = 0;
    }

    for (int i = 0; i < 0xffff; i++) {
        cpu->mem[i] = 0;
    }
}

void cpu_ld(CPU* cpu, char reg, uint8_t val) {
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

void cpu_st(CPU* cpu, char reg, uint16_t addr) {
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

void cpu_poke(CPU* cpu, uint16_t addr, uint8_t val) {
    cpu->mem[addr] = val;
}

void cpu_peek(CPU* cpu, uint16_t addr) {
    cpu->a = cpu->mem[addr];
}

void cpu_push(CPU* cpu, uint8_t val) {
    cpu->stack[cpu->sp] = val;
    cpu->sp++;
}

void cpu_pop(CPU* cpu, char reg) {
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

void cpu_add(CPU* cpu) {
    cpu->c = cpu->a + cpu->b;
}

void cpu_sub(CPU* cpu) {
    cpu->c = cpu->a - cpu->b;
}

void cpu_mul(CPU* cpu) {
    cpu->c = cpu->a * cpu->b;
}

void cpu_div(CPU* cpu) {
    cpu->c = cpu->a / cpu->b;
}

void cpu_and(CPU* cpu) {
    cpu->c = cpu->a & cpu->b;
}

void cpu_or(CPU* cpu) {
    cpu->c = cpu->a | cpu->b;
}

void cpu_xor(CPU* cpu) {
    cpu->c = cpu->a ^ cpu->b;
}

void cpu_not(CPU* cpu) {
    cpu->c = ~cpu->a;
}

// execution
void cpu_execute(CPU* cpu) {
    cpu->pc = 0;
    for (; cpu->pc < 0xffff; cpu->pc++) {
        printf("0x%x\n", cpu->pc);
        switch (cpu->code[cpu->pc]) {
            case 0x01:{
                switch (cpu->code[cpu->pc + 1]) {
                    case 0x1:{
                        cpu_ld(cpu, 'a', cpu->code[cpu->pc + 2]);
                        break;
                    } case 0x2:{
                        cpu_ld(cpu, 'b', cpu->code[cpu->pc + 2]);
                        break;
                    } case 0x3:{
                        cpu_ld(cpu, 'c', cpu->code[cpu->pc + 2]);
                        break;
                    }
                }
                cpu->pc += 2;
                printf("NEWADDR: 0x%x\n", cpu->code[cpu->pc]);
                break;
            } case 0x2:{
                puts("gjfdsjkfd");
                uint16_t addr = cpu_intcat(cpu->code[cpu->pc + 2], cpu->code[cpu->pc + 3]);
                switch (cpu->code[cpu->pc + 1]) {
                    case 0x1:{
                        cpu_st(cpu, 'a', addr);
                        break;
                    } case 0x2:{
                        cpu_st(cpu, 'b', addr);
                        break;
                    } case 0x3:{
                        cpu_st(cpu, 'c', addr);
                        break;
                    }
                }
                printf("ADDR: 0x%x\n", cpu->mem[addr]);
                cpu->pc += 3;
                break;
            } case 0xB:{
                goto exit; // im so sorry
            } case 0xC:{
                cpu->pc = cpu_intcat(cpu->code[cpu->pc + 1], cpu->code[cpu->pc + 2]) - 1;
                // printf("%d\n%x\n", cpu->pc, cpu->code[cpu->pc]);
                break;
            }
        }

        // if (cpu->mem[0] != 0) {
        //     printf("%c", cpu->mem[0]);
        // }

        exit: return;
    }
}