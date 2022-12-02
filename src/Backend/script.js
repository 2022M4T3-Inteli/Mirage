const canvas = document.getElementById("trackingMap");
const ctx = canvas.getContext("2d");

let xTamanho = canvas.width;
let yTamanho = canvas.height;
let xMetade = xTamanho/2;
let yMetade = yTamanho/2;
let radius = 5;
let ladoRetanguloX = xTamanho/30
let ladoRetanguloY = yTamanho/20

var distancia1 = Math.sqrt((xTamanho**2 + yTamanho**2)/4);
var distancia2 = Math.sqrt((xTamanho**2 + yTamanho**2)/4);
var distancia3 = Math.sqrt((xTamanho**2 + yTamanho**2)/4);
var x = (distancia3**2 - distancia1**2 - xTamanho**2)/(-2*xTamanho);
var y = (distancia2**2 - distancia1**2 - yTamanho**2)/(-2*yTamanho);


function drawTag(xFun, yFun, radiusFun){
    ctx.beginPath();
    ctx.arc(xFun, yFun, radiusFun, 0, Math.PI*2, false);
    ctx.fillStyle = "#17a2b8";
    ctx.fill();
    ctx.closePath();
}

function quadradoAzul(xBeg,yBeg,wid,hei){
    ctx.beginPath();
    ctx.rect(xBeg,yBeg,wid,hei);
    ctx.fillStyle = "#007bff";
    ctx.fill();
}

function draw(){
    ctx.clearRect(0, 0, xMetade, yMetade);
    drawTag(x,y,radius);
    quadradoAzul(0,0,ladoRetanguloX,ladoRetanguloY);
    quadradoAzul(0,yTamanho-ladoRetanguloY,ladoRetanguloX,ladoRetanguloY);
    quadradoAzul(xTamanho-ladoRetanguloX,0,ladoRetanguloX,ladoRetanguloY);
}

setInterval(draw)

function change_url(state){
    history.pushState({}, null, state);
}

function direcionar_url(){
    var url = window.location.href;
    var room = $("#rooms option:selected").val();
    var tag = $("#tags option:selected").val();
    window.location = url + "/" + room + "/" + tag;
}

function alerta(){
    window.location.reload();
    document.getElementById("alert").style.display = "block";
}

function home_page(){
    document.getElementById("alert").style.display = "block";
}

function close_alert(){
    document.getElementById("alert").style.display = "none";
    window.location.href = "home";
}