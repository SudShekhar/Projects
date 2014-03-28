var express = require('express'),
    app = express()
  , http = require('http')
  , server = http.createServer(app)
  , io = require('socket.io').listen(server);

// listen for new web clients:
server.listen(8080);

//routing
app.get('/',function(req,res){
	res.sendfile('/home/shekhar/nodechat/index.html');
});

//usernames presently in chat
var usernames = {};
var Colors;
var clrs =["#FF0000","#00FF00","#00FFFF","#FFFF00"]; // Colors which we allot to players
var ind =0; // index controls the player number and color alloted.
var turn = 0;
io.sockets.on('connection',function(socket){
	//when client emits sendchat this listens and executes
	socket.on('sendchat',function(data){
		//tell client to do updatechat with these parameters
		io.sockets.emit('updatechat',socket.username,data);
	});

	//when client emits adduser, this listens and executes
	socket.on('adduser',function(username){
		//store username in socket session for this client
		socket.username = username;
		//add username to global list
		usernames[username] = [username,clrs[ind]];
		socket.emit('attachColor',clrs[ind]);
	
		//echo to client that they have connected
		socket.emit('updatechat','SERVER','you have connected');
		//echo to all clients that person has connected
		socket.broadcast.emit('updatechat','SERVER',username+' has connected');
		//update list of users in chat, client side
		io.sockets.emit('updateusers',usernames);
		ind=(ind+1)%4;
	});
	socket.on('canvasMoved',function(x,y){
		socket.broadcast.emit('canvasMoved',x,y);
	});
	//when user disconnects perform this
	socket.on('disconnect',function(){
		//remove from global list
		if (socket.username in usernames){
			delete usernames[socket.username];
		}
		io.sockets.emit('updateusers',usernames);
		socket.broadcast.emit('updatechat','SERVER',socket.username + ' has left');
	});
});