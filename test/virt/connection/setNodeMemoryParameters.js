var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#setNodeMemoryParameters', function() {
        it('should change all or a subset of the node memory tunables without error', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                conn.setNodeMemoryParameters([{
                    field : 'model',
                    type  : 1,
                    value : 0,
                }]);
            } finally {
                conn.close();
            }
        });
    });
});
