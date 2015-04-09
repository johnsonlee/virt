var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#open', function() {
        it('should return a Connection object', function() {
            var conn = Connection.open('qemu:///system');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);
        });
    });
});
