//Config inciial de ambiente, acesso ao database
const dotenv = require('dotenv');
dotenv.config({path: "./config.env"}); 
const path = require('path');

// Instância do express, starter do server (app) e da ORM (mongoose)
const express = require('express');
const app = express();
const mongoose = require('mongoose');
const hostname = '127.0.0.1';
const port = 8080;
const bodyParser = require('body-parser');
const cors = require('cors')

// Define variable
var externalDist1 = 4510;
var externalDist2 = 4920;
var externalDist3 = 4850;
var externalBuzzer = 0;


// Leitor de JSON utilizando middlewares
app 
    .use(
    express.urlencoded({
        extended: true,
    }),
    )
    .use(bodyParser.json())

    //Set do uso de arquivos esáticos(imagens, css e afins)
    .use(express.static(__dirname + '/public'))

    // Set do tipo de arquivo recebido pelo servidor nas requisições de formulário
    .use(express.json())
    
    // Set cors para requisição de renderização de página
    .use(cors());

// setup da view engine (tipo de arquivo que será lido, node não roda html )
app
    .set('views', path.join(__dirname, 'views'))
    .set('view engine', 'ejs');



//Rotas da API 
const loginRoutes = require('./routes/loginRoutes')
const homeRoutes = require('./routes/homeRoutes')
const assignRoutes = require('./routes/assignRoutes')
const assignBeaconRoutes = require('./routes/assignBeaconRoutes')
const assignRoomRoutes = require('./routes/assignRoomRoutes')
const assignTagRoutes = require('./routes/assignTagRoutes')
const searchRoutes = require('./routes/searchRoutes')
const editRoutes = require('./routes/editRoutes')
const removeRoutes = require('./routes/removeRoutes')

//Uso das rotas na URL
app.use('/', loginRoutes)
app.use('/search', searchRoutes)
app.use('/home', homeRoutes)
app.use('/assign', assignRoutes)
app.use('/beacon', assignBeaconRoutes)
app.use('/room', assignRoomRoutes)
app.use('/tag', assignTagRoutes)
app.use('/edit', editRoutes)
app.use('/remove', removeRoutes)


// Log de conexão com o servidor e database
mongoose
    .connect(
        process.env.DATABASE
    )
    .then(() => {
        console.log("Conectamos ao banco")
    } )
    .catch((err) => console.log(err));

// Retorna porta que está operando
app
    .listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
});

app.get("/getdistances", function (req, res) {
    res.header("Access-Control-Allow-Origin", "*");
    dados = {
        dist1: externalDist1,
        dist2: externalDist2,
        dist3: externalDist3,
    };
    jsonD = JSON.stringify(dados);
    res.send(jsonD);
});

function buzzerSearch(x) {
    let url = "/getbuzzer";
    $.ajax({
    type: "POST",
    url: url,
    contentType: "application/json; charset=utf-8",
    dataType: "json",
    data: JSON.stringify({
            status: x,
        }),
    });
}