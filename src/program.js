function click () {
}

function makeSvg () {
    // open the SVG and make the render port work like a mathematical system
    var svg="<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"-1.25 -1.25 2.5 2.5\" preserveAspectRatio=\"xMidYMid meet\" onclick=\"click()\">";
    svg += "<g transform=\"scale(1, -1)\">";

	// create a background layer that shows a circle
	svg += "<circle id=\"bsp-background\" class=\"bsp-background\" cx=\"0\" cy=\"0\" r=\"1\" />";

	// create a layer for drawing the scene

	// create a layer for drawing the user feedback when they click and drag

    // close the SVG
    svg += "</g></svg>";
    return svg;
}

function main () {
    var display = makeSvg ();
    document.getElementById("display").innerHTML = display;

    test();
}

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
