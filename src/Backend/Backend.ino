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

// const char *ssid = "SHARE-RESIDENTE";
// const char *password = "Share@residente";
const char* ssid = "Inteli-COLLEGE"; // set the wi-fi name
const char* password = "QazWsx@123";  // set the wi-fi password

WiFiServer server(80);

void setup()
{
    Serial.begin(115200); // start the terminal
    pinMode(13, OUTPUT); // set the buzzer pin mode
    delay(10);

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

}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

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
            client.println("<!DOCTYPE html>\
  <html lang=\"en\">\
  <head>\
      <meta charset=\"UTF-8\">\
      <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
      <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
      <title>Mirage Tracking System</title>\
  </head>\
  <body>\
      <div class=\"sidebar\">\
          <div class=\"icons\">\
          <img src=\"https://img.icons8.com/ios-glyphs/512/home.png\" width=\"35px\">\
          <img src=\"https://img.icons8.com/material/512/search.png\" width=\"35px\">\
          <img src=\"https://img.icons8.com/material/512/user-male-circle--v1.png\" width=\"35px\">\
          </div>\
      </div>\
      <header>\
          <h1 id=\"titulo\">Mirage Tracking System</h1>\
      </header>\
      <div class=\"content\">\
              <section>\
                  <aside>\
                      <canvas width=\"500px\" height=\"350px\" id=\"trackingMap\">\
                          Your browser does not support the canvas element. Please use a different browser.\
                      </canvas>\
                  </aside>\
              </section>\
      </div>\
      <div class=\"boxes\">\
          <select class=\"select\">\
              <option>Room1</option>\
              <option>Room2</option>\
          </select>\
          <br>\
          <select class=\"select\">\
              <option>Tag1</option>\
              <option>Tag2</option>\
              <option>Tag3</option>\
          </select>\
      </div>\
      <div class=\"buttons\">\
          <p><a href=\"/H\"><button class=\"botao_on\">Start Search</button></a></p>\
          <p><a href=\"/L\"><button class=\"botao_off\">Stop Search</button></a></p>\
      </div>\
  </body>\
  <script>const canvas = document.getElementById(\"trackingMap\");var ctx = canvas.getContext(\"2d\");let xPos = canvas.width/2;let yPos = canvas.height/2;let xSpeed = 2;let ySpeed = 2;let radius = 5;function drawTag(xPosFun, yPosFun, radiusFun){ctx.beginPath();ctx.arc(xPosFun, yPosFun, radiusFun, 0, Math.PI*2, false);ctx.fillStyle = \"blue\";ctx.fill();ctx.closePath();}function quadradoVerm(xBeg,yBeg,wid,hei){ctx.beginPath();ctx.rect(xBeg,yBeg,wid,hei);ctxfillStyle = \"red\";ctx.fill();}function quadradoAzul(){ctx.beginPath();ctx.rect(160, 10, 100, 40);ctx.strokeStyle = \"cyan\";ctx.stroke();ctx.closePath();}function draw(){ctx.clearRect(0, 0, canvas.width, canvas.height);drawTag(xPos,yPos,radius);drawTag(xPos+25,yPos-55,radius);drawTag(xPos-70,yPos-105,radius);drawTag(xPos+100,yPos,radius);quadradoVerm(canvas.width*0.05,canvas.height*0.05,30,30);quadradoVerm(canvas.width*0.95,canvas.height*0.05,-30,30);quadradoVerm((canvas.width)/2,canvas.height*0.95,-30,-30);}setInterval(draw, 10);</script>\
  <style type=\"text/css\">div.sidebar{width:50px;background-color: rgb(84, 133, 255);height:100%;float:left;position:fixed;z-index:1;top:0;left:0;overflow-x:hidden;padding-top:20px;}div.content{margin-left:70px;padding:0px 10px;float: left;}div.icons{text-align: center;line-height: 100px;}div.boxes{line-height: 60px;text-align: center;}select.select{text-align: center;width: 300px;}div.buttons{text-align: center;}#trackingMap{border-style: dotted;border-color: black;}#titulo{text-align: center;font-size: 50px;font-family: \"Times New Roman\", Times, serif;color: rgb(84, 133, 255);}#start{background-color: rgb(84, 133, 255);}#stop{background-color: rgb(255, 176, 176);}</style>\
  </html>");
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

        // Check to see if the client request was "GET /H" or "GET /L":
        Serial.println(currentLine);
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(13, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(13, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    // client.stop();
    Serial.println("Client Disconnected.");
  }
}