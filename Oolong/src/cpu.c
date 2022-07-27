#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "cpu.h"
#include "terminal.h"

uint16_t cpu_hexcat(uint8_t a, uint8_t b) {
    char s1[20];
    char s2[20];
 
    // Convert both the integers to string
    sprintf(s1, "%x", a);
    sprintf(s2, "%x", b);
 
    // Concatenate both strings
    strcat(s1, s2);
 
    // Convert the concatenated string
    // to integer
    uint16_t num = (uint16_t)strtol(s1, NULL, 16);

    // return the formed integer
    return num;
}

// S-S-S-STOLEN!!!: https://www.geeksforgeeks.org/time-delay-c/
void cpu_delay(int secs) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * secs;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds) {}
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
    for (cpu->pc = 0; cpu->code[cpu->pc] != 0xB; cpu->pc++) {
        cpu_delay(1);
        puts("executing...");
        printf("0x%x: 0x%x\n", cpu->pc, cpu->code[cpu->pc]);
        switch (cpu->code[cpu->pc]) {
            case 0x01:{ // load a immediate
                cpu_ld(cpu, 'a', cpu->code[cpu->pc + 2]);
                cpu->pc += 2;
                break;
            } case 0x02:{ // load absolute
                uint16_t addr = cpu_hexcat(cpu->code[cpu->pc + 2], cpu->code[cpu->pc + 3]);
                switch (cpu->code[cpu->pc + 1]) {
                    case 0x1:{
                        cpu_ld(cpu, 'a', cpu->code[addr]);
                        break;
                    } case 0x2:{
                        cpu_ld(cpu, 'b', cpu->code[addr]);
                        break;
                    } case 0x3:{
                        cpu_ld(cpu, 'c', cpu->code[addr]);
                        break;
                    }
                }
                cpu->pc += 3;
                break;
            } case 0x03:{
                uint16_t addr = cpu_hexcat(cpu->code[cpu->pc + 2], cpu->code[cpu->pc + 3]);
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
                cpu->pc += 3;
                break;
            } case 0x03:{
                puts("I'm poking!");
                uint16_t addr = cpu_hexcat(cpu->code[cpu->pc + 2], cpu->code[cpu->pc + 3]);
                cpu_poke(cpu, addr, cpu->code[cpu->pc + 1]);
                cpu->pc += 3;
                break;
            } case 0xB:{
                goto exit; // im so sorry
            } case 0xC:{
                cpu->pc = cpu_hexcat(cpu->code[cpu->pc + 1], cpu->code[cpu->pc + 2]) - 1;
                // printf("%d\n%x\n", cpu->pc, cpu->code[cpu->pc]);
                break;
            }
        }

        if (cpu->mem[0] != 0) {
            printf("%c", cpu->mem[0]);
        }

        cpu->mem[0] = 0;

        cont: continue;
        exit: return;
    }
}