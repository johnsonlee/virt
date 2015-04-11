var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#nodeGetCPUStats', function() {
        it('should return the CPU stats of host node CPUs', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var stats = conn.nodeGetCPUStats(5);
                stats.should.be.a.Object;
                console.log(JSON.stringify(stats));
            } finally {
                conn.close();
            }
        });
    });
});
