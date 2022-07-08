#include <stdio.h>
#include "cpu.h"

int main() {
    cpu cpu;
    
    reset(&cpu);
    push(&cpu, 0x69);
    pop(&cpu, 'a');

    printf("A Reg: %d", cpu.a);

    // print stack
    // for (int i = 0; i < 0xff; i++) {
    //     printf("%x: %x\n", i, cpu.stack[i]);
    // }
}