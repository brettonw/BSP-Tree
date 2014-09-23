var makeTuple = function (d) {
    DEF ("Tuple-" + d, function () {
        var tuple = Object.create(null);

        tuple.zero = function () {
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = 0;
            }
            this.value = value;
            return this;
        }

        tuple.init = function (source) {
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = source[i];
            }
            this.value = value;
            return this;
        }

        tuple.initFromTuple = function (tuple) {
            return this.init(tuple.value);
        }

        tuple.isEqualTo = function (right) {
            for (var i = 0; i < d; ++i) {
                if (this.value[i] != right.value[i]) return false;
            }
            return true;
        }

        tuple.isNotEqualTo = function (right) {
            for (var i = 0; i < d; ++i) {
                if (this.value[i] != right.value[i]) return true;
            }
            return false;
        }

        tuple.add = function (right) {
            var result = Object.create(this.prototype);
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = this.value[i] + right.value[i];
            }
            result.value = value;
            return result;
        }

        tuple.subtract = function (right) {
            var result = Object.create(this.prototype);
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = this.value[i] - right.value[i];
            }
            result.value = value;
            return result;
        }

        tuple.scale = function (right) {
            var result = Object.create(this.prototype);
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = this.value[i] * right;
            }
            result.value = value;
            return result;
        }

        tuple.dot = function (right) {
            var result = this.value[0] * right.value[0];
            for (var i = 1; i < d; ++i) {
                result += (this.value[i] * right.value[i]);
            }
            return result;
        }

        tuple.length = function () {
            return Math.sqrt (this.dot (this));
        }

        tuple.normalize = function () {
            var length = this.length();
            return this.scale(1.0 / length);
        }

        tuple.minor = function () {
            var result = 0;
            for (var i = 1; i < d; ++i) {
                if (Math.abs(this.value[i]) < Math.abs(this.value[result])) {
                    result = i;
                }
            }
            return result;
        }

        tuple.major = function () {
            var result = 0;
            for (var i = 1; i < d; ++i) {
                if (Math.abs(this.value[i]) > Math.abs(this.value[result])) {
                    result = i;
                }
            }
            return result;
        }

        tuple.print = function (name) {
            var output = name + " (" + this.value[0].toPrecision(4);
            for (var i = 1; i < d; ++i) {
                output += ", " + this.value[i].toPrecision(4);
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
