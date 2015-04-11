var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getHostname', function() {
        it('should return a system hostname on which the hypervisor is running', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var hostname = conn.getHostname();
                hostname.should.be.a.String;
            } finally {
                conn.close();
            }
        });
    });
});
