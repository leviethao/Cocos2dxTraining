let express = require('express');
let http = require('http');
let app = express();
let server = http.createServer(app);
let socketio = require('socket.io');
let io = socketio.listen(server);
const PORT = 3000

app.get('/', (req, res) => {
    res.json("Hello My Game")
})

io.on('connection', socket => {
    socket.emit('message', 'Welcome ' + socket.id)
    io.emit('message', 'message broadcast from server');
    
    socket.join(9); // Join Room
    // Send message to room
    io.to(9).emit('message', 'Server send message to room 9')

    socket.on('message', data => {
        console.log('message from client: ', data)
    })
    socket.on('SayHello', data => {
        console.log('Receive event from ',socket.id, ': ', data)
        io.emit('ClientMessage', data)
    })
})


server.listen(PORT, () => {
    console.log(`server running on ${PORT}`);
});
