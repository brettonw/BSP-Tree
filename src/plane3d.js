// This program is a BSP Tree testbed based on the old BSP Tree FAQ demo source

// "static" methods to operate on tuples
var tuple2d = function () {
    var tuple2d = Object.create(null);

    tuple2d.validate = function (left) {
        return left.hasOwnProperty("x") && left.hasOwnProperty("y");
    }

    tuple2d.copy = function (left) {
        return {
            x: left.x,
            y: left.y
        }
    }

    tuple2d.areEqual = function (left, right) {
        return (left.x == right.x) && (left.y == right.y);
    }

    tuple2d.areNotEqual = function (left, right) {
        return (left.x != right.x) || (leftTuple.y != right.y);
    }

    tuple2d.add = function (left, right) {
        return {
            x: left.x + right.x,
            y: left.y + right.y
        }
    }

    tuple2d.subtract = function (left, right) {
        return {
            x: left.x - right.x,
            y: left.y - right.y
        }
    }

    tuple2d.scale = function (left, right) {
        function isNumber(n) {
            return !isNaN(parseFloat(n)) && isFinite(n);
        };

        if (isNumber(right) && this.validate (left)) return {
            x: left.x * right,
            y: left.y * right
        }

        if (isNumber(left) && this.validate(right)) return {
            x: left * right.x,
            y: left * right.y
        };
        
        // XXX want to halt execution here
        debugger;
        return null;
    }

    tuple2d.dot = function (left, right) {
        return (left.x * right.x) + (left.y * right.y);
    }

    tuple2d.cross = function (left, right) {
        return (left.x * right.y) - (left.y * right.x);
    }

    tuple2d.length = function (left) {
        return Math.sqrt (this.dot (left, left));
    }

    tuple2d.normalize = function (left) {
        var length = this.length(left);
        return this.scale(left, 1.0 / length);
    }

    return tuple2d;
}();

var tuple3d = function () {
    var tuple3d = Object.create(null);

    tuple3d.validate = function (left) {
        return left.hasOwnProperty("x") && left.hasOwnProperty("y") && left.hasOwnProperty("z");
    }

    tuple3d.copy = function (left) {
        return {
            x: left.x,
            y: left.y,
            z: left.z
    }
    }

    tuple3d.areEqual = function (left, right) {
        return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
    }

    tuple3d.areNotEqual = function (left, right) {
        return (left.x != right.x) || (leftTuple.y != right.y) || (leftTuple.z != right.z);
    }

    tuple3d.add = function (left, right) {
        return {
            x: left.x + right.x,
            y: left.y + right.y,
            z: left.z + right.z
        }
    }

    tuple3d.subtract = function (left, right) {
        return {
            x: left.x - right.x,
            y: left.y - right.y,
            z: left.z - right.z
    }
    }

    tuple3d.scale = function (left, right) {
        function isNumber(n) {
            return !isNaN(parseFloat(n)) && isFinite(n);
        };

        if (isNumber(right) && this.validate(left)) return {
            x: left.x * right,
            y: left.y * right,
            z: left.z * right
        }

        if (isNumber(left) && this.validate(right)) return {
            x: left * right.x,
            y: left * right.y,
            z: left * right.z
    };

        // XXX want to halt execution here
        debugger;
        return null;
    }

    tuple3d.dot = function (left, right) {
        return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
    }

    tuple3d.cross = function (left, right) {
        return {
            x: (left.y * right.z) - (left.z * right.y),
            y: (left.z * right.x) - (left.x * right.z),
            z: (left.x * right.y) - (left.y * right.x),
        };
    }

    tuple3d.length = function (left) {
        return Math.sqrt(this.dot(left, left));
    }

    tuple3d.normalize = function (left) {
        var length = this.length(left);
        return this.scale(left, 1.0 / length);
    }

    return tuple3d;
}();



//-----
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
    document.getElementById ("display").innerHTML = display;
}

