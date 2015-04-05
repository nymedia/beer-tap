// Define static values 
#define MAX_ATTEMPTS 10
#define MAX_WIFI_LENGTH 50 

// Connect to network
char defaultSSID[MAX_WIFI_LENGTH]     = "default-ssid";
char defaultPassword[MAX_WIFI_LENGTH] = "default-password";

// Internal network
char apSSID[MAX_WIFI_LENGTH] = "esp-rev2";
char apPassword[MAX_WIFI_LENGTH] = "security";

// Other options
bool autoreconnect = true;

// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);

// Connect to selected network.
bool connect(char ssid[], char password[]) {
  // Disconnect
  WiFi.disconnect();  
  
  // Set AP
  WiFi.softAP(apSSID, apPassword);
  
  int attempts = 0;
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
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
