#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"

// Stolen: https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format/45041802
void print_binary(int number, int num_digits) {
    int digit;
    for(digit = num_digits - 1; digit >= 0; digit--) {
        printf("%c", number & (1 << digit) ? '1' : '0');
    }
}

int main() {
    CPU cpu;

    uint8_t code[9] = {
        0xC, 0x00, 0x05, // jmp 6
        0, 0, 
        0x1, 0x1, 0x69, // ld a, 69
        0xB // break
    };

    // uint8_t code[4] = {
    //     0x1, 0x1, 0x69, 0xB
    // };

    cpu_reset(&cpu);

    FILE* fcode;
    fcode = fopen("code.bin","wb");

    for (int i = 0; i < sizeof(code); i++) {
        cpu.code[i] = code[i];
    }

    fwrite(cpu.code, sizeof(cpu.code), 1, fcode);

    cpu_execute(&cpu);
    printf("A REG: 0x%x\n", cpu.a);

    // print stack
    // for (int i = 0; i < 0xff; i++) {
    //     printf("%x: %x\n", i, cpu.stack[i]);
    // }
}
