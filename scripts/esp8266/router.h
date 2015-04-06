
void routerDashboard() {
  String s = "<p>Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Vestibulum tortor quam, feugiat vitae, ultricies eget, tempor sit amet, ante. Donec eu libero sit amet quam egestas semper. Aenean ultricies mi vitae est. Mauris placerat eleifend leo. Quisque sit amet est et sapien ullamcorper pharetra. Vestibulum erat wisi, condimentum sed, commodo vitae, ornare sit amet, wisi. Aenean fermentum, elit eget tincidunt condimentum, eros ipsum rutrum orci, sagittis tempus lacus enim ac dui. Donec non enim in turpis pulvinar facilisis. Ut felis. Praesent dapibus, neque id cursus faucibus, tortor neque egestas augue, eu vulputate magna eros eu erat. Aliquam erat volutpat. Nam dui mi, tincidunt quis, accumsan porttitor, facilisis luctus, metus</p>";
  server.send(200, "text/html", htmlDocument(s));
}

void routerSettings() {
  String s = "";
  
  // Manage WiFi
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  if (ssid.length() && (password.length() >= 8)) {
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
      s += "<div class='row'><div class='col s12 m5'><div class='card-panel teal'><span class='white-text'>Connected to network.</span></div></div></div>";
    }
  }
  
  // Manage internal network
  String apssid = server.arg("apssid");
  String appassword = server.arg("appassword");
  if (apssid.length() && (appassword.length() >= 8)) {
    apssid.toCharArray(apSSID, MAX_WIFI_LENGTH);
    appassword.toCharArray(apPassword, MAX_WIFI_LENGTH);
    connect(defaultSSID, defaultPassword);
    s += "<div class='row'><div class='col s12 m5'><div class='card-panel teal'><span class='white-text'>Changed AP settings.</span></div></div></div>";
  }
  
  s += "<h2>Settings</h2>";
  s += "<div class='pure-g'>";
  
  // Connect to exising network.
  s += "<div class='pure-u-1-3'>";
  s += "<h3>Connect network:</h3>";
  s += "<form class='pure-form' method='post'>";
  s += "<fieldset class='pure-group'>";
  s += "<input placeholder='SSID' id='ssid' name='ssid' type='text' class='validate' value='";
  s += defaultSSID;
  s += "'>";
  s += "<input placeholder='Password' id='password' name='password' type='text' class='validate' value='";
  // s += defaultPassword;
  s += "'>";
  s += "</fieldset>";
  s += "<button class='pure-button pure-button-primary' type='submit' name='action'>Submit</button>";
  s += "</form>";
  s += "</div>";
  
  // Rename internal network.
  s += "<div class='pure-u-1-3'>";
  s += "<h3>Internal network:</h3>";
  s += "<form class='pure-form pure-form-stacked' method='post'>";
  s += "<fieldset class='pure-group'>";
  s += "<input placeholder='SSID' id='apssid' name='apssid' type='text' class='validate' value='";
  s += apSSID;
  s += "'>";
  s += "<input placeholder='Password' id='appassword' name='appassword' type='text' class='validate' value='";
  s += apPassword;
  s += "'>";
  s += "</fieldset>";
  s += "<button class='pure-button pure-button-primary' type='submit' name='action'>Submit</button>";
  s += "</form>";
  s += "<h4>Available networks:<a id='refresh-available-networks' style='cursor: pointer;'>Refresh";
  s += getIcon(8);
  s += "</a></h4>";
  s += "<div id='available-networks'></div>";
  s += "</div>";
  
  s += "<div class='pure-u-1-3'>";
  s += "<h3>Other settings:</h3>";
  // Autoreconnect
  s += "<input type='checkbox' id='autoreconnect' /><label for='autoreconnect'>Autoreconnect</label>";
  s += "</div>";
  
  s += "</div>";
  s += "<script>ajax('/component/networks', 'available-networks');\n</script>";
  // Return rendered markup.
  server.send(200, "text/html", htmlDocument(s));
}

void routerOneWire() {
  String s = "<h3>Available sensors:<a id='refresh-available-sensors' style='cursor: pointer;'>Refresh";
  s += getIcon(8);
  s += "</a></h3>";
  s += "<div id='available-sensors'></div>";
  s += "<script>ajax('/component/sensors', 'available-sensors');\n</script>";

  server.send(200, "text/html", htmlDocument(s));
}

void routerNetworks() {
  String s = componentAvailableNetworks();
  server.send(200, "text/html", s);
}

void routerSensors() {
  String s = componentAvailableSensors();
  server.send(200, "text/html", s);
}

void routerHeader() {
  String s = componentHeader();
  server.send(200, "text/html", s);
}

void routerJs() {
  String s = jsBase();
  server.send(200, "application/javascript", s);
}

void routerCssBase() {
  String s = cssBase();
  server.send(200, "text/css", s);
}

void routerCssCustom() {
  String s = cssCustom();
  server.send(200, "text/css", s);
}

void routerFooter() {
  String s = componentFooter();
  server.send(200, "text/html", s);
}

void routerPaths() {
  server.on("/", routerDashboard);
  server.on("/settings", routerSettings);
  server.on("/onewire", routerOneWire);
  server.on("/component/networks", routerNetworks);
  server.on("/component/sensors", routerSensors);
  server.on("/component/header", routerHeader);
  server.on("/component/footer", routerFooter);
  server.on("/base.css", routerCssBase);
  server.on("/custom.css", routerCssCustom);
  server.on("/base.js", routerJs); 
}
