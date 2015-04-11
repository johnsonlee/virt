var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#nodeGetMemoryParameters', function() {
        it('should return all node memory parameters', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var params = conn.nodeGetMemoryParameters();
                params.should.be.a.Object;
            } finally {
                conn.close();
            }
        });
    });
});
