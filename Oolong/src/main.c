#include <stdio.h>
#include <stdint.h>

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

    uint8_t code[4] = {0x1, 0x1, 0x69, 0xB};
    FILE* fcode;
    fcode = fopen("code.bin","wb");
    fwrite(code, sizeof(code), 1, fcode);

    for (int i = 0; i < 3; i++) {
        cpu.code[i] = code[i];
    }
    
    reset(&cpu);

    execute(&cpu);

    // print stack
    // for (int i = 0; i < 0xff; i++) {
    //     printf("%x: %x\n", i, cpu.stack[i]);
    // }
}
