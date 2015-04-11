var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getVersion', function() {
        it('should return the version level of the Hypervisor running', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var version = conn.getVersion();
                version.should.be.a.Number;
            } finally {
                conn.close();
            }
        });
    });
});
