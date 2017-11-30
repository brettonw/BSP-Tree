function test() {
    var points = [
        NEW("HTuple-3").point([0, 0, 1]),
        NEW("HTuple-3").point([1, 0, 0]),
        NEW("HTuple-3").point([0, 1, 0])
    ];

    points[0].print("0s");
    points[1].print("1");
    points[2].print("2");

    var plane = NEW("Hyperplane-3").initWithPoints(points);

    plane.print("plane");


    var N = NEW("HTuple-3").point([1, 0, 0]);
    var up = NEW("HTuple-3").point([0, 1, 0]);
    var right = N.cross (up);
    N.print("N");
    up.print("up");
    right.print("right");
    up = right.cross (N);
    up.print("up");
}
