#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "arduino_secret.h"

#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "redirect1.h"

#define LED D4

ESP8266WebServer server(80);

void handleRoot() {
  Serial.println("GET /");
  server.send(200, "text/html", htmlPage1);
}

void handlePage2() {
  Serial.println("GET /test");
  server.send(200, "text/html", htmlPage2);
}

void handlePage3() {
  Serial.println("GET /test2");
  server.send(200, "text/html", htmlPage3);
}

void handlePage4() {
  Serial.println("GET /youtube");
  server.send(200, "text/html", htmlRedirect1);
}

void setup(void){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED, HIGH);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/test", handlePage2);
  server.on("/test2", handlePage3);
  server.on("/youtube", handlePage4);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
  delay(2000);            // wait for 1 second.
  digitalWrite(LED, LOW); // turn the LED on.
  delay(40); // wait for 1 second
}
