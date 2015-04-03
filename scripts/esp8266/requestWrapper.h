String htmlDocument(String body) {
  // Prepare the response
  String s = "<!DOCTYPE HTML>\r\n<html>\r\n<head>";
  s += "<title>Manage device</title>";
  s += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/materialize/0.96.0/css/materialize.min.css'>";
  s += "<meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no'/>";
  s += "</head><body>";
  
  // Navbar
  s += "<div class='navbar'><nav><div class='nav-wrapper container'><a href='#!' class='brand-logo'>Manage device</a><ul class='right hide-on-med-and-down'><li>";
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
  // Content
  s += "<div class='container'>";
  s += body;  
  s += "<script type='text/javascript' src='https://code.jquery.com/jquery-2.1.1.min.js'></script>";
  s += "<script src='https://cdnjs.cloudflare.com/ajax/libs/materialize/0.96.0/js/materialize.min.js'></script>";
  s += "</div>";
  
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
  s += "<li><a class='grey-text text-lighten-3' href='/networks'>Networks</a></li>";
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
  s += "</body></html>\n";
  
  return s;
}
