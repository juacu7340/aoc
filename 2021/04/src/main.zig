const std = @import("std");

const input = @embedFile("input.txt");
const sample = @embedFile("sample.txt");

const Cell = struct {
    number: u8,
    marked: bool,
};

const Board = struct {
    numbers: [5][5]Cell,
    marked: bool,
};

pub fn @"1"(numbers: []const u8, boards: []Board) !void {
    _ = numbers;
    _ = boards;

    std.debug.print("Part 1: {}", .{});
}

pub fn @"2"() !void {}

pub fn main() !void {
    var lines = std.mem.tokenizeScalar(u8, sample, '\n');
}
