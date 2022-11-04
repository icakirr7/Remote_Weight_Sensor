 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
 #include <WiFiClient.h>
 #include "HX711.h"
 #include <ESP8266WebServer.h>
 ESP8266WebServer server(80);
const char* ssid     = "Yordam";
const char* password = "1029384756yT";
const char* serverName = "http://192.168.1.49/loadcell/post-esp-data.php";

String apiKeyValue = "tPmAT5Ab3j7F9";
float val1;
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;
HX711 scale;


String data;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); 
  scale.set_scale(-1994.63);
  
  scale.tare();   
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // (you can also pass in a Wire library object like &Wire2)

}

void loop() {
  // put your main code here, to run repeatedly:
if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    
    http.begin(client, serverName);
    
    
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    val1=scale.get_units();

    data=(String)val1;
    
   
    String httpRequestData = "api_key=" + apiKeyValue+ "&value1=" + String(data)+ "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
 
    int httpResponseCode = http.POST(httpRequestData);
  
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(1000); 
  
}
