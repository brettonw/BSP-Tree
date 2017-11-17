var makeTuple = function (d) {
    DEF ("Tuple-" + d, function () {
        var tuple = Object.create(null);

        tuple.use = function (source) {
            this.value = source;
            return this;
        }

        tuple.zero = function () {
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = 0;
            }
            return this.use(value);
        }

        tuple.init = function (source) {
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = source[i];
            }
            return this.use (value);
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
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = this.value[i] + right.value[i];
            }
            return Object.create(Object.getPrototypeOf(this)).use (value);
        }

        tuple.subtract = function (right) {
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = this.value[i] - right.value[i];
            }
            return Object.create(Object.getPrototypeOf(this)).use (value);
        }

        tuple.scale = function (right) {
            var value = new Array(d);
            for (var i = 0; i < d; ++i) {
                value[i] = this.value[i] * right;
            }
            return Object.create(Object.getPrototypeOf(this)).use (value);
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
