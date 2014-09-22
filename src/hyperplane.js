var makeHyperplane = function (d) {
    return registry.get("Hyperplane" + d, function () {
        var htuple = registry.fetch("HTuple" + d);
        var hyperplane = Object.create(htuple);

        hyperplane.fromNormalAndPoint = function (normal, point) {
            htuple.htuple (normal, -htuple.dot(normal, point));
        }

        hyperplane.fromPoints = function (a, b, c) {
            var ab = htuple.subtract(b, a);
            var ac = htuple.subtract(c, a);
            var normal = htuple.normalize(htuple.cross(ab, ac));
            return this.fromNormalAndPoint(normal, a);
        }

        return hyperplane;
    });
};
