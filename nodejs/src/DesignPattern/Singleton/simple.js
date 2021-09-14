// simple code

var Singleton = function( name ) {
	this.name = name
	this.instance = null

}

Singleton.prototype.getName = function() {
	console.log( this.name )
}

Singleton.getInstance = function(name) {
	if (!this.instance) {
		this.instance = new Singleton(name)
	}
	return this.instance
}

var a = Singleton.getInstance('sven1')
var b = Singleton.getInstance('sven2')
var c = new Singleton('sven3')
console.log(a === b)
console.log(c === b)