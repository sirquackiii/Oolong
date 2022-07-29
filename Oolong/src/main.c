#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"
#include "terminal.h"

FILE* fcode;
uint8_t* buffer;
long filelen;
CPU cpu;
uint8_t code[0xffff];

// Stolen: https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format/45041802
void print_binary(int number, int num_digits) {
    int digit;
    for (digit = num_digits - 1; digit >= 0; digit--) {
        printf("%c", number & (1 << digit) ? '1' : '0');
    }
}

void load_code(char* fn) {
    // file bullshit i stole from stack overflow
    fcode = fopen(fn, "rb");
    fseek(fcode, 0, SEEK_END);
    filelen = ftell(fcode);
    rewind(fcode);

    buffer = (char*)malloc(filelen * sizeof(char));
    fread(buffer, filelen, 1, fcode);
    fclose(fcode);

    cpu_reset(&cpu);

    for (int i = 0; i < sizeof(buffer); i++) {
        code[i] = buffer[i];
    }
    
    for (int i = 0; i < sizeof(code); i++) {
        cpu.code[i] = code[i];
    }
}

int main(int argc, char** argv) {
    load_file(argv[1]);

    print_fibonacci(10);

    // print stack
    // for (int i = 0; i < 0xff; i++) {
    //     printf("%x: %x\n", i, cpu.stack[i]);
    // }

    return 0;
}
