var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#openReadOnly', function() {
        it('should return a Connection object', function() {
            var conn = Connection.openReadOnly('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);
            conn.close();
        });
    });
});
