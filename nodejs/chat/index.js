Obj = function(){}
Obj.prototype.a = function(){
	console.log("a");
}
Obj.prototype.b = function(){
	this.a();
	console.log("b");
}

a = new Obj();
a.b();