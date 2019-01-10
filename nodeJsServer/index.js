//Imports libraries
const express = require("express");
const ip = require('ip').address();
const app = express();
let http = require('http').Server(app);
let io = require('socket.io')(http);
let message = false;

//Replies to the node MCU
app.get("/v1/", (req, res) => {
  res.send(message);
  console.log('requested v1. Sent:', message, new Date())
});

/*
App Functionality. Not important to DT lamp
*/
app.get("/", (req, res) => {
  res.sendFile(__dirname + '/index.html');
});
app.get("/vue.min.js", (req, res) => {
  res.sendFile(__dirname + '/vue.min.js');
});
let server = http.listen(3000, () => {
  console.log(`Server started at http://${ip}:${server.address().port}`);
});
io.on('connection', (socket) => {
  console.log('a user connected');
  socket.emit('state', message);
  socket.emit('ip', ip);
  socket.on('stateUpdate', newState => {
    console.log('newState', newState)
    message = newState
    io.emit('state', message);
  })
});