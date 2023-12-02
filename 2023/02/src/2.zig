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
        var game = std.ArrayList(u8).init(allocator);
        defer game.deinit();

        file.reader().streamUntilDelimiter(game.writer(), '\n', null) catch |err| switch (err) {
            error.EndOfStream => break,
            else => return err,
        };

        var max = struct {
            red: u32,
            green: u32,
            blue: u32,
        }{ .red = 0, .green = 0, .blue = 0 };

        const @":" = std.mem.indexOfScalar(u8, game.items, ':').?;
        const id = try std.fmt.parseInt(u32, game.items[5..@":"], 10);
        _ = id;

        var @";" = std.mem.splitScalar(u8, game.items[@":" + 1 ..], ';');
        while (@";".next()) |set| {
            var @"," = std.mem.splitScalar(u8, set, ',');
            while (@",".next()) |cube| {
                var @" " = std.mem.splitScalar(u8, cube[1..], ' ');
                const number = try std.fmt.parseInt(u32, @" ".next().?, 10);
                const rgb = @" ".next().?;

                if (number > max.red and std.mem.eql(u8, rgb, "red")) {
                    max.red = number;
                } else if (number > max.green and std.mem.eql(u8, rgb, "green")) {
                    max.green = number;
                } else if (number > max.blue and std.mem.eql(u8, rgb, "blue")) {
                    max.blue = number;
                }
            }
        }
        counter += (max.red * max.green * max.blue);
    }
    std.debug.print("{d}\n", .{counter});
}
