const std = @import("std");

const input = @embedFile("input.txt");
const sample = @embedFile("sample.txt");

pub fn @"1"(data: []const u8) !void {
    var horizontal: u32 = 0;
    var depth: u32 = 0;

    var rows = std.mem.tokenizeScalar(u8, data, '\n');

    while (rows.next()) |row| {
        const idx = std.mem.indexOfScalar(u8, row, ' ').?;

        //https://ziglang.org/download/0.12.0/release-notes.html#Aggregate-Destructuring
        const command, const number = .{ row[0..idx], try std.fmt.parseInt(u32, row[idx + 1 ..], 10) };

        switch (command[0]) {
            'f' => horizontal += number,
            'd' => depth += number,
            'u' => depth -= number,
            else => {},
        }
    }

    std.debug.print("Part 1: {}\n", .{horizontal * depth});
}

fn @"2"(data: []const u8) !void {
    var horizontal: u32 = 0;
    var depth: u32 = 0;
    var aim: u32 = 0;

    var rows = std.mem.tokenizeScalar(u8, data, '\n');

    while (rows.next()) |row| {
        const idx = std.mem.indexOfScalar(u8, row, ' ').?;

        //https://ziglang.org/download/0.12.0/release-notes.html#Aggregate-Destructuring
        const command, const number = .{ row[0..idx], try std.fmt.parseInt(u32, row[idx + 1 ..], 10) };

        switch (command[0]) {
            'f' => {
                horizontal += number;
                depth += (aim * number);
            },
            'd' => aim += number,
            'u' => aim -= number,
            else => {},
        }
    }

    std.debug.print("Part 2: {}\n", .{horizontal * depth});
}

pub fn main() !void {
    try @"1"(input);
    try @"2"(input);
}
