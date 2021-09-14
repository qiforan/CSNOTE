var fs = require('fs');
var files = ['a.txt', 'b.txt', 'c.txt'];
for (var i = 0; i < files.length; i++) {
	fs.readFile(files[i], 'utf8', (err, contents) => {
		console.log(file[i] + ': ' + contents);
	});
}