var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getNodeMemoryParameters', function() {
        it('should return all node memory parameters', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var params = conn.getNodeMemoryParameters();
                params.should.be.a.Array;

                for (var i = 0; i < params.length; i++) {
                    var param = params[i];

                    param.should.have.property('field');
                    param.should.have.property('type');
                    param.should.have.property('value');
                }
            } finally {
                conn.close();
            }
        });
    });
});
