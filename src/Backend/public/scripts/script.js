// Elementos do html
const canvas = document.getElementById("trackingMap");
const ctx = canvas.getContext("2d");
const inputDiv = document.getElementById("inputdata");

// Distancias usadas para o cálculo da posição
var distancia1 = 0;
var distancia2 = 0;
var distancia3 = 0;

// Variáveis do canvas
let xTamanho = canvas.width; // Tamanho do canvas em x
let yTamanho = canvas.height; // Tamanho do canvas em y
let radius = 10; // Raio da tag
let ladoRetanguloX = xTamanho / 30; // Lado do retângulo do beacon
let ladoRetanguloY = yTamanho / 20; // Lado do retângulo do beacon

// Função que desenha uma tag no canvas
function drawTag(xFun, yFun, radiusFun) {
    ctx.beginPath();
    ctx.arc(xFun, yFun, radiusFun, 0, Math.PI * 2, false);
    ctx.fillStyle = "blue";
    ctx.globalAlpha = 1;
    ctx.fill();
    ctx.closePath();
}

// Função que desenha os arcos no canvas
function drawArc(xFun, yFun, radiusFun) {
    ctx.beginPath();
    ctx.arc(xFun, yFun, radiusFun, 0, Math.PI * 2, false);
    ctx.fillStyle = "#7cc9ffff";
    ctx.globalAlpha = 0.2;
    ctx.fill();
    ctx.closePath();
}

// Função que desenha os beacons no canvas
function quadradoAzul(xBeg, yBeg, wid, hei) {
    ctx.beginPath();
    ctx.rect(xBeg, yBeg, wid, hei);
    ctx.fillStyle = "#007bff";
    ctx.fill();
}

// Função que desenha os elementos no canvas
// Esta função se repete a cada 100ms
function draw() {
    get_data(); // Função que recebe os dados do node
  // input into html
    inputDiv.innerHTML =
        "Distancia 1: " +
        (distancia1 - 4000) / 100 +
        "m <br>" +
        " Distancia 2: " +
        (distancia2 - 4000) / 100 +
        "m <br>" +
        " Distancia 3: " +
        (distancia3 - 4000) / 100 +
        "m";
    // Normalização das distâncias recebidas
    var sensor1 = (distancia1 - 4000) / 2;
    var sensor2 = (distancia2 - 4000) / 2;
    var sensor3 = (distancia3 - 4000) / 2;
    // Cálculo da posição da tag
    // Ao desenharmos triângulos retângulos, podemos usar o teorema de pitágoras para calcular a posição da tag no canvas
    var x = (sensor3 ** 2 - sensor1 ** 2 - xTamanho ** 2) / (-2 * xTamanho);
    var y = (sensor2 ** 2 - sensor1 ** 2 - yTamanho ** 2) / (-2 * yTamanho);
    ctx.clearRect(0, 0, xTamanho, yTamanho); // Limpa o canvas para receber os novos desenhos
    // Desenha os elementos no canvas
    drawTag(x, y, radius);
    quadradoAzul(0, 0, ladoRetanguloX, ladoRetanguloY);
    quadradoAzul(0, yTamanho - ladoRetanguloY, ladoRetanguloX, ladoRetanguloY);
    quadradoAzul(xTamanho - ladoRetanguloX, 0, ladoRetanguloX, ladoRetanguloY);
    drawArc(0, 0, sensor1);
    drawArc(0, yTamanho, sensor2);
    drawArc(xTamanho, 0, sensor3);
}

// Função que recebe os dados do node
function get_data() {
    let url = "/getdistances";
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
        let data = JSON.parse(this.responseText);
        distancia1 = data.dist1;
        distancia2 = data.dist2;
        distancia3 = data.dist3;
    }
};
    xhttp.open("GET", url, true);
    xhttp.send();
}

// Função que envia um sinal para o buzzer ligar ou desligar, e troca o texto do botão
function buzzerSearch(x) {
    if(x==1){
        $("#buzzer").html("On")
    }
    if(x==0){
        $("#buzzer").html("Off")
    }
    // Post AJAX do estado do buzzer
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

// Coloca a função draw em loop
setInterval(draw, 100);