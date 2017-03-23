
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char* ssid = "Porton";
const char* password = "123456789";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
//ESP8266WebServer server(80);


void handleRoot() {
//  server.send(200, "text/html", "<h1>Estas conectado.</h1>");
}

void setup() {
  Serial.println("Inicio de servidor");
  Serial.print("SSID: ");
  Serial.print(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  initHardware();
  setupWiFi();
  server.begin();
  delay(1000);
  Serial.println("Inicio de servidor completado");
  
}

void loop() {
  // Se revisa si un cliente se ha conectado
  
  WiFiClient client = server.available();
  if (!client) {
    delay(100);
    return;
  }

  
  // Read the first line of the request
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val1;
  int val2;
  if (req.indexOf("/gpio/0") != -1){
    val1 = 0;
    val2 = 0;
  }
   
  else if (req.indexOf("/gpio/1") != -1){
    val1 = 1;
    val2 = 1;
  }
    
  else if (req.indexOf("/gpio/2") != -1)
   val1 = (!digitalRead(2)); 
   else if (req.indexOf("/gpio/3") != -1)
   val2 = (!digitalRead(0));
   
  else {
    Serial.println("invalid request");
    client.print("HTTP/1.1 404\r\n");
    client.stop();
    return;
  }

  // Set GPIOX according to the request
  digitalWrite(2,val1);
  digitalWrite(0,val2);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nRelé está en";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Cliente desconectado");




void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(ssid,password);
}

void initHardware()
{
  Serial.begin(115200);
  //pinMode(DIGITAL_PIN, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
}

