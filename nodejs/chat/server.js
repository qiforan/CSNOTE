var http = require('http');
var fs = require('fs');
var path = require('path');
var mime= require('mime');

var cache = {}

function send404(response){
	response.writeHead(404, {'Content-Type': 'text/plain'});
	response.write('Error: 404: resource not found');
	response.end();
}

function sendFile(response, filePath, fileContent){
	response.writeHead(200, {'Content-Type': mime.lookup(path.basename(filePath))});
	response.end(fileContent);
}

function serverStatic(response, cache, absPath){
	if(cache[absPath]){
		sendFile(response,absPath,cache[absPath]);
	}else{
		fs.exists(absPath, function(exists){
			if(exists){
				fs.readFile(absPath, (err, data) => {
					if(err){
						send404(response);
					}
					else{
						cache[absPath] = data;
						sendFile(response,absPath,data);
					}
				});
			}
			else{
				send404(response);
			}
		});
	}
}

var server = http.createServer((request, response) => {
	var filePath = false;
	if(request.url == '/'){
		filePath = 'public/index.html';
	}
	else{
		filePath = 'public' + request.url;
	}
	var absPath = './' + filePath;
	console.log("testing")
	console.log(request.url, filePath);
	serverStatic(response,cache,absPath);
})

server.listen(3000, () => {
	console.log("server listens at port 3000");
})

var chatServer = require('./lib/chat-server');
chatServer.listen(server)