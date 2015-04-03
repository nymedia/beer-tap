#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "requestWrapper.h"
 
#define max_attempts 10
#define MAX_WIFI_LENGTH 50 

char defaultSSID[MAX_WIFI_LENGTH]     = "default-ssid";
char defaultPassword[MAX_WIFI_LENGTH] = "default-password";
 
char ap_ssid[MAX_WIFI_LENGTH] = "esp-rev2";
char ap_password[MAX_WIFI_LENGTH] = "security";
 
// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
  
  // Run it in dual mode
  WiFi.mode(WIFI_AP_STA);
  
  
  server.on("/", routerDashboard);
  server.on("/networks", routerNetworks);
  server.on("/onewire", routerOneWire);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
  
  // Try to connect to default Wi-Fi
  connect(defaultSSID, defaultPassword);
 
  // Print the IP address
  Serial.println(WiFi.softAPIP());
}
 
bool connect(char ssid[], char password[]) {
  // Disconnect
  WiFi.disconnect();  
  
  // Set AP
  WiFi.softAP(ap_ssid, ap_password);
  
  int attempts = 0;
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED && attempts < max_attempts) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
 
  Serial.println("");
 
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }
  else {
    Serial.println("WiFi connected");
    return true;
  }
}

void loop() {
  server.handleClient();
}

void routerDashboard() {
  String s = "Hello World!";
  server.send(200, "text/html", htmlDocument(s));
}

void routerNetworks() {
  String s = "";
  
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  if (ssid.length() && password.length()) {
    char buffSSID[MAX_WIFI_LENGTH];
    char buffPassword[MAX_WIFI_LENGTH];
    ssid.toCharArray(buffSSID, MAX_WIFI_LENGTH);
    password.toCharArray(buffPassword, MAX_WIFI_LENGTH);
    if (!connect(buffSSID, buffPassword)) {
      connect(defaultSSID, defaultPassword);
      s += "<div class='row'><div class='col s12 m5'><div class='card-panel red'><span class='white-text'>Unable to connect to network. Connecting to default one instead.</span></div></div></div>";
    }
    else {
      strcpy(buffSSID, defaultSSID);
      strcpy(buffPassword, defaultPassword);
      s += "<div class='row'><div class='col s12 m5'><div class='card-panel teal'><span class='white-text'>Connected to new network.</span></div></div></div>";
    }
  }
  
  s += "<h1>Connect to network:</h1>";
  s += "<div class='row'><form class='col s12' method='post'>";
  s += "<div class='row'><div class='input-field col s6'><input placeholder='SSID' id='ssid' name='ssid' type='text' class='validate'><label for='ssid'>SSID</label></div>";
  s += "<div class='input-field col s6'><input id='password' name='password' type='password' class='validate'><label for='password'>Password</label></div></div>";
  s += "<div class='row'><button class='btn waves-effect waves-light' type='submit' name='action'>Submit<i class='mdi-content-send right'></i></button></div>";
  s += "</form></div>";
  server.send(200, "text/html", htmlDocument(s));
}

void routerOneWire() {
  String s = "";
  server.send(200, "text/html", htmlDocument(s));
}

