var makeTuple = function (d) {
    return registry.get ("Tuple" + d, function () {
        var tuple = Object.create(null);

        tuple.validate = function (left) {
            return (left instanceof Array) && (left.length == d);
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
            var result = new Array(d);
            for (var i = 0; i < d; ++i) {
                result[i] = left[i] + right[i];
            }
            return result;
        }

        tuple.subtract = function (left, right) {
            var result = new Array(d);
            for (var i = 0; i < d; ++i) {
                result[i] = left[i] - right[i];
            }
            return result;
        }

        tuple.scale = function (left, right) {
            function isNumber(n) {
                return !isNaN(parseFloat(n)) && isFinite(n);
            }

            var result = new Array(d);
            if (isNumber(right) && this.validate(left)) {
                for (var i = 0; i < d; ++i) {
                    result[i] = left[i] * right;
                }
            } else if (isNumber(left) && this.validate(right)) {
                for (var i = 0; i < d; ++i) {
                    result[i] = left * right[i];
                }
            } else {

                // XXX want to halt execution here
                debugger;
            }
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

        tuple.print = function (left) {
            var output = "(" + left[0];
            for (var i = 1; i < d; ++i) {
                output += ", " + left[i];
            }
            output += ")";
            console.log(output);
        }

        return tuple;
    });
};

makeTuple(1);
makeTuple(2);
makeTuple(3);
makeTuple(4);
