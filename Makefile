test:
	@mocha --reporter list

doc: index.js
	@jsdoc -d doc $^

.PHONY: test
