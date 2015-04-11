var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getNodeCellsFreeMemory', function() {
        it('should return the free memory in one or more NUMA cells', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var mems = conn.getNodeCellsFreeMemory(0, 5);
                mems.should.be.a.Array;
                mems.length.should.be.below(6);
            } finally {
                conn.close();
            }
        });
    });
});
