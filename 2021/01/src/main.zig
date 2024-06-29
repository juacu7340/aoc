const std = @import("std");

const input = @embedFile("input.txt");
const sample = @embedFile("sample.txt");

//fn @"1"(data: [*:0]const u8) !void {
//fn @"1"(data: [:0]const u8) !void {

pub fn @"1"(data: []const u8) !void {
    var rows = std.mem.tokenizeScalar(u8, data, '\n');
    var prev_number: u32 = try std.fmt.parseInt(u32, rows.peek().?, 10);
    var counter: u32 = 0;

    while (rows.next()) |row| {
        const number = try std.fmt.parseInt(u32, row, 10);
        if (number > prev_number) {
            counter = counter + 1;
        }

        prev_number = number;
    }

    std.debug.print("Part 1: {}\n", .{counter});
}

fn @"2"(data: []const u8) !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();

    var measurements = std.ArrayList(u32).init(allocator);
    defer measurements.deinit();

    var rows = std.mem.tokenizeScalar(u8, data, '\n');

    while (rows.next()) |row| {
        const number = try std.fmt.parseInt(u32, row, 10);
        try measurements.append(number);
    }

    var i: u32 = 3;
    var counter: u32 = 0;
    var prev_number: u32 = measurements.items[0] + measurements.items[1] + measurements.items[2];
    while (i < measurements.items.len) : (i += 1) {
        const number: u32 = measurements.items[i] + measurements.items[i - 1] + measurements.items[i - 2];

        if (number > prev_number) {
            counter += 1;
        }

        prev_number = number;
    }

    std.debug.print("Part 2: {}\n", .{counter});
}

pub fn main() !void {
    try @"1"(input[0..]);
    try @"2"(input[0..]);
}
