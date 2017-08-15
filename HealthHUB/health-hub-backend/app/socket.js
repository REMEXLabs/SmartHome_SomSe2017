var routes = require('./routes.js'),
socketio = require('socket.io'),
serial = require('./serial.js');
db = require('./database.js');

var server = routes.server;
var io = socketio.listen(server);	// web socket server

server.listen(9080); //start the webserver on port 9080

io.sockets.on('connection', function (socket) {
  // gets called whenever a client connects
  console.log('The user is connected');

  socket.on('setup', (message) => {
    console.log(message);
    serial.setupFingerprint();
  });

  socket.on('new-user', (message) => {
    console.log(message);
    db.addUser(message["lastname"], message["firstname"], message["technicalAffinity"], function(user){
      console.log("user added to database");
      socket.emit('message', {type:'registration-success'});
    });
  });
});

module.exports.io=io;
