let makeHTuple = function (d) {
    DEF ("HTuple-" + d, function () {
        let dd = d + 1;

        let tuple = Object.create(registry.fetch ("Tuple-" + dd));

        tuple.htuple = function (source, h) {
            let value = new Array(dd);
            for (let i = 0; i < d; ++i) {
                value[i] = source[i];
            }
            value[d] = h;
            this.value = value;
            return this;
        };

        tuple.vector = function (source) {
            return this.htuple(source, 0);
        };

        tuple.point = function (source) {
            return this.htuple(source, 1);
        };

        return tuple;
    });
};

makeHTuple(1);

makeHTuple(2);
αω.HTuple2 = function () {
    let tuple = registry.fetch("HTuple-2");
    tuple.cross = function (right) {
        return (this.value[0] * right.value[1]) - (this.value[1] * right.value[0]);
    };
    return tuple;
}();

makeHTuple(3);
αω.HTuple3 = function () {
    let tuple = registry.fetch("HTuple-3");
    tuple.cross = function (right) {
        let value = [
            (this.value[1] * right.value[2]) - (this.value[2] * right.value[1]),
            (this.value[2] * right.value[0]) - (this.value[0] * right.value[2]),
            (this.value[0] * right.value[1]) - (this.value[1] * right.value[0]),
            0
        ];
        return Object.create(Object.getPrototypeOf(this)).use(value);
    };
    return tuple;
}();
