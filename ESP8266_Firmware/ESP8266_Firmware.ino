#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
//#include "FS.h"
#include <WebSocketsServer.h>
#include <Hash.h>

WebSocketsServer webSocket = WebSocketsServer(81);

const char* ssid = "ControlRelays";
const char* password = "123456789";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
//ESP8266WebServer server(80);


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

    switch(type) {
        case WStype_DISCONNECTED:
            
            break;
        case WStype_CONNECTED:
         {
                IPAddress ip = webSocket.remoteIP(num);
                
                
            }
            break;
        case WStype_TEXT:
        {
            
            String text = String((char *) &payload[0]);
          if(text=="1"){
            Serial.println("Relé 1 encendido");
            digitalWrite(0,HIGH);
            }
            if(text=="2"){
            Serial.println("Relé 2 encendido");
            digitalWrite(2,HIGH);
            }
             if(text=="3"){
            Serial.println("Relé 1 apagado");
            digitalWrite(0,LOW);
            }
            if(text=="4"){
            Serial.println("Relé 2 apagado");
            digitalWrite(2,LOW);
            }
            if(text=="5"){
            Serial.println("Relé 1 y 2 encendidos");
            digitalWrite(0,HIGH);
            digitalWrite(2,HIGH);
            }
             if(text=="6"){
            Serial.println("Relé 1 y 2 apagados");
            digitalWrite(0,LOW);
            digitalWrite(2,LOW);
            }
            
            
            

                            
                   }
            
           
           webSocket.sendTXT(num, payload, lenght);
            webSocket.broadcastTXT(payload, lenght);
            break;
        
        case WStype_BIN:
     
            hexdump(payload, lenght);

            // echo data back to browser
            webSocket.sendBIN(num, payload, lenght);
            break;
    }

}


void setup() {
  Serial.println("Inicio de servidor");
  Serial.print("SSID: ");
  Serial.print(ssid);
  Serial.print("Password: ");
  Serial.println(password);

//Inicializacion de pines
  Serial.begin(9600);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
 

//Inicio de Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  delay(100);
  server.begin();
  delay(1000);
  Serial.println("Inicio de servidor completado");

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  delay(100);
}

void loop() {
  // Se revisa si un cliente se ha conectado
  webSocket.loop();

  /*
  WiFiClient client = server.available();
  
  if (!client){
    delay(10);
    return;
    
  }
  else{
  
  
  // Read the first line of the request
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val1;
  int val2;
  
  if (req.indexOf("/gpio/0") != -1){
    val1 = 0;
  }
   
  else if (req.indexOf("/gpio/1") != -1){
    val1 = 1;
  }
  else if (req.indexOf("/gpio/2") != -1){
    val2 = 0;
  }
  else if (req.indexOf("/gpio/3") != -1){
    val2 = 1;
  }
  else if (req.indexOf("/gpio/4") != -1){
    val1 = 0;
    val2 = 0;
  }
  else if (req.indexOf("/gpio/5") != -1){
    val1 = 1;
    val2 = 1;
  }
  else {
    Serial.println("Petición inválida");
    client.print("HTTP/1.1 404\r\n");
    client.stop();
    return;
  }

  //Set del valor recibido
  digitalWrite(0,val1);
  digitalWrite(2,val2);
    
  
  

  // Set GPIOX according to the request
  //digitalWrite(2,val1);
  //digitalWrite(0,val2);

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nRelé 1 está en";
  s += (val1)?"high":"low";
  s += "</html>\n";
  s += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nRelé 2 está en";
  s += (val2)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(10);
  Serial.println("Cliente desconectado");

  }
  */

}



