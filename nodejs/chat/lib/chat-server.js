var socketio = require('socket.io');
var io;
var guestNum = 1;
var nicknames = {};
var nameUsed = [];
var currentRoom = {};

exports.listen = (server) => {
	io = socketio.listen(server);
	io.set('log level', 1);
	io.sockets.on('connection',(socket) => {
		guestNum = assignGuestName(socket, guestNum, nicknames, nameUsed);
		joinRoom(socket, 'Lobby');
		handleMessageBroadcasting(socket, nicknames);
		handleNameChangeAttempts(socket, nicknames, nameUsed);
		handleRoomJoining(socket);
		socket.on('rooms', (rooms) => {
			socket.emit('rooms', io.sockets.manager.rooms);
		});
		handleClientDisconnect(socket, nicknames, nameUsed);
	});
}

function assignGuestName(socket, guestNumber, nickNames, nameUsed) {
	var name = 'Guest' + guestNumber;
	nickNames[socket.id] = name;
	socket.emit('nameResult', {
		success: true,
		name: name,
	});
	nameUsed.push(name);
	return guestNumber + 1;
}

function joinRoom(socket, room) {
	socket.join(room);
	currentRoom[socket.id] = room;
	socket.emit('joinResult',{room: room});
	socket.broadcast.to(room).emit('message', {
		text: nicknames[socket.id] + 'has joined ' + room + '.'
	});

	var usersInRoom = io.sockets.clients(room);
	if(usersInRoom.length > 1){
		var usersInRoomSummary = 'Users currently in ' + room + ': ';
		for(var index in usersInRoom){
			var userSocketId = usersInRoom[index].id;
			if(userSocketId != socket.id){
				if(index > 0)
					usersInRoomSummary += ', ';
				usersInRoomSummary += nicknames[userSocketId];
			}
		}
		usersInRoomSummary += ',';
		socket.emit('message', {text: usersInRoomSummary});
	}
}

function handleMessageBroadcasting(socket) {
	socket.on('message', (message) => {
		socket.broadcast.to(message.room).emit('message',{
			text: nicknames[socket.id] + ': ' + message.text,
		});
	});
}

function handleRoomJoining(socket){
	socket.on('join', (room) => {
		console.log(room);
		socket.leave(currentRoom[socket.id]);
		joinRoom(socket, room.newRoom);
	});
}

function handleNameChangeAttempts(socket, nickNames, nameUsed){
	socket.on('nameAttempt', (name) => {
		if(name.indexOf('Guest') == 0){
			socket.emit('nameResult', {
				success:false,
				message: 'Names cannot begin with "Guest"',
			});
		}else{
			if(nameUsed.indexOf(name) == -1){
				var previousName = nickNames[socket.id];
				var previousNameIndex = nameUsed.indexOf(previousName);
				nameUsed.push(name);
				nickNames[socket.id] = name;
				delete nameUsed[previousNameIndex];
				socket.emit('nameResult',{
					success:true,
					name:name,
				});
				socket.broadcast.to(currentRoom[socket.id]).emit('message', {
					text: previousName + ' is now known as ' + nickNames[socket.id] + '.',
				});
			}else{
				socket.emit('nameResult',{
					success:false,
					message: 'That name is already in use.'
				});
			}
		}
	});
}

function handleRoomJoining(socket) {
	socket.on('join', (room) => {
		socket.leave(currentRoom[socket.id]);
		joinRoom(socket, room.newRoom);
	});
}

function handleClientDisconnect(socket) {
	socket.on('disconnect', () =>{
		var nameIndex = nameUsed.indexOf(nicknames[socket.id]);
		delete nameUsed[nameIndex];
		delete nicknames[socket.id];
	});
}