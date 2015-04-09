all: rebuild test doc

rebuild:
	@node-gyp config rebuild

test:
	@mocha --reporter list

doc: index.js
	@jsdoc -d doc $^

.PHONY: rebuild test doc
