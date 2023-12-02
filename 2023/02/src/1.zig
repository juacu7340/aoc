const std = @import("std");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();

    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    const red = 12;
    const green = 13;
    const blue = 14;

    var counter: usize = 0;
    while (true) {
        var game = std.ArrayList(u8).init(allocator);
        defer game.deinit();

        file.reader().streamUntilDelimiter(game.writer(), '\n', null) catch |err| switch (err) {
            error.EndOfStream => break,
            else => return err,
        };

        const @":" = std.mem.indexOfScalar(u8, game.items, ':').?;
        const id = try std.fmt.parseInt(u32, game.items[5..@":"], 10);

        var @";" = std.mem.splitScalar(u8, game.items[@":" + 1 ..], ';');
        game: while (@";".next()) |set| {
            var @"," = std.mem.splitScalar(u8, set, ',');
            while (@",".next()) |cube| {
                var @" " = std.mem.splitScalar(u8, cube[1..], ' ');
                const number = try std.fmt.parseInt(u32, @" ".next().?, 10);
                const rgb = @" ".next().?;

                if (number > red and std.mem.eql(u8, rgb, "red")) {
                    break :game;
                } else if (number > green and std.mem.eql(u8, rgb, "green")) {
                    break :game;
                } else if (number > blue and std.mem.eql(u8, rgb, "blue")) {
                    break :game;
                }
            }
        } else {
            counter += id;
        }
    }
    std.debug.print("{d}\n", .{counter});
}
