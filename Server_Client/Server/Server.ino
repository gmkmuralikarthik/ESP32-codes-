// the following is the code for server
//this code sends string "HI" to connected client

#include "WiFi.h"
#include "ESPAsyncWebServer.h"


const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";



AsyncWebServer server(80);


String Send_data() {
  return String("HI");
}

void setup(){

  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);


  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", Send_data().c_str());
  });

  server.begin();
}
 
void loop(){
  
}
