#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// WiFi Definitions
const char* ssid = "Esp8266TestNet"; //"The Whare";  //
const char* password = "Esp8266Test"; // "Bundaberg"; // has to be longer than 7 chars 
const char* value = "";

int ledPin = D2; // GPIO13
WiFiServer server(80);
bool gotWiFiDetails = false;

void setup() {

   Serial.begin(9600);
   delay(10);
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH); // turn on

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password, 1, 0); // last parameter to 1 to hide 
  
   server.begin();

   char* new2_ssid = "";
   char* new2_pass = "";
   //char new_ssid[] = "";
   //char new_pass[] = "";
   
   while(!gotWiFiDetails) {
        // Check of client has connected
      WiFiClient client = server.available();
      
      while(!client) {
        //Serial.print("not working\n");
        client = server.available();
        //return;
      }
    
      // Read the request line
      String request = client.readStringUntil('\r');
      Serial.println(request);
      client.flush();
      
      // Match request
      if(request.indexOf("/led/on") != -1) {
         digitalWrite(ledPin, HIGH);
         value = "on";
      } else if (request.indexOf("/led/off") != -1) {
         digitalWrite(ledPin, LOW);
          value = "off";
      } else if(request.indexOf("/ssid") != -1) {
         Serial.print("found it");
         request.remove(0, request.indexOf("ssid"));
         Serial.print("strip1: ");
         Serial.println(request);
         request.remove(0, request.indexOf("/")+1);
         Serial.print("strip2: ");
         Serial.println(request);
         request.remove(request.indexOf(" "));
         Serial.print("strip3: ");
         Serial.println(request);
         if(request.indexOf("%20") != -1) {
           request.replace("%20", " ");
           Serial.print("replace: ");
           Serial.println(request);
         }
         new2_ssid = request;
         char new_ssid[request.length()];
         request.toCharArray(new_ssid, request.length());
         //new_ssid = str_array;
      } else if(request.indexOf("/password") != -1) {
         Serial.print("found it");
         request.remove(0, request.indexOf("password"));
         Serial.print("strip1: ");
         Serial.println(request);
         request.remove(0, request.indexOf("/")+1);
         Serial.print("strip2: ");
         Serial.println(request);
         request.remove(request.indexOf(" "));
         Serial.print("strip3: ");
         Serial.println(request);
         if(request.indexOf("%20") != -1) {
           request.replace("%20", " ");
           Serial.print("replace: ");
           Serial.println(request);
         }
         new2_pass = request;
         char new_pass[request.length()];
         request.toCharArray(new_pass, request.length());
         //new_pass = new_ssid;
         //Serial.print(str_array[1]);
         //Serial.print(new_pass[1]);
      }
      
      client.flush();
//      char new_ssid[request.length()];
//       new_ssid.toCharArray(new_ssid, new_ssid_temp.length());
//      char new_pass[request.length()];
//       new_pass.toCharArray(new_pass_temp, new_pass_temp.length());
         
      // JSON response
      String s = "HTTP/1.1 200 OK\r\n";
      s += "Content-Type: application/json\r\n\r\n";
      s += "{\"data\":{\"message\":\"success\",\"value\":\"";
      s += value;
      s += "\"}}\r\n";
      s += "\n";
    
      // Send the response to the client
      client.print(s);
      delay(1);
      Serial.println("Client disconnected");
    
      // The client will actually be disconnected when the function returns and the client object is destroyed
      if ((new2_pass != "") && (new2_ssid != "")) {
        gotWiFiDetails = true;
      }
   }
   WiFi.softAPdisconnect (true);
   
   const int  port   = 2390;
   const String REQUEST_LED = "/led";
   const String PARAM_STATE = "state";
   AsyncWebServer server(port);
   Serial.print("\n");
   Serial.print(new2_ssid);
   Serial.print(new2_pass); //????"????? what is that???
   // Serial.print(new_ssid);
   //Serial.print(new_pass);
   
    WiFi.mode(WIFI_STA);
    WiFi.begin(new2_ssid, new2_pass);
    Serial.print("\nConnecting ");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(300);
    }
    Serial.println("");
    Serial.print("WiFi connected to: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


}

void loop() {
  
}
