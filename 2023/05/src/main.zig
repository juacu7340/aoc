const std = @import("std");

pub fn foo(row: [3]i64, value: i64) !i64 {
    var k0: i64 = row[0];
    var n0: i64 = row[1];
    var p: i64 = row[2];

    if (value <= n0 and value >= (n0 + (p - 1))) {
        return k0 + (value - n0);
    } else {
        return error{};
    }
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();

    const file = try std.fs.cwd().openFile("sample.txt", .{});
    defer file.close();

    var seeds = std.ArrayList(u64).init(allocator);

    var almanac: [8]std.ArrayList([3]i64) = std.ArrayList([3]i64).init(allocator) ** 8;

    while (true) {}

    for (seeds.items) |seed| {
        var map_index: usize = 0;
        var value: i64 = seed;

        while (map_index < almanac.len) {
            for (almanac[map_index].items) |map| {
                value = try foo(map, value) catch continue;
                break;
            }
            map_index = map_index + 1;
        }
    }

    var result = seeds.items[0];
    for (seeds.items) |seed| {
        if (seed < result) result = seed;
    }

    std.debug.print("{d}\n", .{result});
}
