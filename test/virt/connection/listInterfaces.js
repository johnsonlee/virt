var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#listInterfaces', function() {
        it('should return name of interfaces', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var ifaces = conn.listInterfaces();
                ifaces.should.be.a.Array;
                console.log(ifaces);
            } finally {
                conn.close();
            }
        });
    });
});
