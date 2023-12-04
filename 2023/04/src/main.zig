const std = @import("std");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();

    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var counter: usize = 0;
    while (true) {
        var card = std.ArrayList(u8).init(allocator);
        defer card.deinit();

        file.reader().streamUntilDelimiter(card.writer(), '\n', null) catch |err| switch (err) {
            error.EndOfStream => break,
            else => return err,
        };

        const @":" = std.mem.indexOfScalar(u8, card.items, ':').?;
        var @"|" = std.mem.splitScalar(u8, card.items[@":" + 1 ..], '|');

        var winning_numbers_it = std.mem.tokenizeScalar(u8, @"|".next().?, ' ');
        var numbers_it = std.mem.tokenizeScalar(u8, @"|".next().?, ' ');

        var winning_numbers = std.ArrayList(u32).init(allocator);
        var numbers = std.ArrayList(u32).init(allocator);
        var index: usize = 0;
        while (winning_numbers_it.next()) |winning_number| {
            try winning_numbers.append(try std.fmt.parseInt(u32, winning_number, 10));
            index = index + 1;
        }

        index = 0;
        while (numbers_it.next()) |number| {
            try numbers.append(try std.fmt.parseInt(u32, number, 10));
            index = index + 1;
        }

        var score: usize = 0;
        for (numbers.items) |number| {
            for (winning_numbers.items) |winning_number| {
                if (number == winning_number) {
                    if (score == 0) {
                        score = 1;
                    } else {
                        score = score * 2;
                    }
                }
            }
        }
        counter = counter + score;
    }
    std.debug.print("{d}\n", .{counter});
}
