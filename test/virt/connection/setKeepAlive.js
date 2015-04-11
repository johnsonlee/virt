var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#setKeepAlive', function() {
        it('should return true if keepalive support', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var result = conn.setKeepAlive(1, 1);
                result.should.be.a.Boolean;
            } finally {
                conn.close();
            }
        });
    });
});
