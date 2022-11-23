const canvas = document.getElementById("trackingMap");
var ctx = canvas.getContext("2d");


let xPos = canvas.width/2;
let yPos = canvas.height/2;
let xSpeed = 2;
let ySpeed = 2;
let radius = 5;
function drawTag(xPosFun, yPosFun, radiusFun){

    ctx.beginPath();
    ctx.arc(xPosFun, yPosFun, radiusFun, 0, Math.PI*2, false);
    ctx.fillStyle = "#17a2b8";
    ctx.fill();
    ctx.closePath();
    // adds movement to the sphere
    // xPos += xSpeed;
    // yPos += ySpeed;
}

function quadradoVerm(xBeg,yBeg,wid,hei){
    ctx.beginPath();
    ctx.rect(xBeg,yBeg,wid,hei); //beginning from the upper left, X and Y coordinates, width and height
    ctx.fillStyle = "#007bff";
    ctx.fill();
}

function quadradoAzul(){
    ctx.beginPath();
    ctx.rect(160, 10, 100, 40);
    ctx.strokeStyle = "#17a2b8";
    ctx.stroke();
    ctx.closePath();
}

function draw(){
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawTag(xPos,yPos,radius);
    drawTag(xPos+25,yPos-55,radius);
    drawTag(xPos-70,yPos-105,radius);
    drawTag(xPos+100,yPos,radius);
    quadradoVerm(canvas.width*0.05,canvas.height*0.05,30,30);
    quadradoVerm(canvas.width*0.95,canvas.height*0.05,-30,30);
    quadradoVerm((canvas.width)/2,canvas.height*0.95,-30,-30);
}

setInterval(draw, 10)



function change_url(state){history.pushState({}, null, state);}


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
    window.location.href = "/Frontend/home.html";
}