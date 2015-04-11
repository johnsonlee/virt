var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getMaxVcpus', function() {
        it('should return the maximum of virtual CPU', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var max = conn.getMaxVcpus('hvm');
                max.should.be.a.Number;
                max.should.be.above(0);
            } finally {
                conn.close();
            }
        });
    });
});
