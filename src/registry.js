var registry = function () {
    var registry = Object.create (null);

    registry.contents = {};

    registry.get = function (name, create) {
        if (!this.contents.hasOwnProperty(name)) {
            this.contents[name] = create();
        }
        return this.contents[name];
    }

    registry.fetch = function (name) {
        return this.contents[name];
    }
}();
