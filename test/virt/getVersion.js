var should = require('should');
var virt = require('../../');

describe('virt', function() {
    describe('#getVersion', function() {
        it('should return the version information', function() {
            var version = virt.getVersion();
            should.exist(version);
            version.should.be.a.Number;
        });
    });
});
