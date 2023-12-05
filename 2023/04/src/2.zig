const std = @import("std");

const card_t = struct {
    card: std.ArrayList(u8),
    winning_numbers: []const u8,
    numbers: []const u8,
};

pub fn explore(allocator: std.mem.Allocator, cards: std.ArrayList(card_t), index: usize) !usize {
    if (index >= cards.items.len) return 1;

    var winning_numbers = std.ArrayList(u32).init(allocator);
    defer winning_numbers.deinit();
    var numbers = std.ArrayList(u32).init(allocator);
    defer numbers.deinit();

    var winning_numbers_it = std.mem.tokenizeScalar(u8, cards.items[index].winning_numbers, ' ');
    var numbers_it = std.mem.tokenizeScalar(u8, cards.items[index].numbers, ' ');

    var i: usize = 0;
    while (winning_numbers_it.next()) |winning_number| {
        try winning_numbers.append(try std.fmt.parseInt(u32, winning_number, 10));
        i = i + 1;
    }

    i = 0;
    while (numbers_it.next()) |number| {
        try numbers.append(try std.fmt.parseInt(u32, number, 10));
        i = i + 1;
    }

    i = 0;

    for (numbers.items) |number| {
        for (winning_numbers.items) |winning_number| {
            if (number == winning_number) {
                i = i + 1;
            }
        }
    }

    var result: usize = 0;
    var next: usize = 1;
    while (next <= i) {
        result = result + try explore(allocator, cards, index + next);
        next = next + 1;
    }
    return 1 + result;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();

    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var counter: usize = 0;
    var cards = std.ArrayList(card_t).init(allocator);
    defer cards.deinit();
    var card_counter: usize = 0;
    while (true) {
        try cards.append(card_t{ .card = std.ArrayList(u8).init(allocator), .winning_numbers = undefined, .numbers = undefined });
        file.reader().streamUntilDelimiter(cards.items[card_counter].card.writer(), '\n', null) catch |err| switch (err) {
            error.EndOfStream => {
                _ = cards.pop();
                break;
            },
            else => return err,
        };
        var card = cards.items[card_counter].card;

        const @":" = std.mem.indexOfScalar(u8, card.items, ':').?;
        var @"|" = std.mem.splitScalar(u8, card.items[@":" + 1 ..], '|');

        cards.items[card_counter].winning_numbers = @"|".next().?;
        cards.items[card_counter].numbers = @"|".next().?;

        card_counter = card_counter + 1;
    }

    for (cards.items, 0..) |_, i| {
        counter = counter + try explore(allocator, cards, i);
    }

    std.debug.print("{d}\n", .{counter});
}
