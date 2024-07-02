const std = @import("std");

const input = @embedFile("input.txt");
const sample = @embedFile("sample.txt");

// Note: Change the number of bits according to the input!
pub fn @"1"(data: []const u8) !void {
    var gama_rate: u12 = 0;
    var epsilon_rate: u12 = 0;

    var rows = std.mem.tokenizeScalar(u8, data, '\n');

    var bits: [12]u12 = [_]u12{0} ** 12;
    while (rows.next()) |row| {
        for (row, 0..) |bit, i| {
            bits[i] += try std.fmt.charToDigit(bit, 10);
        }
    }

    for (bits, 0..) |bit, i| {
        if (bit > 500) {
            const value = @as(u12, 1) << @intCast(12 - 1 - i);
            gama_rate += value;
        }
    }

    epsilon_rate = ~gama_rate;
    const power_consumption = std.math.mulWide(u12, gama_rate, epsilon_rate);

    std.debug.print(
        \\Part 1: {}
        \\
    , .{power_consumption});
}

fn @"2"(data: []const u8) !void {
    const size = std.mem.count(u8, data, "\n") + 1;

    var oxygen_generator_rating: u12 = undefined;
    oxygen_generator_rating = 0;

    var co2_scrubber_rating: u12 = undefined;
    co2_scrubber_rating = 0;

    {
        var rows = std.mem.tokenizeScalar(u8, data, '\n');
        var counter: u32 = 0;

        while (rows.next()) |row| {
            const bit = try std.fmt.charToDigit(row[0], 2);
            counter += bit & @as(u8, 1);
        }
        if (counter >= (size >> 1)) {
            oxygen_generator_rating |= (1 << (12 - 1));
        } else {
            co2_scrubber_rating |= (1 << (12 - 1));
        }
    }

    for (1..12) |idx| {
        var rows = std.mem.tokenizeScalar(u8, data, '\n');
        var oxygen_counter: u32 = 0;
        var oxygen_hit_counter: u32 = 0;

        var oxygen_last_number: u12 = undefined;

        var co2_counter: u32 = 0;
        var co2_hit_counter: u32 = 0;

        var co2_last_number: u12 = undefined;

        while (rows.next()) |row| {
            const number = try std.fmt.parseInt(u12, row, 2);
            const bit = try std.fmt.charToDigit(row[idx], 2);

            const shift: u4 = (@as(u4, 12) - @as(u4, @intCast(idx)));
            const oxygen_magic: u12 = (number >> shift) ^ (oxygen_generator_rating >> shift);
            const co2_magic: u12 = (number >> shift) ^ (co2_scrubber_rating >> shift);

            if (oxygen_magic == 0) {
                oxygen_hit_counter += 1;
                oxygen_counter += bit;
                oxygen_last_number = number;
            }

            if (co2_magic == 0) {
                co2_hit_counter += 1;
                co2_counter += bit;
                co2_last_number = number;
            }
        }

        if (oxygen_hit_counter == 1) {
            oxygen_generator_rating = oxygen_last_number;
        } else if (oxygen_counter + oxygen_counter >= oxygen_hit_counter) {
            const delta = (@as(u12, 1) << @intCast(11 - idx));
            oxygen_generator_rating |= delta;
        }

        if (co2_hit_counter == 1) {
            co2_scrubber_rating = co2_last_number;
        } else if (co2_counter + co2_counter < co2_hit_counter) {
            const delta = (@as(u12, 1) << @intCast(11 - idx));
            co2_scrubber_rating |= delta;
        }
    }

    const life_support_rating = std.math.mulWide(u12, oxygen_generator_rating, co2_scrubber_rating);
    std.debug.print(
        \\Part 2: {}
        \\
    , .{life_support_rating});
}

pub fn main() !void {
    try @"1"(input);
    try @"2"(input);
}
