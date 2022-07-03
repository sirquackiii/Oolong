const std = @import("std");

pub const cpu = struct {
    mem: [0xffff]u8,
    stack: [0xff]u8,
    sp: u8, // stack pointer
    aReg: u8,
    bReg: u8,
    cReg: u8,
    // Functions
    pub fn push(self: *cpu, byte: u8) void {
        self.sp += 1;
        self.stack[self.sp] = byte;
    }

    pub fn pull(self: *cpu) void {
        self.stack[self.sp] = 0;
        self.sp -= 1;
    }

    pub fn poke(self: *cpu, addr: u16, val: u8) void {
        self.mem[addr] = val;
    }

    pub fn peek(self: *cpu, addr: u16) u8 {
        return self.mem[addr];
    }

    pub fn mov(self: *cpu, reg: u8, val: u8) void {
        switch (reg) {
            'a' => {
                self.aReg = val;
                std.debug.print("REG A: ${x}\n", .{val});
            },

            'b' => {
                self.bReg = val;
                std.debug.print("REG B: ${x}\n", .{val});
            },

            'c' => {
                self.cReg = val;
                std.debug.print("REG C: ${x}\n", .{val});
            },

            else => std.debug.print("AAAAAA\n", .{}),
        }
    }
};

pub fn hello() i8 {
    return 5;
}