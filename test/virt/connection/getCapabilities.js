var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getCapabilities', function() {
        it('should return an XML string defining the capabilities', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var xml = conn.getCapabilities();
                xml.should.be.a.String;
            } finally {
                conn.close();
            }
        });
    });
});
