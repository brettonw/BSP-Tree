let makeMatrix = function (m, n) {
    DEF("Matrix-" + m + "-" + n, function () {
        let matrix = Object.create(null);
        return matrix;
    });
};

makeMatrix(3, 3);
makeMatrix(4, 4);
