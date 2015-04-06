String componentHeader() {
  
  // Strart header.
  String s = "<header>";
  if (WiFi.status() == WL_CONNECTED) {
    s += "<div class='strength'>";
    long rssi = getRSSI(defaultSSID);
    s += getStrengthIcon(rssi);
    s += "</div>";
    s += "<div>IP: ";
    s += getIP();
    s += "</div>";
    s += "<div>SSID: ";
    s += WiFi.SSID();
    s += "</div>";
  }
  else {
    s += getIcon(1);
  }
  
  s += "<h1 class='brand-title'>";
  s += getMacAddress();
  
  s += "</h1><h2 class='brand-tagline'>Manage device</h2>";
  
  // Navigation
  s += "<nav class='nav'>";
  s += "<div class='pure-menu'><ul class='pure-menu-list'>";
  s += "<li class='pure-menu-item'><a href='/' class='pure-menu-link'>Dashboard</a></li>";
  s += "<li class='pure-menu-item'><a href='/onewire' class='pure-menu-link'>OneWire</a></li>";
  s += "<li class='pure-menu-item'><a href='/settings' class='pure-menu-link'>Settings</a></li>";
  s += "</ul></div>";
  s += "</nav>";
  
  s += "</header>";

  return s;
}

String componentFooter() {
  String s = "";
  
  // Footer
  s += "<footer class='page-footer'>";
  s += "<div class='pure-menu pure-menu-horizontal'><ul>";
  s += "<li class='pure-menu-item'><a href='http://nymedia.no' class='pure-menu-link'>Ny Media AS</a></li>";
  s += "</ul></div>";
  s += "</footer>";
  
  return s;
}

String componentAvailableNetworks() {
  String s = ""; 
  s += "<table class='pure-table'><thead><tr><th>SSID</th><th>Strength</th><th>Secured?</th></tr></thead>";
  s += "<tbody>";
  int n = WiFi.scanNetworks();
  if (n == 0) {
    s += "<tr><td colspan='2'>No networks found</td></tr>";
  }
  else {
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      s += "<tr><td>";
      s += WiFi.SSID(i);
      s += "</td><td>";   
      s += WiFi.RSSI(i);
      s += "</td><td>";
      s += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "Yes";
      s += "</td></tr>";
    }
  }
  s += "</tbody></table>";
  return s;
}

String componentAvailableSensors() {
  String s = "";
  s += "<table class='pure-table'><thead><tr><th>ID</th><th>Chip</th><th>Value</th></tr></thead>";
  s += "<tbody>";
  byte addr[8];
  while (ds.search(addr)) {
    s += "<tr><td>";
    s += getOneWireAddress(addr);
    s += "</td><td>";
    s += getOneWireChip(addr);
    s += "</td><td>";
    // @todo: Make it universal - including DHT11/22 family.
    s += getTemperature(addr);
    s += "</td></tr>";
  }
  s += "</tbody></table>";
  return s;
}
