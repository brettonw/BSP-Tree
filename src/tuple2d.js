// This program is a BSP Tree testbed based on the old BSP Tree FAQ demo source

// "static" methods to operate on tuples
var tuple2d = function () {
    var tuple2d = Object.create(tuple);


    tuple2d.cross = function (left, right) {
        return (left[0] * right[1]) - (left[1] * right[0]);
    }

    return tuple2d;
}();

