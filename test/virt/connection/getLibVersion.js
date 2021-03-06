var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getLibVersion', function() {
        it('should return the libvirt library version used on the connection', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var libVersion = conn.getLibVersion();
                libVersion.should.be.a.Number;
            } finally {
                conn.close();
            }
        });
    });
});
