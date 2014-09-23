var registry = function () {
    var registry = Object.create (null);

    registry.contents = {};

    // by convention, type names will have a root and be hyphenated to separate
    // other parameters, e.g. Tuple-3, Hyperplane-2, Matrix-3-2, etc.
    registry.define = function (typeName, create) {
        if (!this.contents.hasOwnProperty(typeName)) {
            this.contents[typeName] = create();
        }
        return this.contents[typeName];
    }

    registry.fetch = function (typeName) {
        return this.contents[typeName];
    }

    return registry;
}();

var DEF = function (typename, create) {
    registry.define(typename, create);
}

var NEW = function (typeName) {
    var prototype = registry.fetch(typeName);
    return (prototype != null) ? Object.create(prototype) : null;
}
