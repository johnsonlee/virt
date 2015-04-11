var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#isSecure', function() {
        it('should return a boolean value indicate that the connection to the hypervisor is secure', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var secure = conn.isSecure();
                secure.should.be.a.Boolean;
            } finally {
                conn.close();
            }
        });
    });
});
