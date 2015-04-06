#include <OneWire.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "esp8266.h"
#include "requestWrapper.h"
#include "components.h"
#include "router.h"
 
// Prepare module settings
void setup() {
  Serial.begin(9600);
  
  // Run it in dual mode
  WiFi.mode(WIFI_AP_STA);
  
  routerPaths();
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
  
  // Try to connect to default Wi-Fi
  connect(defaultSSID, defaultPassword);
 
  // Print the IP address
  Serial.println(WiFi.softAPIP());
  
  // Retrive MAC address
  WiFi.softAPmacAddress(mac);
}

// Main loop
void loop() {
  server.handleClient();
  // Reconnect if autoreconnect is TRUE and WiFi network is not connected.
  if (autoreconnect && (WiFi.status() != WL_CONNECTED)) {
    connect(defaultSSID, defaultPassword);
  }
}

