var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getNodeFreeMemory', function() {
        it('should return the free memory available on the Node', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var fm = conn.getNodeFreeMemory();
                fm.should.be.a.Number;
                fm.should.be.above(0);
            } finally {
                conn.close();
            }
        });
    });
});
