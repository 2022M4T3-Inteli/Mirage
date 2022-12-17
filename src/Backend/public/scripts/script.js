const canvas = document.getElementById("trackingMap");
const ctx = canvas.getContext("2d");
const inputDiv = document.getElementById("inputdata");
var distancia1 = 0;
var distancia2 = 0;
var distancia3 = 0;
// Adiciona transparência

let xTamanho = canvas.width;
let yTamanho = canvas.height;
let xMetade = xTamanho / 2;
let yMetade = yTamanho / 2;
let radius = 10;
let ladoRetanguloX = xTamanho / 30;
let ladoRetanguloY = yTamanho / 20;

function drawTag(xFun, yFun, radiusFun) {
    ctx.beginPath();
    ctx.arc(xFun, yFun, radiusFun, 0, Math.PI * 2, false);
    ctx.fillStyle = "blue";
    ctx.globalAlpha = 1;
    ctx.fill();
    ctx.closePath();
}
function drawArc(xFun, yFun, radiusFun) {
    ctx.beginPath();
    ctx.arc(xFun, yFun, radiusFun, 0, Math.PI * 2, false);
    ctx.fillStyle = "#7cc9ffff";
    ctx.globalAlpha = 0.2;
    ctx.fill();
    ctx.closePath();
}

function quadradoAzul(xBeg, yBeg, wid, hei) {
    ctx.beginPath();
    ctx.rect(xBeg, yBeg, wid, hei);
    ctx.fillStyle = "#007bff";
    ctx.fill();
}

function draw() {
    get_data();
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
    var sensor1 = (distancia1 - 4000) / 2;
    var sensor2 = (distancia2 - 4000) / 2;
    var sensor3 = (distancia3 - 4000) / 2;
    var x = (sensor3 ** 2 - sensor1 ** 2 - xTamanho ** 2) / (-2 * xTamanho);
    var y = (sensor2 ** 2 - sensor1 ** 2 - yTamanho ** 2) / (-2 * yTamanho);
    ctx.clearRect(0, 0, xTamanho, yTamanho);
    drawTag(x, y, radius);
    quadradoAzul(0, 0, ladoRetanguloX, ladoRetanguloY);
    quadradoAzul(0, yTamanho - ladoRetanguloY, ladoRetanguloX, ladoRetanguloY);
    quadradoAzul(xTamanho - ladoRetanguloX, 0, ladoRetanguloX, ladoRetanguloY);
    drawArc(0, 0, sensor1);
    drawArc(0, yTamanho, sensor2);
    drawArc(xTamanho, 0, sensor3);
}

setInterval(draw, 100);

function change_url(state) {
    history.pushState({}, null, state);
}

function direcionar_url() {
    var url = window.location.href;
    var room = $("#rooms option:selected").val();
    var tag = $("#tags option:selected").val();
    window.location = url + "/" + room + "/" + tag;
}

function alerta() {
    window.location.reload();
    document.getElementById("alert").style.display = "block";
}

function home_page() {
    document.getElementById("alert").style.display = "block";
}

function close_alert() {
    document.getElementById("alert").style.display = "none";
    window.location.href = "home";
}   
// get asyncronous data from node

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

// codigo buzzer 
function buzzerSearch(x) {
    if(x==1){
        $("#buzzer").html("On")
    }
    if(x==0){
        $("#buzzer").html("Off")
    }
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
