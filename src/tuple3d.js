var tuple3d = function () {
    var tuple3d = Object.create(tuple);

    tuple3d.cross = function (left, right) {
        return {
            x: (left[1] * right[2]) - (left[2] * right[1]),
            y: (left[2] * right[0]) - (left[0] * right[2]),
            z: (left[0] * right[1]) - (left[1] * right[0]),
        };
    }

    return tuple3d;
}();
