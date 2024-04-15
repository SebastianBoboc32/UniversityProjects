const http = require('http');
const app = require('./app');
const cors = require('cors');
const { faker } = require('@faker-js/faker');
const { Server } = require('socket.io');

const port = process.env.PORT || 3000;

const corsOptions = {
    origin: 'http://localhost:3001', 
    methods: ["GET", "POST","PUT","DELETE"],
    allowedHeaders: ["Content-Type"],
    credentials: true,
  };
app.use(cors(corsOptions));

const server = http.createServer(app);

const io = new Server(server, {
    cors: {
      origin: "http://localhost:3001",
      methods: ["GET", "POST","PUT","DELETE"],
      credentials: true
    }
  });

function generateARandomFish() {
        return ({
            id: faker.string.uuid(),
            name: faker.commerce.productName(), 
            origin: faker.location.country(),
            species: faker.lorem.word(),
            beauty_score: parseFloat(faker.string.numeric(2, { bannedDigits: ['0'], allowLeadingZeros: false })) / 10
        });
}



io.on('connection',(socket) =>{
    console.log('a user connected');

    socket.on('disconnect',() => {
        console.log('user disconnected');
    });

    const intervalId = setInterval(() =>{
        const data = generateARandomFish();
        io.emit('data',data);
        console.log('Fish sen succesfully');
    },10000);

    socket.on('disconnect',() => {
        clearInterval(intervalId);
    })
})

server.listen(port);
