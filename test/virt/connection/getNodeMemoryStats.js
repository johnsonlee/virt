var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getNodeMemoryStats', function() {
        it('should return all node memory stats', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var stats = conn.getNodeMemoryStats(5);
                stats.should.be.a.Object;
            } finally {
                conn.close();
            }
        });
    });
});
