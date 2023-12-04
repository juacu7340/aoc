const std = @import("std");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();

    const allocator = arena.allocator();

    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var data_stat = try file.stat();
    var data_size = data_stat.size;
    var data = try file.readToEndAlloc(allocator, data_size);

    var engine_schematic = std.ArrayList([]const u8).init(allocator);
    defer engine_schematic.deinit();

    var rows = std.mem.tokenizeScalar(u8, data, '\n');
    while (rows.next()) |row| {
        try engine_schematic.append(row);
    }

    var counter: usize = 0;
    for (engine_schematic.items, 0..) |line, row| { //[] const u8
        //std.debug.print("{s}\n", .{line});
        var i: usize = 0;
        while (i < line.len) {
            var character = line[i];
            if (std.ascii.isDigit(character)) {
                var parser = std.fmt.Parser{ .buf = line[i..] };
                var number = parser.number();
                var adjacent: bool = false;
                //std.debug.print("\n:::{d}\n", .{number.?});
                loop: for (parser.pos, 0..) |_, index| {
                    //std.debug.print("\n!{c}!\n", .{line[index]});
                    // i + index = exah number
                    //std.debug.print("row:{d}\n", .{row});
                    if (i + index > 0) {
                        character = engine_schematic.items[row][i + index - 1];
                        //std.debug.print("{c}", .{character});
                        if (character != '.' and !std.ascii.isDigit(character)) {
                            adjacent = true;
                            break :loop;
                        }
                        if (row > 0) {
                            character = engine_schematic.items[row - 1][i + index - 1];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                            character = engine_schematic.items[row - 1][i + index];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                        }

                        if (row + 1 < engine_schematic.items.len) {
                            character = engine_schematic.items[row + 1][i + index - 1];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                            character = engine_schematic.items[row + 1][i + index];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                        }
                    }
                    if (i + index + 1 < line.len) {
                        character = engine_schematic.items[row][i + index + 1];
                        //std.debug.print("{c}", .{character});
                        if (character != '.' and !std.ascii.isDigit(character)) {
                            adjacent = true;
                            break :loop;
                        }
                        if (row > 0) {
                            character = engine_schematic.items[row - 1][i + index + 1];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                            character = engine_schematic.items[row - 1][i + index];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                        }

                        if (row + 1 < engine_schematic.items.len) {
                            character = engine_schematic.items[row + 1][i + index + 1];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                            character = engine_schematic.items[row + 1][i + index];
                            //std.debug.print("{c}", .{character});
                            if (character != '.' and !std.ascii.isDigit(character)) {
                                adjacent = true;
                                break :loop;
                            }
                        }
                    }
                    //std.debug.print("\n", .{});
                }
                if (adjacent) {
                    //std.debug.print("!{d}\n", .{number.?});
                    counter = counter + number.?;
                }
                i = i + parser.pos;
            }
            i = i + 1;
        }
    }
    std.debug.print("{d}\n", .{counter});
}
