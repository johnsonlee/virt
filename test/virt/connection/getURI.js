var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getURI', function() {
        it('should return the URI (name) of the hypervisor connection', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var uri = conn.getURI();
                uri.should.be.a.String;
            } finally {
                conn.close();
            }
        });
    });
});
