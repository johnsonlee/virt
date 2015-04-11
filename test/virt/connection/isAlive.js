var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#isAlive', function() {
        it('should return a boolean value that indicate the connection to the hypervisor is still alive', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var alive = conn.isAlive();
                alive.should.be.a.Boolean;
            } finally {
                conn.close();
            }
        });
    });
});
