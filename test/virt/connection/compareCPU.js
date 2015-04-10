var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#compareCPU', function() {
        it('should return the comparison result', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            var result = conn.compareCPU('<?xml version="1.0" encoding="utf-8"?>', 1);
            cpu.should.be.a.Number;

            conn.close();
        });
    });
});
