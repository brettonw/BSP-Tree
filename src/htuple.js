var makeHTuple = function (d) {
    return registry.get ("HTuple" + d, function () {
        var dd = d + 1;

        var tuple = Object.create(registry.fetch ("Tuple" + dd));

        tuple.htuple = function (left, h) {
            var result = new Array(dd);
            for (var i = 0; i < d; ++i) {
                result[i] = left[i];
            }
            result[d] = h;
            return result;
        }

        tuple.vector = function (left) {
            return this.htuple(left, 0);
        }

        tuple.point = function (left) {
            return this.htuple(left, 1);
        }

        return tuple;
    });
};

makeHTuple(1);
makeHTuple(2);
makeHTuple(3);
