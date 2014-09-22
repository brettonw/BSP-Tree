var HTuple2d = function () {
    return registry.get("HTuple2d", function () {
        var tuple = Object.create(makeHTuple(2));

        tuple.cross = function (left, right) {
            return (left[0] * right[1]) - (left[1] * right[0]);
        }

        return tuple;
    });
}();

