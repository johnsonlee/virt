var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getSysinfo', function() {
        it('should return XML description of the sysinfo details for the host', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var xml = conn.getSysinfo();
                xml.should.be.a.String;
                console.log(xml);
            } finally {
                conn.close();
            }
        });
    });
});
