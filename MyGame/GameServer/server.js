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
    
    socket.join(9); // Join Room
    // Send message to room
    // io.to(9).emit('message', 'Server send message to room 9')

    socket.on('SayHello', data => {
        console.log('Receive event from ',socket.id, ': ', data)
        io.emit('ClientMessage', data)
    })

    socket.on('updateLocation', data => {
        // console.log("updateLocation data: ", JSON.parse(data))
        io.to(9).emit('friendMove', JSON.parse(data))
    })
})


server.listen(PORT, () => {
    console.log(`server running on ${PORT}`);
});
