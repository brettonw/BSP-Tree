var HTuple2d = function () {
    var tuple = registry.fetch("HTuple2");

    tuple.cross = function (left, right) {
        return (left[0] * right[1]) - (left[1] * right[0]);
    }

    return tuple;
}();

