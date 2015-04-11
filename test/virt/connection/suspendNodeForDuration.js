var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#suspendNodeForDuration', function() {
        it('should suspend the node without error', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                conn.suspendNodeForDuration(1, 60); // suspend memory for 60s
            } finally {
                conn.close();
            }
        });
    });
});
