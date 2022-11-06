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
            client.println("<html>");
            client.println("<head><meta content = \"width=device-width, initial-scale=1\">");
            client.println("<style>html{margin:0px auto; text-align:center;}");
            client.println(".botao_on {background-color: #00FF00; color: black; padding: 15px 40px; border-radius: 25px;}");
            client.println(".botao_off {background-color: #FF0000; color: white; padding: 15px 40px; border-radius: 25px;}</style></head>");

            client.println("<body><h1>Indoor positioning system - ATECH </h1>");
            client.println("<form><label>Escolha a tag para localizar:</label><select><option>Tag1</option><option>Tag2</option></select></form>");
            client.print("<p><a href=\"/H\"><button class=\"botao_on\">Ativar rastreamento</button></a></p>");
            client.print("<p><a href=\"/L\"><button class=\"botao_off\">Desativar rastreamento</button></a></p>");
            client.println("</body></html>");
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
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(13, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(13, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}