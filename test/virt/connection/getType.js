var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getType', function() {
        it('should return the name of the Hypervisor driver used', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var type = conn.getType();
                type.should.be.a.String;
            } finally {
                conn.close();
            }
        });
    });
});
