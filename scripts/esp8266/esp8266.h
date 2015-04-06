// Define static values
#define MAX_ATTEMPTS 10
#define MAX_WIFI_LENGTH 50

// Connect to network
char defaultSSID[MAX_WIFI_LENGTH]     = "default-ssid";
char defaultPassword[MAX_WIFI_LENGTH] = "default-password";

// Internal network
char apSSID[MAX_WIFI_LENGTH] = "esp-rev2";
char apPassword[MAX_WIFI_LENGTH] = "security";
byte mac[6];

// Other options
bool autoreconnect = true;

// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);

// OneWire line
OneWire  ds(0);

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

String getIP() {
  IPAddress ip = WiFi.localIP();
  return String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
}

String getMacAddress() {
  return String(mac[5], HEX) + ":" + String(mac[4], HEX) + ":" + String(mac[3], HEX) + ":" + String(mac[2], HEX) + ":" + String(mac[1], HEX) + ":" + String(mac[0], HEX);
}

long getRSSI(char* ssid) {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    return 0;
  }
  else {
    for (int i = 0; i < n; ++i) {
      const char* tmpSSID = WiFi.SSID(i);
      if (strcmp(tmpSSID, ssid) == 0) {
        return WiFi.RSSI(i);
      }
    }
  }
  return -1;
}

/**
 * 1 - wifi off
 * 2 - wifi 4 bars
 * 3 - wifi 3 bars
 * 4 - wifi 2 bars
 * 5 - wifi 1 bars
 * 6 - wifi 0 bars
 * 7 - secure
 * 8 - refresh
 * 9 - 
 * 10 - 
 * 11 - 
 * 12 - 
 * 13 - 
 * 14 - 
 * 15 - 
 * 16 - 
 * 17 - 
 * 18 - 
 * 19 - 
 * 20 - 
 * 21 - 
 * 22 - 
 * 23 - 
 * 24 - 
 */
String getIcon(byte choose) {
  String s = "";
  switch (choose) {
    case 1:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'><path d='M0 0h24v24h-24z' fill='none'/><path d='M23.64 7c-.45-.34-4.93-4-11.64-4-1.5 0-2.89.19-4.15.48l10.33 10.32 5.46-6.8zm-6.6 8.22l-13.77-13.78-1.27 1.28 2.05 2.06c-2.14.98-3.46 2.04-3.69 2.22l11.63 14.49.01.01.01-.01 3.9-4.86 3.32 3.32 1.27-1.27-3.46-3.46z'/></svg>";
      break;
    
    case 2:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path d='M12.01 21.49l11.63-14.49c-.45-.34-4.93-4-11.64-4-6.72 0-11.19 3.66-11.64 4l11.63 14.49.01.01.01-.01z'/> <path d='M0 0h24v24h-24z' fill='none'/> </svg>";
      break;
    
    case 3:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path fill-opacity='.3' d='M12.01 21.49l11.63-14.49c-.45-.34-4.93-4-11.64-4-6.72 0-11.19 3.66-11.64 4l11.63 14.49.01.01.01-.01z'/> <path d='M0 0h24v24h-24z' fill='none'/> <path d='M3.53 10.95l8.46 10.54.01.01.01-.01 8.46-10.54c-.43-.33-3.66-2.95-8.47-2.95-4.81 0-8.04 2.62-8.47 2.95z'/> </svg>";
      break;
    
    case 4:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path fill-opacity='.3' d='M12.01 21.49l11.63-14.49c-.45-.34-4.93-4-11.64-4-6.72 0-11.19 3.66-11.64 4l11.63 14.49.01.01.01-.01z'/> <path d='M0 0h24v24h-24z' fill='none'/> <path d='M4.79 12.52l7.2 8.98h.01l.01-.01 7.2-8.98c-.36-.27-3.11-2.51-7.21-2.51s-6.85 2.24-7.21 2.52z'/> </svg>";
      break;
    
    case 5:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path fill-opacity='.3' d='M12.01 21.49l11.63-14.49c-.45-.34-4.93-4-11.64-4-6.72 0-11.19 3.66-11.64 4l11.63 14.49.01.01.01-.01z'/> <path d='M0 0h24v24h-24z' fill='none'/> <path d='M6.67 14.86l5.33 6.63v.01l.01-.01 5.33-6.63c-.28-.21-2.31-1.86-5.34-1.86s-5.06 1.65-5.33 1.86z'/> </svg>";
      break;
    
    case 6:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path fill-opacity='.3' d='M12.01 21.49l11.63-14.49c-.45-.34-4.93-4-11.64-4-6.72 0-11.19 3.66-11.64 4l11.63 14.49.01.01.01-.01z'/> <path d='M0 0h24v24h-24z' fill='none'/> </svg>";
      break;
    
    case 7:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path d='M12 1l-9 4v6c0 5.55 3.84 10.74 9 12 5.16-1.26 9-6.45 9-12v-6l-9-4zm0 10.99h7c-.53 4.12-3.28 7.79-7 8.94v-8.93h-7v-5.7l7-3.11v8.8z'/> <path d='M0 0h24v24h-24z' fill='none'/> </svg>";
      break;
    
    case 8:
      s += "<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'> <path d='M17.65 6.35c-1.45-1.45-3.44-2.35-5.65-2.35-4.42 0-7.99 3.58-7.99 8s3.57 8 7.99 8c3.73 0 6.84-2.55 7.73-6h-2.08c-.82 2.33-3.04 4-5.65 4-3.31 0-6-2.69-6-6s2.69-6 6-6c1.66 0 3.14.69 4.22 1.78l-3.22 3.22h7v-7l-2.35 2.35z'/> <path d='M0 0h24v24h-24z' fill='none'/> </svg>";
      break;
    
    case 9:
      s += "";
      break;
    
    case 10:
      s += "";
      break;
    
    case 11:
      s += "";
      break;
    
    case 12:
      s += "";
      break;
    
    case 13:
      s += "";
      break;
    
    case 14:
      s += "";
      break;
    
    case 15:
      s += "";
      break;
    
    case 16:
      s += "";
      break;
    
    case 17:
      s += "";
      break;
    
    case 18:
      s += "";
      break;
    
    case 19:
      s += "";
      break;
    
    case 20:
      s += "";
      break;
    
    case 21:
      s += "";
      break;
    
    case 22:
      s += "";
      break;
    
    case 23:
      s += "";
      break;
    
    case 24:
      s += "";
      break;
  }
  return s;
}

String getStrengthIcon(long rssi) {
  if (rssi == 0 || rssi == -1) {    
    return getIcon(1);
  }
  else if (rssi > -60) {
    return getIcon(2);
  }
  else if (rssi > -70) {
    return getIcon(3);
  }
  else if (rssi > -80) {
    return getIcon(4);
  }
  else if (rssi > -90) {
    return getIcon(5);
  }
  else {
    return getIcon(6);
  }
}

float getTemperature(byte addr[8]) {
  byte type_s;
  byte data[12];
  
  ds.select(addr);
  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -127;
  }
  
    // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      type_s = 1;
      break;
    case 0x28:
      type_s = 0;
      break;
    case 0x22:
      type_s = 0;
      break;
    default:
      return -127;
  } 
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad
  
  delay(100);
  
  for (int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
   // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  return (float)raw / 16.0;
}

String getOneWireChip(byte addr[8]) {
  String s;
  switch (addr[0]) {
  case 0x10:
    s += "DS18S20";
    break;
  case 0x28:
    s += "DS18B20";
    break;
  case 0x22:
    s += "DS1822";
    break;
  default:
    s += "Unsupported device";
  } 
  return s;
}

String getOneWireAddress(byte addr[8]) {
  String s;
  for(int i = 0; i < 8; i++) {
    if (i > 0) {
      s += ":";
    }
    // @todo: add leading zeroes
    s += String(addr[i], HEX);
  }
  return s;
}
