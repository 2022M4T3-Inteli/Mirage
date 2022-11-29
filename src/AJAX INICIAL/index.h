const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        :root{
    /* --sidebar: rgb(84, 133, 255); */
    /* --sidebar-hover: azure; */
    /* --sidebar-active: rgb(96, 181, 215); */
    --font: "Times New Roman", Times, serif;
    --button: #007bff;
    /* --table-hover: rgb(218, 227, 250); */
--sidebar: #7cc9ffff;
--sidebar-hover: #6cade2ff;
--sidebar-active: #578cbdff;
/* --: #496584ff; */
--table-hover: #c7c7c7ff;
}

.sidebar{
    width: 15%;
    background-color: var(--sidebar);
    height:100%;
    float:left;
    position:fixed;
    overflow: auto;
    margin: 0;
    padding: 0;
    font-family: var(--font);
    border-top-left-radius:0%;
    border-top-right-radius:5%;
    border-bottom-left-radius:0%;
    border-bottom-right-radius:5%;
}
.sidebar a {
    display: block;
    color: black;
    padding: 10%;
    text-decoration: none;
}
.sidebar a.active {
    background-color: var(--sidebar-active);
    color: black;
}
.sidebar a:hover:not(.active) {
    background-color: var(--sidebar-hover);
    color: black;
}
.sidebarIcons{
    text-align: center;
    line-height: 100px;
}
.icons{
    text-align: center;
    width:35px;
}
.content{
    margin-left: 15%;
    padding: 1px 16px;
    float: left;
    font-family: var(--font);
}
.boxes{
    line-height: 60px;
    text-align: center;
}
.select{
    text-align: center;
    width: 300px;
    border-radius: 8px;
    background-color: var(--sidebar-hover);
    color: white;
}
.buttons{
    text-align: center;
}
.contentAddIcons{
    line-height: 150px;
    text-align: center;
}
.addIcons{
    text-align: center;
    width:130px;
}
.forms{
    line-height: 50px;
    font-size: larger;
}
.formsInput{
    background-color: var(--sidebar-hover);
    font-size: large;
    line-height: 30px;
    border-radius: 8px;
    border: 1px solid var(--button);
    color: white;
}
.centralize{
    text-align: center;
    margin-left: 15%;
}
.loginSidebar{
    width:25%;
    background-color: var(--sidebar);
    height:100%;
    float:left;
    position:fixed;
}
.loginContent{
    margin-left: 25%;
    text-align: center;
}
.loginSidebarItens{
    text-align: center;
    position: relative;
    top: 50%;
    transform: translateY(-50%); 
    font-size: 30px;
}
.loginIcon{
    text-align: center;
    width: 200px;
}
table {
    font-family: arial, sans-serif;
    border-collapse: collapse;
    width: 100%;
}  
td, th {
    border: 1px solid #dddddd;
    text-align: left;
    padding: 8px;
}
tr:nth-child(even) {
    background-color: var(--sidebar-hover);
    color:white
}

table tr:hover {
    background-color: var(--table-hover);
    color: black;
}
table tr td {
    text-align: center;
}
@media screen and (max-width: 1000px) {
    .sidebar {
        width: 100%;
        height: auto;
        position: relative;
        border-top-left-radius:0%;
        border-top-right-radius:0%;
        border-bottom-left-radius:5%;
        border-bottom-right-radius:5%;
    }
    .sidebar a {
        float: left;
    }
    div.content {
        margin-left: 0;
    }
    .loginSidebar {
      width: 100%;
      height: auto;
      position: relative;
    }
    .loginSidebarItens{
        transform: translateY(0);
        font-size: 20px;
    }
    .loginIcon{
        width: 100px;
    }
    div.loginContent{
        margin-left: 0;
    }
    .centralize{
        margin-left: 0;
    }
}
@media screen and (max-width: 400px) {
    .sidebar a {
      text-align: center;
      float: none;
    }
    .sidebar{
        border-top-left-radius:5%;
        border-top-right-radius:5%;
        border-bottom-left-radius:5%;
        border-bottom-right-radius:5%;
    }
    .centralize{
        margin-left: 0;
    }
}
#trackingMap{
    border-style: dotted;
    border-color: black;
}
#titulo{
    text-align: center;
    font-size: 50px;
    font-family: var(--font);
    color: var(--button);
}
#subtitulo{
    font-size: 30px;
    font-family: var(--font);
    color: var(--button);
    font-weight: bolder;
}
#tableRoom{
    position: relative;
    text-align: center;
    float:initial;
}
    </style>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <title>Mirage Tracking System</title>
</head>
<body>
    <div class="sidebar">
        <div class="sidebarIcons">
            <a class="active" href="/index.html">
                <img class="icons" src="https://img.icons8.com/ios-glyphs/512/home.png">
                Home
            </a>
            <a href="/search.html">
                <img class="icons" src="https://img.icons8.com/material/512/search.png">
                Search
            </a>            
            <a href="/add.html">
                <img class="icons" src="https://img.icons8.com/ios-glyphs/512/filled-plus-2-math.png">
                Add new
            </a>
            <a href="/login.html">
                <img class="icons" src="https://img.icons8.com/material/512/user-male-circle--v1.png">
                Profile
            </a>
        </div>
    </div>
    <header class="centralize">
        <h1 id="titulo">Mirage Tracking System</h1>
    </header>
    <div class="content">
            <section>
                <aside>
                    <canvas width="500px" height="350px" id="trackingMap">
                        Your browser does not support the canvas element. Please use a different browser.
                    </canvas>
                </aside>
            </section>
    </div>
    <div class="boxes">
        <select class="select" id="rooms" onchange="direcionar_url()">
            <option>Room1</option>
            <option>Room2</option>
        </select>
        <br>
        <select class="select" id="tags" onchange="direcionar_url()">
            <option>All_Tags</option>
            <option>Tag1</option>
            <option>Tag2</option>
            <option>Tag3</option>
        </select>
    </div>
    <div class="buttons">
        <input type="button" value="Start search" class="btn btn-primary">
        <input type="button" value="Stop search" class="btn btn-primary">
    </div>
    <div id="sensor">70</div>
</body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
<script>
    setInterval(function() {
    getData();
    }, 2000);

    function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensor").innerHTML =
        this.responseText;
        }
    };
    xhttp.open("GET", "readADC", true);
    xhttp.send();
    }

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

    
    // var posicao_tag = posicao_beacon + valor_output;

    function draw(){
        var posicao_beacon = -(canvas.width/2) + 10;
        var valor_output = $('#sensor').text();
        valor_output = parseInt(valor_output);
        if(valor_output >= canvas.width){
            valor_output = canvas.width - 100;
        }
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        drawTag(xPos + posicao_beacon + valor_output,yPos,radius);
        drawBeacon(xPos + posicao_beacon,yPos,radius);
    }




    // function change_url(state){history.pushState({}, null, state);}


    // function direcionar_url(){
    //     var url = window.location.href;
    //     var room = $("#rooms option:selected").val();
    //     var tag = $("#tags option:selected").val();
    //     window.location = url + "/" + room + "/" + tag;
    // }


    setInterval(draw, 10)
</script>
</html>
)=====";