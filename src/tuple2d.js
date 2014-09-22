// This program is a BSP Tree testbed based on the old BSP Tree FAQ demo source

// "static" methods to operate on tuples
var Tuple2d = function () {
    var tuple = Object.create(MakeTuple (2));

    tuple.cross = function (left, right) {
        return (left[0] * right[1]) - (left[1] * right[0]);
    }

    return tuple;
}();

