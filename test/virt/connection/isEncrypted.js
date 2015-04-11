var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#isEncrypted', function() {
        it('should return a boolean value indicate that the connection to the hypervisor is encrypted', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var encrypted = conn.isEncrypted();
                encrypted.should.be.a.Boolean;
            } finally {
                conn.close();
            }
        });
    });
});
