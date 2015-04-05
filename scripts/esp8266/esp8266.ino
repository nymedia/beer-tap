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
  delay(10);
  
  // Run it in dual mode
  WiFi.mode(WIFI_AP_STA);
  
  server.on("/", routerDashboard);
  server.on("/settings", routerSettings);
  server.on("/onewire", routerOneWire);
  server.on("/component/networks", routerNetworks);
  server.on("/component/header", routerHeader);
  server.on("/component/footer", routerFooter);
  server.on("/base.css", routerCss);
  server.on("/base.js", routerJs);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
  
  // Try to connect to default Wi-Fi
  connect(defaultSSID, defaultPassword);
 
  // Print the IP address
  Serial.println(WiFi.softAPIP());
}

// Main loop
void loop() {
  server.handleClient();
  // Reconnect if autoreconnect is TRUE and WiFi network is not connected.
  if (autoreconnect && (WiFi.status() != WL_CONNECTED)) {
    connect(defaultSSID, defaultPassword);
  }
}

