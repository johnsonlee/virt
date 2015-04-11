var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#ref', function() {
        it('should return true', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var result = conn.ref();
                result.should.be.true;
            } finally {
                conn.close();
            }
        });
    });
});
