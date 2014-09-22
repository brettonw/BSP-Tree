var HTuple3d = function () {
    return registry.get("HTuple3d", function () {
        var tuple = Object.create(makeHTuple(3));

        tuple.cross = function (left, right) {
            return [
                (left[1] * right[2]) - (left[2] * right[1]),
                (left[2] * right[0]) - (left[0] * right[2]),
                (left[0] * right[1]) - (left[1] * right[0]),
                0
            ];
        }

        return tuple;
    });
}();
