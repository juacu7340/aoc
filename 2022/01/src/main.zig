const std = @import("std");

const data = @embedFile("input.txt");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();



    std.io.GenericReader(comptime Context: type, comptime ReadError: type, comptime readFn: fn(context:Context, buffer:[]u8)ReadError!usize)

}
