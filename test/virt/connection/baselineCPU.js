var should = require('should');
var Connection = require('../../../').Connection;

describe('Connection', function() {
    describe('#baselineCPU', function() {
        it('should return XML description of the computed CPU', function() {
            var conn = Connection.open('vbox:///session');
            should.exist(conn);
            conn.should.be.an.instanceOf(Connection);

            try {
                var cpu = conn.baselineCPU(['<?xml version="1.0" encoding="utf-8"?>'], 1);
                cpu.should.be.a.String;
            } finally {
                conn.close();
            }
        });
    });
});
