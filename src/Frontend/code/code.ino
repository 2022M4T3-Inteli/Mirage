String html_parte1 = "<!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css' integrity='sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin='anonymous'> <title>Mirage Tracking System</title></head><body onload='load()'> <div class='sidebar'> <div class='sidebarIcons'> <a class='active' href='/index.html'> <img class='icons' src='https://img.icons8.com/ios-glyphs/512/home.png'> Home </a> <a href='/search.html'> <img class='icons' src='https://img.icons8.com/material/512/search.png'> Search </a> <a href='/add.html'> <img class='icons' src='https://img.icons8.com/ios-glyphs/512/filled-plus-2-math.png'> Add new </a> <a href='/login.html'> <img class='icons' src='https://img.icons8.com/material/512/user-male-circle--v1.png'> Profile </a> </div> </div> <header class='centralize'> <h1 id='titulo'>Mirage Tracking System</h1> </header> <div class='content'> <section> <aside> <canvas width='500px' height='350px' id='trackingMap'> Your browser does not support the canvas element. Please use a different browser. </canvas> </aside> </section> </div> <div class='boxes'> <select class='select' id='rooms' onchange='direcionar_url()'> <option>Room1</option> <option>Room2</option> </select> <br> <select class='select' id='tags' onchange='direcionar_url()'> <option>All_Tags</option> <option>Tag1</option> <option>Tag2</option> <option>Tag3</option> </select> </div> <div class='buttons'> <input type='button' value='Start search' class='btn btn-primary'> <input type='button' value='Stop search' class='btn btn-primary'> </div> <div id='sensor'>";

String html_parte2 = "</div></body><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js'></script><script>function load(){console.log('oi');}const canvas = document.getElementById('trackingMap'); var ctx = canvas.getContext('2d'); let xPos = canvas.width/2; let yPos = canvas.height/2; let radius = 8; function drawTag(xPosFun, yPosFun, radiusFun){ ctx.beginPath(); ctx.arc(xPosFun, yPosFun, radiusFun, 0, Math.PI*2, false); ctx.fillStyle = 'rgb(96, 181, 215)'; ctx.fill(); ctx.closePath(); } function drawBeacon(xPosFun, yPosFun, radiusFun){ ctx.beginPath(); ctx.arc(xPosFun, yPosFun, radiusFun, 0, Math.PI*2, false); ctx.fillStyle = 'blue'; ctx.fill(); ctx.closePath(); } function draw(){ ctx.clearRect(0, 0, canvas.width, canvas.height); drawTag(xPos + posicao_tag,yPos,radius); drawBeacon(xPos + posicao_beacon,yPos,radius); } setInterval(draw, 10); function change_url(state){history.pushState({}, null, state);} function direcionar_url(){ var url = window.location.href; var room = $('#rooms option:selected').val(); var tag = $('#tags option:selected').val(); window.location = url + '/' + room + '/' + tag; } var posicao_beacon = -(canvas.width/2) + 10; var valor_output = document.getElementById('sensor').innerText; valor_output = parseInt(valor_output); if(valor_output >= 200){valor_output = 200;} var posicao_tag = posicao_beacon + valor_output; </script> <style> :root{ /* --sidebar: rgb(84, 133, 255); */ /* --sidebar-hover: azure; */ /* --sidebar-active: rgb(96, 181, 215); */ --font: 'Times New Roman', Times, serif; --button: #007bff; /* --table-hover: rgb(218, 227, 250); */--sidebar: #7cc9ffff;--sidebar-hover: #6cade2ff;--sidebar-active: #578cbdff;/* --: #496584ff; */--table-hover: #c7c7c7ff;}.sidebar{ width: 15%; background-color: var(--sidebar); height:100%; float:left; position:fixed; overflow: auto; margin: 0; padding: 0; font-family: var(--font); border-top-left-radius:0%; border-top-right-radius:5%; border-bottom-left-radius:0%; border-bottom-right-radius:5%;}.sidebar a { display: block; color: black; padding: 10%; text-decoration: none;}.sidebar a.active { background-color: var(--sidebar-active); color: black;}.sidebar a:hover:not(.active) { background-color: var(--sidebar-hover); color: black;}.sidebarIcons{ text-align: center; line-height: 100px;}.icons{ text-align: center; width:35px;}.content{ margin-left: 15%; padding: 1px 16px; float: left; font-family: var(--font);}.boxes{ line-height: 60px; text-align: center;}.select{ text-align: center; width: 300px; border-radius: 8px; background-color: var(--sidebar-hover); color: white;}.buttons{ text-align: center;}.contentAddIcons{ line-height: 150px; text-align: center;}.addIcons{ text-align: center; width:130px;}.forms{ line-height: 50px; font-size: larger;}.formsInput{ background-color: var(--sidebar-hover); font-size: large; line-height: 30px; border-radius: 8px; border: 1px solid var(--button); color: white;}.centralize{ text-align: center; margin-left: 15%;}.loginSidebar{ width:25%; background-color: var(--sidebar); height:100%; float:left; position:fixed;}.loginContent{ margin-left: 25%; text-align: center;}.loginSidebarItens{ text-align: center; position: relative; top: 50%; transform: translateY(-50%); font-size: 30px;}.loginIcon{ text-align: center; width: 200px;}table { font-family: arial, sans-serif; border-collapse: collapse; width: 100%;} td, th { border: 1px solid #dddddd; text-align: left; padding: 8px;}tr:nth-child(even) { background-color: var(--sidebar-hover); color:white}table tr:hover { background-color: var(--table-hover); color: black;}table tr td { text-align: center;}@media screen and (max-width: 1000px) { .sidebar { width: 100%; height: auto; position: relative; border-top-left-radius:0%; border-top-right-radius:0%; border-bottom-left-radius:5%; border-bottom-right-radius:5%; } .sidebar a { float: left; } div.content { margin-left: 0; } .loginSidebar { width: 100%; height: auto; position: relative; } .loginSidebarItens{ transform: translateY(0); font-size: 20px; } .loginIcon{ width: 100px; } div.loginContent{ margin-left: 0; } .centralize{ margin-left: 0; }}@media screen and (max-width: 400px) { .sidebar a { text-align: center; float: none; } .sidebar{ border-top-left-radius:5%; border-top-right-radius:5%; border-bottom-left-radius:5%; border-bottom-right-radius:5%; } .centralize{ margin-left: 0; }}#trackingMap{ border-style: dotted; border-color: black;}#titulo{ text-align: center; font-size: 50px; font-family: var(--font); color: var(--button);}#subtitulo{ font-size: 30px; font-family: var(--font); color: var(--button); font-weight: bolder;}#tableRoom{ position: relative; text-align: center; float:initial;} </style></html>";


/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin

This base was adapted and used by group Mirage at Atech Location System

 */

#include <WiFi.h>

#define pin1 4
#define pin2 5
#define pin3 6
#define pin4 7

// const char *ssid = "SHARE-RESIDENTE";
// const char *password = "Share@residente";
// const char* ssid = "Inteli-COLLEGE"; // set the wi-fi name
// const char* password = "QazWsx@123";  // set the wi-fi password
const char* ssid = "ESP32-S3_Grupo4";
const char* password = "copia_nao";
int ldrPin = 13;
int backup_output = 0;
WiFiServer server(80);
float dist;

// Change the SSID and PASSWORD here if needed
const char * WIFI_FTM_SSID = "ESP32-S3_Grupo4"; // SSID of AP that has FTM Enabled
const char * WIFI_FTM_PASS = "copia_nao"; // STA Password
// FTM settings
// Number of FTM frames requested in terms of 4 or 8 bursts (allowed values - 0 (No pref), 16, 24, 32, 64)
const uint8_t FTM_FRAME_COUNT = 16;
// Requested time period between consecutive FTM bursts in 100’s of milliseconds (allowed values - 0 (No pref) or 2-255)
const uint16_t FTM_BURST_PERIOD = 2;
// Semaphore to signal when FTM Report has been received
xSemaphoreHandle ftmSemaphore;
// Status of the received FTM Report
bool ftmSuccess = true;

void onFtmReport(arduino_event_t *event) {
  const char * status_str[5] = {"SUCCESS", "UNSUPPORTED", "CONF_REJECTED", "NO_RESPONSE", "FAIL"};
  // Onde é feito o cálculo de wifi
  wifi_event_ftm_report_t * report = &event->event_info.wifi_ftm_report;
  // Set the global report status
  ftmSuccess = report->status == FTM_STATUS_SUCCESS;
  if (ftmSuccess) {
    // The estimated distance in meters may vary depending on some factors (see README file)
    // Serial.printf("FTM Estimate: Distance RAW: %.4f,Distance: %.4f m, Return Time: %u ns\n", (float)report->dist_est, (float)(report->dist_est - 4010) / 100, report->rtt_est);
    dist = report->rtt_est;
    Serial.println(dist);
    if( dist>=200 && dist<280 ){
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
    } else if( dist>=265 && dist<330 ){
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
    } else if( dist>=330 && dist<395 ){
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
    } else if( dist>=395 && dist<460 ){
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
    }
    // Serial.printf("Return Time: %u ns\n", report->rtt_est);
    // Pointer to FTM Report with multiple entries, should be freed after use
    free(report->ftm_report_data);
  } else {
    Serial.print("FTM Error: ");
    Serial.println(status_str[report->status]);
  }
  // Signal that report is received
  xSemaphoreGive(ftmSemaphore);
}

// Initiate FTM Session and wait for FTM Report
bool getFtmReport(){
  if(!WiFi.initiateFTM(FTM_FRAME_COUNT, FTM_BURST_PERIOD)){
    Serial.println("FTM Error: Initiate Session Failed");
    return false;
  }
  // Wait for signal that report is received and return true if status was success
  return xSemaphoreTake(ftmSemaphore, portMAX_DELAY) == pdPASS && ftmSuccess;
}

void setup()
{
  Serial.begin(115200); // start the terminal
  pinMode(13, OUTPUT); // set the buzzer pin mode
  delay(10);
  pinMode(ldrPin, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected."); // show that the WiFi was sucessfully connected 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // print the ip adress that will be used to connect to the server 
  
  server.begin();

  // Create binary semaphore (initialized taken and can be taken/given from any thread/ISR)
  ftmSemaphore = xSemaphoreCreateBinary();
  // Listen for FTM Report events
  WiFi.onEvent(onFtmReport, ARDUINO_EVENT_WIFI_FTM_REPORT);
  // Connect to AP that has FTM Enabled
  Serial.println("Connecting to FTM Responder");
  WiFi.begin(WIFI_FTM_SSID, WIFI_FTM_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("Initiating FTM session with Frame Count ");
  Serial.print(FTM_FRAME_COUNT);
  Serial.print(" and Burst Period ");
  Serial.print(FTM_BURST_PERIOD * 100);
  Serial.println(" ms");
  

}

void loop(){
  if(getFtmReport()){};
  WiFiClient client = server.available();   // listen for incoming clients
  // int ldr = analogRead(ldrPin);
  // int valor_output= ldr / 50;
  float valor_output = dist;
  if (valor_output - backup_output > 3){
    client.print(".");
    backup_output = valor_output;
    Serial.println("contener");
  }
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(html_parte1);
            client.print(valor_output);
            client.println(html_parte2);
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    // client.stop();
    Serial.println("Client Disconnected.");
  }
  backup_output = valor_output;

  delay(2000);
}