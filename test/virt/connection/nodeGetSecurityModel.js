var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#nodeGetSecurityModel', function() {
        it('should return the security model of a hypervisor', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var model = conn.nodeGetSecurityModel();
                model.should.be.a.Object;
                model.should.have.property('model');
                model.should.have.property('doi');
            } finally {
                conn.close();
            }
        });
    });
});
