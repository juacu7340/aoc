const std = @import("std");
const math = @import("std").math;

pub fn s(p: f64, d: f64) f64 {
    return math.sqrt(math.pow(f64, p, 2) - (4 * d));
}

pub fn main() !void {
    var p: f64 = 44707080;
    var d: f64 = 283113411341491;

    var low: f64 = math.ceil((p - s(p, d)) / 2.0);
    var high: f64 = math.floor((p + s(p, d)) / 2.0);
    std.debug.print("{d}\n", .{high - low + 1});
}
