var HTuple3d = function () {
    var tuple = registry.fetch("HTuple3");
    tuple.cross = function (left, right) {
        return [
            (left[1] * right[2]) - (left[2] * right[1]),
            (left[2] * right[0]) - (left[0] * right[2]),
            (left[0] * right[1]) - (left[1] * right[0]),
            0
        ];
    }
    return tuple;
}();
