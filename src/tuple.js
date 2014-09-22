var makeTuple = function (d) {
    return registry.get ("Tuple" + d, function () {
        var tuple = Object.create(null);

        tuple.validate = function (left) {
            return (left instanceof Array) && (left.lengh == d);
        }

        tuple.copy = function (left) {
            var result = new Array(d);
            for (var i = 0; i < d; ++i) {
                result[i] = left[i];
            }
            return result;
        }

        tuple.extend = function (left, newSize, fill) {

        }

        tuple.areEqual = function (left, right) {
            for (var i = 0; i < d; ++i) {
                if (left[i] != right[i]) return false;
            }
            return true;
        }

        tuple.areNotEqual = function (left, right) {
            for (var i = 0; i < d; ++i) {
                if (left[i] != right[i]) return true;
            }
            return false;
        }

        tuple.add = function (left, right) {
            var result = [];
            for (var i = 0; i < d; ++i) {
                result.push (left[i] + right[i]);
            }
            return result;
        }

        tuple.subtract = function (left, right) {
            var result = [];
            for (var i = 0; i < d; ++i) {
                result.push(left[i] - right[i]);
            }
            return result;
        }

        tuple.scale = function (left, right) {
            function isNumber(n) {
                return !isNaN(parseFloat(n)) && isFinite(n);
            }

            var result = [];
            if (isNumber(right) && this.validate(left)) {
                for (var i = 0; i < d; ++i) {
                    result.push(left[i] * right);
                }
            }

            if (isNumber(left) && this.validate(right)) {
                for (var i = 0; i < d; ++i) {
                    result.push(left * right[i]);
                }
            }

            // XXX want to halt execution here
            debugger;
            return result;
        }

        tuple.dot = function (left, right) {
            var result = left[0] * right[0];
            for (var i = 0; i < d; ++i) {
                result += (left[i] * right[i]);
            }
            return result;
        }

        tuple.length = function (left) {
            return Math.sqrt (this.dot (left, left));
        }

        tuple.normalize = function (left) {
            var length = this.length(left);
            return this.scale(left, 1.0 / length);
        }

        return tuple;
    });
};

makeTuple(1);
makeTuple(2);
makeTuple(3);
makeTuple(4);
