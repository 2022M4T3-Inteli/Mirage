const canvas = document.getElementById("trackingMap");
var ctx = canvas.getContext("2d");

let xPos = canvas.width/2;
let yPos = canvas.height/2;
let radius = 8;
function drawTag(xPosFun, yPosFun, radiusFun){
    ctx.beginPath();
    ctx.arc(xPosFun, yPosFun, radiusFun, 0, Math.PI*2, false);
    ctx.fillStyle = "rgb(96, 181, 215)";
    ctx.fill();
    ctx.closePath();
}
function drawBeacon(xPosFun, yPosFun, radiusFun){
    ctx.beginPath();
    ctx.arc(xPosFun, yPosFun, radiusFun, 0, Math.PI*2, false);
    ctx.fillStyle = "blue";
    ctx.fill();
    ctx.closePath();
}

function draw(){
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawTag(xPos + posicao_tag,yPos,radius);
    drawBeacon(xPos + posicao_beacon,yPos,radius);
}

setInterval(draw, 10)



function change_url(state){history.pushState({}, null, state);}


function direcionar_url(){
    var url = window.location.href;
    var room = $("#rooms option:selected").val();
    var tag = $("#tags option:selected").val();
    window.location = url + "/" + room + "/" + tag;
}



var posicao_beacon = -(canvas.width/2) + 10;
var valor_output = document.getElementById('sensor').innerText;
// var valor_output = $('#sensor').text();
valor_output = parseInt(valor_output);
if(valor_output >= 70){
    valor_output = 70;
}
var posicao_tag = posicao_beacon + valor_output;

// run a code when the page is loaded
function load(){console.log('oi');}