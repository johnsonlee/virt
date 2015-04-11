var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#nodeGetCPUMap', function() {
        it('should return the CPU map of host node CPUs', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var cpumap = conn.nodeGetCPUMap();
                cpumap.should.be.a.ArrayBuffer;
            } finally {
                conn.close();
            }
        });
    });
});
