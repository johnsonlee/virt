var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#getNodeInfo', function() {
        it('should return the hardware information about the node', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var info = conn.getNodeInfo();
                info.should.be.a.Object;
                info.should.have.property('model');
                info.should.have.property('memory');
                info.should.have.property('cpus');
                info.should.have.property('mhz');
                info.should.have.property('nodes');
                info.should.have.property('sockets');
                info.should.have.property('cores');
                info.should.have.property('threads');
            } finally {
                conn.close();
            }
        });
    });
});
