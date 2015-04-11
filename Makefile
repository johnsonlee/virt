build: configure
	@node-gyp build

rebuild: configure
	@node-gyp rebuild

configure:
	@node-gyp configure

test:
	@mocha --reporter list

doc: jsdoc
	@jsdoc -d doc index.js

clean:
	@rm -rf build


.PHONY: build test
