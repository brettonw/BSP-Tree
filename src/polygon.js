var makePolygon = function (d) {
    return registry.get("Polygon" + d, function () {
        var htuple = registry.fetch("HTuple" + d);
        var hyperplane = registry.fetch("Hyperplane" + d);
        var polygon = Object.create(null);

        polygon.fromPoints = function (points) {
        }

        polygon.invert = function (left) {
            return htuple.scale(left, -1.0);
        }

        polygon.contains = function (point) {
            return htuple.scale(left, -1.0);
        }

        hyperplane.intersectRay = function (plane, ray) {
            var cosTheta = -htuple.dot(ray.direction, plane);
            return (Math.abs(cosTheta) < Math.EPSILON) ? -1.0 : htuple.dot(ray.origin, plane) / cosTheta;
        }

        return hyperplane;
    });
};

makePolygon(1);
makePolygon(2);
makePolygon(3);
