let makeHyperplane = function (d) {
    DEF("Hyperplane-" + d, function () {
        let htuple = registry.fetch("HTuple-" + d);
        let hyperplane = Object.create(htuple);

        hyperplane.initWithNormalAndPoint = function (normal, point) {
            return this.htuple(normal.value, -normal.dot(point));
        };

        hyperplane.normal = function () {
            return Object.create(Object.getPrototypeOf(this)).vector();
        };

        hyperplane.D = function () {
            return this.value[d];
        };

        hyperplane.invert = function () {
            return this.scale(-1.0);
        };

        hyperplane.intersectRay = function (ray) {
            let cosTheta = -ray.direction.dot(plane);
            return (Math.abs(cosTheta) < Math.EPSILON) ? -1.0 : htuple.dot(ray.origin, plane) / cosTheta;
        };

        return hyperplane;

    });
};

makeHyperplane(1);

makeHyperplane(2);
αω.Hyperplane2 = function () {
    let hyperplane = registry.fetch("Hyperplane-2");
    hyperplane.initWithPoints = function (points) {
        let ab = points[1].subtract(points[0]);
        let normal = NEW("HTuple2").vector([-ab[1], ab[0]]);
        return this.initWithNormalAndPoint(normal, points[0]);
    };
    return hyperplane;
}();

makeHyperplane(3);
αω.Hyperplane3 = function () {
    let hyperplane = registry.fetch("Hyperplane-3");
    hyperplane.initWithPoints = function (points) {
        let ab = points[1].subtract(points[0]);
        let bc = points[2].subtract(points[1]);
        let normal = ab.cross(bc).normalize();
        return this.initWithNormalAndPoint(normal, points[0]);
    };
    return hyperplane;
}();
