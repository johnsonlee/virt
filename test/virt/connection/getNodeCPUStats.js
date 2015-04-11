var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getNodeCPUStats', function() {
        it('should return the CPU stats of host node CPUs', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var stats = conn.getNodeCPUStats(5);
                stats.should.be.a.Object;
            } finally {
                conn.close();
            }
        });
    });
});
