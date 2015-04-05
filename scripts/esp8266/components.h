String componentHeader() {
  String s = "";
  
  // Navbar
  s += "<div class='navbar'><nav><div class='nav-wrapper container'><a href='/' class='brand-logo'>Manage device</a><ul class='right'><li>";
  if (WiFi.status() == WL_CONNECTED) {
    s += "<a class='tooltipped' data-position='bottom' data-delay='50' data-tooltip='";
    IPAddress ip = WiFi.localIP();
    s += "IP: ";
    s += String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    s += ", SSID: ";
    s += WiFi.SSID();
    s += "'><i class='mdi-device-signal-wifi-4-bar'></i></a>";
  }
  else {
    s += "<i class='mdi-device-signal-wifi-off'></i>";
  }
  s += "</li></ul></div></nav></div>";

  return s;
}

String componentFooter() {
  String s = "";
  
  
  // Footer
  s += "<footer class='page-footer'>";
  s += "<div class='container'>";
  s += "<div class='row'>";
  s += "<div class='col l6 s12'>";
  s += "<h5 class='white-text'>About</h5>";
  s += "<p class='grey-text text-lighten-4'>This device is a part of beer-tap system.</p>";
  s += "</div>";
  s += "<div class='col l4 offset-l2 s12'>";
  s += "<h5 class='white-text'>Links</h5>";
  s += "<ul>";
  s += "<li><a class='grey-text text-lighten-3' href='/'>Dashboard</a></li>";
  s += "<li><a class='grey-text text-lighten-3' href='/settings'>Network settings</a></li>";
  s += "<li><a class='grey-text text-lighten-3' href='/onewire'>OneWire</a></li>";
  s += "</ul>";
  s += "</div>";
  s += "</div>";
  s += "</div>";
  s += "<div class='footer-copyright'>";
  s += "<div class='container'>";
  s += "Proudly made by Ny Media AS";
  s += "<a class='grey-text text-lighten-4 right' href='http://nymedia.no'>Ny Media</a>";
  s += "</div>";
  s += "</div>";
  s += "</footer>";
  
  return s;
}

String componentAvailableNetworks() {
  String s = ""; 
  s += "<table><thead><tr><th data-field='ssid'>SSID</th><th data-field='quality'>Quality</th><th>Secured?</th></tr></thead>";
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
      s += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
      s += "</td></tr>";
    }
  }
  s += "</tbody></table>";
  return s;
}
