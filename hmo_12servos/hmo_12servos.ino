
#include <WiFi.h>
#include <Servo.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "esp_wpa2.h"



#define EAP_ANONYMOUS_IDENTITY "anonymous@example.com"
#define EAP_IDENTITY "17EE10012"
#define EAP_PASSWORD "lionel10messi"
const char* ssid = "CAMPUS_SECURED"; // Eduroam SSID





Servo myservo;  
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo myservo9;
Servo myservo10;
Servo myservo11;
// create servo object to control a servo
// twelve servo objects can be created on most boards

// GPIO the servo is attached to
static const int servoPin = 13;
static const int servoPin1 = 22;
static const int servoPin2 = 16;
static const int servoPin3 = 17;
static const int servoPin4 = 18;
static const int servoPin5 = 19;
static const int servoPin6 = 21;
static const int servoPin7 = 22;
static const int servoPin8 = 23;
static const int servoPin9 = 25;
static const int servoPin10 = 26;
static const int servoPin11 = 27;
// Replace with your network credentials


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(5);
String valueString1 = String(5);
String valueString2 = String(5);
String valueString3 = String(5);
String valueString4 = String(5);
String valueString5 = String(5);
String valueString6 = String(5);
String valueString7 = String(5);
String valueString8 = String(5);
String valueString9 = String(5);
String valueString10 = String(5);
String valueString11 = String(5);
int pos1[11] ;
int pos2[11] ;

void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin);  
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  myservo3.attach(servoPin3);
  myservo4.attach(servoPin4);
  myservo5.attach(servoPin5);
  myservo6.attach(servoPin6);
  myservo7.attach(servoPin7);
  myservo8.attach(servoPin8);
  myservo9.attach(servoPin9);
  myservo10.attach(servoPin10);
  myservo11.attach(servoPin11);
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
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
 
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }");
            client.println(".slider1 {width: 300px } </style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // Web Page
            client.println("<centre></head><body><h1>ESP32 with Servo</h1></centre>");
            
            client.println("<centre><p>Position: <span id=\"servoPos\"></span></p></centre>");    
                  
            client.println("motor 0<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value  )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos1\"></span></p></centre>");   
            client.println("motor 1<input type=\"range\" min=\"0\" max=\"180\" class=\"slider1\" id=\"servoSlider1\" onchange=\"servo1(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos2\"></span></p></centre>");   
            client.println("motor 2<input type=\"range\" min=\"0\" max=\"180\" class=\"slider2\" id=\"servoSlider2\" onchange=\"servo2(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos3\"></span></p></centre>");   
            client.println("motor 3<input type=\"range\" min=\"0\" max=\"180\" class=\"slider3\" id=\"servoSlider3\" onchange=\"servo3(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos4\"></span></p></centre>");   
            client.println("motor 4<input type=\"range\" min=\"0\" max=\"180\" class=\"slider4\" id=\"servoSlider4\" onchange=\"servo4(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos5\"></span></p></centre>");   
            client.println("motor 5<input type=\"range\" min=\"0\" max=\"180\" class=\"slider5\" id=\"servoSlider5\" onchange=\"servo5(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos6\"></span></p></centre>");   
            client.println("motor 6<input type=\"range\" min=\"0\" max=\"180\" class=\"slider6\" id=\"servoSlider6\" onchange=\"servo6(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos7\"></span></p></centre>");   
            client.println("motor 7<input type=\"range\" min=\"0\" max=\"180\" class=\"slider7\" id=\"servoSlider7\" onchange=\"servo7(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos8\"></span></p></centre>");   
            client.println("motor 8<input type=\"range\" min=\"0\" max=\"180\" class=\"slider8\" id=\"servoSlider8\" onchange=\"servo8(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos9\"></span></p></centre>");   
            client.println("motor 9<input type=\"range\" min=\"0\" max=\"180\" class=\"slider9\" id=\"servoSlider9\" onchange=\"servo9(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos10\"></span></p></centre>");   
            client.println("motor 10<input type=\"range\" min=\"0\" max=\"180\" class=\"slider10\" id=\"servoSlider10\" onchange=\"servo10(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
             client.println("<centre><p>Position: <span id=\"servoPos11\"></span></p></centre>");   
            client.println("motor 11<input type=\"range\" min=\"0\" max=\"180\" class=\"slider11\" id=\"servoSlider11\" onchange=\"servo11(this.value )\" value=\""+valueString+"\"/>");
            client.println("<br>");
        

          
            
            client.println("<iframe src =\"http://10.105.33.219:8000/index.html\" width=\"700\" height=\"550\" style=\"border:none\"> </iframe>");


            
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
           
            client.println("var slider1 = document.getElementById(\"servoSlider1\");");
            client.println("var servoP1 = document.getElementById(\"servoPos1\"); servoP1.innerHTML = slider1.value;");
            client.println("slider1.oninput = function() { slider1.value = this.value; servoP1.innerHTML = this.value; }");

            client.println("var slider2 = document.getElementById(\"servoSlider2\");");
            client.println("var servoP2 = document.getElementById(\"servoPos2\"); servoP2.innerHTML = slider2.value;");
            client.println("slider2.oninput = function() { slider2.value = this.value; servoP2.innerHTML = this.value; }");


client.println("var slider3 = document.getElementById(\"servoSlider3\");");
            client.println("var servoP3 = document.getElementById(\"servoPos3\"); servoP3.innerHTML = slider3.value;");
            client.println("slider3.oninput = function() { slider3.value = this.value; servoP3.innerHTML = this.value; }");


client.println("var slider4 = document.getElementById(\"servoSlider4\");");
            client.println("var servoP4 = document.getElementById(\"servoPos4\"); servoP4.innerHTML = slider4.value;");
            client.println("slider4.oninput = function() { slider4.value = this.value; servoP4.innerHTML = this.value; }");


client.println("var slider5 = document.getElementById(\"servoSlider5\");");
            client.println("var servoP5 = document.getElementById(\"servoPos5\"); servoP5.innerHTML = slider5.value;");
            client.println("slider5.oninput = function() { slider5.value = this.value; servoP5.innerHTML = this.value; }");


client.println("var slider6 = document.getElementById(\"servoSlider6\");");
            client.println("var servoP6 = document.getElementById(\"servoPos6\"); servoP6.innerHTML = slider6.value;");
            client.println("slider6.oninput = function() { slider6.value = this.value; servoP6.innerHTML = this.value; }");


client.println("var slider7 = document.getElementById(\"servoSlider7\");");
            client.println("var servoP7 = document.getElementById(\"servoPos7\"); servoP7.innerHTML = slider7.value;");
            client.println("slider7.oninput = function() { slider7.value = this.value; servoP7.innerHTML = this.value; }");

client.println("var slider8 = document.getElementById(\"servoSlider8\");");
            client.println("var servoP8 = document.getElementById(\"servoPos8\"); servoP8.innerHTML = slider8.value;");
            client.println("slider8.oninput = function() { slider8.value = this.value; servoP8.innerHTML = this.value; }");

client.println("var slider9 = document.getElementById(\"servoSlider9\");");
            client.println("var servoP9 = document.getElementById(\"servoPos9\"); servoP9.innerHTML = slider9.value;");
            client.println("slider9.oninput = function() { slider9.value = this.value; servoP9.innerHTML = this.value; }");

client.println("var slider10 = document.getElementById(\"servoSlider10\");");
            client.println("var servoP10 = document.getElementById(\"servoPos10\"); servoP10.innerHTML = slider10.value;");
            client.println("slider10.oninput = function() { slider10.value = this.value; servoP10.innerHTML = this.value; }");

client.println("var slider11 = document.getElementById(\"servoSlider11\");");
            client.println("var servoP11 = document.getElementById(\"servoPos11\"); servoP11.innerHTML = slider11.value;");
            client.println("slider11.oninput = function() { slider11.value = this.value; servoP11.innerHTML = this.value; }");









            
//client.println("</script>");






              client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value=\" + pos + \"&\");{Connection: close}; }");
// Serial.println("HI7");
            client.println("$.ajaxSetup({timeout:1000}); function servo2(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value2=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo3(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value3=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo4(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value4=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo5(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value5=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo6(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value6=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo7(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value7=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo8(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value8=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo9(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value9=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo10(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value10=\" + pos + \"&\");{Connection: close}; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo11(pos) { ");
       //     client.println("if(servo.id==\"servoSlider1\"){");
            client.println("$.get(\"/?value11=\" + pos + \"&\");{Connection: close}; }");
          client.println("$.ajaxSetup({timeout:1000}); function servo1(pos) { ");
          // client.println("else if(servo.id==\"servoSlider\"){");
            client.println("$.get(\"/?value1=\" + pos + \"&\" ); {Connection: close};}</script>");

           

           
            client.println("</body></html>");     

Serial.println("HI");
            
        //     if (header.indexOf("GET /?d=")==5) {
            if(header.indexOf("GET /?value=")>=0) {
              pos1[0] = header.indexOf('=');
              pos2[0] = header.indexOf('&');
              valueString = header.substring(pos1[0]+1, pos2[0]);
              
              //Rotate the servo
              myservo.write(valueString.toInt());
        //      Serial.println(valueString); 
       //        Serial.println("HI1");
      //
        //    }
             }
         //    else if (header.indexOf("GET /?id=")==1) {
            else if(header.indexOf("GET /?value1=")>=0) {
              pos1[1] = header.indexOf('=');
              pos2[1] = header.indexOf('&');
              valueString1 = header.substring(pos1[1]+1, pos2[1]);
              
              //Rotate the servo
              myservo1.write(valueString1.toInt());
            //  Serial.println(valueString1); 
              
             //  Serial.println("HI4");
         
            }  
            else if(header.indexOf("GET /?value2=")>=0) {
              pos1[2] = header.indexOf('=');
              pos2[2] = header.indexOf('&');
              valueString2 = header.substring(pos1[2]+1, pos2[2]);
              
              //Rotate the servo
              myservo2.write(valueString2.toInt());
             // Serial.println(valueString1); 
              
             //  Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value3=")>=0) {
              pos1[3] = header.indexOf('=');
              pos2[3] = header.indexOf('&');
              valueString3 = header.substring(pos1[3]+1, pos2[3]);
              
              //Rotate the servo
              myservo3.write(valueString3.toInt());
             // Serial.println(valueString3); 
              
         //      Serial.println("HI4");
         
            }                              
            else if(header.indexOf("GET /?value4=")>=0) {
              pos1[4] = header.indexOf('=');
              pos2[4] = header.indexOf('&');
              valueString4 = header.substring(pos1[4]+1, pos2[4]);
              
              //Rotate the servo
              myservo4.write(valueString4.toInt());
           //   Serial.println(valueString4); 
              
  //             Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value5=")>=0) {
              pos1[5] = header.indexOf('=');
              pos2[5] = header.indexOf('&');
              valueString5 = header.substring(pos1[5]+1, pos2[5]);
              
              //Rotate the servo
              myservo5.write(valueString5.toInt());
      //        Serial.println(valueString5); 
              
       //        Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value6=")>=0) {
              pos1[6] = header.indexOf('=');
              pos2[6] = header.indexOf('&');
              valueString6 = header.substring(pos1[6]+1, pos2[6]);
              
              //Rotate the servo
              myservo6.write(valueString6.toInt());
        //      Serial.println(valueString6); 
              
        //       Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value7=")>=0) {
              pos1[7] = header.indexOf('=');
              pos2[7] = header.indexOf('&');
              valueString7 = header.substring(pos1[7]+1, pos2[7]);
              
              //Rotate the servo
              myservo7.write(valueString7.toInt());
          //    Serial.println(valueString7); 
              
          //     Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value8=")>=0) {
              pos1[8] = header.indexOf('=');
              pos2[8] = header.indexOf('&');
              valueString8 = header.substring(pos1[8]+1, pos2[8]);
              
              //Rotate the servo
              myservo8.write(valueString8.toInt());
              Serial.println(valueString8); 
         //     
        //       Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value9=")>=0) {
              pos1[9] = header.indexOf('=');
              pos2[9] = header.indexOf('&');
              valueString9 = header.substring(pos1[9]+1, pos2[9]);
              
              //Rotate the servo
              myservo9.write(valueString9.toInt());
           //   Serial.println(valueString9); 
              
          //     Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value10=")>=0) {
              pos1[10] = header.indexOf('=');
              pos2[10] = header.indexOf('&');
              valueString10 = header.substring(pos1[10]+1, pos2[10]);
              
              //Rotate the servo
              myservo10.write(valueString10.toInt());
            //  Serial.println(valueString10); 
              
            //   Serial.println("HI4");
         
            }
            else if(header.indexOf("GET /?value11=")>=0) {
              pos1[11] = header.indexOf('=');
              pos2[11] = header.indexOf('&');
              valueString11 = header.substring(pos1[11]+1, pos2[11]);
              
              //Rotate the servo
              myservo11.write(valueString11.toInt());
           //   Serial.println(valueString1); 
              
           //    Serial.println("HI4");
         
            }
        // The HTTP response ends with another blank line// The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
