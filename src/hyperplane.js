var makeHyperplane = function (d) {
    DEF("Hyperplane-" + d, function () {
        var htuple = registry.fetch("HTuple-" + d);
        var hyperplane = Object.create(htuple);

        hyperplane.initWithNormalAndPoint = function (normal, point) {
            return this.htuple (normal, -htuple.dot(normal, point));
        }

        hyperplane.initWithPoints = function (a, b, c) {
            var ab = b.subtract(a);
            var bc = c.subtract(b);
            var normal = ab.cross (bc).normalize ();
            return this.initWithNormalAndPoint(normal, a);
        }

        hyperplane.normal = function () {
            return this.vector(this);
        }

        hyperplane.D = function (plane) {
            return plane[d];
        }

        hyperplane.invert = function (left) {
            return htuple.scale(left, -1.0);
        }

        hyperplane.intersectRay = function (plane, ray) {
            var cosTheta = -htuple.dot(ray.direction, plane);
            return (Math.abs(cosTheta) < Math.EPSILON) ? -1.0 : htuple.dot(ray.origin, plane) / cosTheta;
        }

        return hyperplane;
    });
};

makeHyperplane(1);
makeHyperplane(2);
makeHyperplane(3);
