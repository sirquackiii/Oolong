const std = @import("std");
const cpu = @import("cpu.zig");

pub fn main() void {
    var Cpu = cpu.cpu {
        .mem = .{0} ** 0xffff,
        .stack = .{0} ** 0xff,
        .sp = 0,
        .aReg = 0,
        .bReg = 0,
        .cReg = 0,
    };

    // Mem.push(0xff);
    // for (Mem.stack) |_, i| {
    //     _ = i;
    //     std.debug.print("{}, ", .{Mem.stack[i]});
    // }
    // std.debug.print("\n\n", .{});
    // Mem.pull();
    // for (Mem.stack) |_, i| {
    //     _ = i;
    //     std.debug.print("{}, ", .{Mem.stack[i]});
    // }

    Cpu.mov('c', 0xfd);
}