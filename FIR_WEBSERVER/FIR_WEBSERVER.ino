 //the following code is for FIR filter whose output will be shown on webserver
  
  
  
  #include <Arduino.h>
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "esp_wpa2.h"
  #include <SPIFFS.h>



#define EAP_ANONYMOUS_IDENTITY "anonymous@example.com"
#define EAP_IDENTITY "17EE10012"
#define EAP_PASSWORD "lionel10messi"
const char* ssid = "CAMPUS_SECURED"; // Eduroam SSID




  AsyncWebServer server(80);



   float filter[21]={-0.0017  , -0.0006 ,   0.0063 ,   0.0125 ,   0.0015 ,  -0.0301 ,  -0.0491 ,  -0.0024 ,   0.1249  , 0.2711 ,   0.3361 ,   0.2711  ,  0.1249 ,  -0.0024  , -0.0491 ,   -0.0301 ,   0.0015 ,   0.0125,   0.0063  , -0.0006 ,  -0.0017 }   ;         
   float x[20];
   float m=0;
   float dt=1.0/8000;
   double k,y;


      void shift(){
           for(int q=20;q>=0;q--)
             x[q+1]=x[q];
           x[0]=k;
       }


      String filtering( ){

           for(int q=0;q<22;q++)
             y+=filter[q]*x[q];
      return String(y);
         }

       String sinwave(){
          
            k=sin(6.28*50*m);
            m+=dt;
        
            //Serial.println(k);
            delay(50);
            if(m>10) m=0;

            return String(k);
          
       }
  
  
  void setup(){
   
    Serial.begin(115200);
    
    // Initialize SPIFFS...................
    
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
    //.....................................

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY)); 
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
    esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
   
 
    
    WiFi.begin(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
   

      
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/index.html");
        });
        server.on("/input", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send_P(200, "text/plain", sinwave().c_str());
        });
        server.on("/output", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send_P(200, "text/plain", filtering().c_str());
        });
      
        server.begin();
}
 
void loop(){
    sinwave();
    filtering();
    shift();
  
}
