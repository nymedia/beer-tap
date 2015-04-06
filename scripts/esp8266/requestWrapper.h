String cssBase() {
  /*!
  Pure v0.6.0
  Copyright 2014 Yahoo! Inc. All rights reserved.
  Licensed under the BSD License.
  https://github.com/yahoo/pure/blob/master/LICENSE.md
  */
  /*!
  normalize.css v^3.0 | MIT License | git.io/normalize
  Copyright (c) Nicolas Gallagher and Jonathan Neal
  */
  /*! normalize.css v3.0.2 | MIT License | git.io/normalize */
  String s = "html{font-family:sans-serif;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}article,aside,details,figcaption,figure,footer,header,hgroup,main,menu,nav,section,summary{display:block}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}a{background-color:transparent}a:active,a:hover{outline:0}abbr[title]{border-bottom:1px dotted}b,strong{font-weight:700}dfn{font-style:italic}h1{font-size:2em;margin:.67em 0}mark{background:#ff0;color:#000}small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}sup{top:-.5em}sub{bottom:-.25em}img{border:0}svg:not(:root){overflow:hidden}figure{margin:1em 40px}hr{-moz-box-sizing:content-box;box-sizing:content-box;height:0}pre{overflow:auto}code,kbd,pre,samp{font-family:monospace,monospace;font-size:1em}button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}button{overflow:visible}button,select{text-transform:none}button,html input[type=button],input[type=reset],input[type=submit]{-webkit-appearance:button;cursor:pointer}button[disabled],html input[disabled]{cursor:default}button::-moz-focus-inner,input::-moz-focus-inner{border:0;padding:0}input{line-height:normal}input[type=checkbox],input[type=radio]{box-sizing:border-box;padding:0}input[type=number]::-webkit-inner-spin-button,input[type=number]::-webkit-outer-spin-button{height:auto}input[type=search]{-webkit-appearance:textfield;-moz-box-sizing:content-box;-webkit-box-sizing:content-box;box-sizing:content-box}input[type=search]::-webkit-search-cancel-button,input[type=search]::-webkit-search-decoration{-webkit-appearance:none}fieldset{border:1px solid silver;margin:0 2px;padding:.35em .625em .75em}legend{border:0;padding:0}textarea{overflow:auto}optgroup{font-weight:700}table{border-collapse:collapse;border-spacing:0}td,th{padding:0}.hidden,[hidden]{display:none!important}.pure-img{max-width:100%;height:auto;display:block}";
  return s;
}

String cssCustom() {
  String s = "*{-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}a{text-decoration:none;color:#3d92c9}a:focus,a:hover{text-decoration:underline}h3{font-weight:100}.pure-img-responsive{max-width:100%;height:auto}#layout{padding:0}.sidebar{background:#3d4f5d;color:#fff}header{margin:1em}header svg{fill:#ffffff; width: 64px; height:64px;}header .strength{float:right}.brand-tagline,.brand-title{margin:0}.brand-title{text-transform:uppercase}.brand-tagline{font-weight:300;color:#b0cadb}.content-subhead{text-transform:uppercase;color:#aaa;border-bottom:1px solid #eee;padding:.4em 0;font-size:80%;font-weight:500;letter-spacing:.1em}.content{padding:2em 1em 0}.footer{text-align:center;padding:1em 0}.footer a{color:#ccc;font-size:80%}.footer .pure-menu a:focus,.footer .pure-menu a:hover{background:0 0}@media (min-width:48em){.content{padding:2em 3em 0;margin-left:25%}.header{margin:80% 2em 0;text-align:right}.sidebar{position:fixed;top:0;bottom:0}}";
  return s;
}

String jsBase() {
  String s = "";
  s += "function ajax(path, id) {\nvar xmlhttp;\nxmlhttp=new XMLHttpRequest();\nxmlhttp.onreadystatechange=function(){if (xmlhttp.readyState==4 && xmlhttp.status==200){document.getElementById(id).innerHTML=xmlhttp.responseText;}};\nxmlhttp.open('GET',path,true);\nxmlhttp.send();\n};\n";
  s += "window.onload = function (){\n";
  s += "ajax('/component/header', 'header');\n";
  s += "ajax('/component/footer', 'footer');\n";
  s += "if (document.getElementById('refresh-available-networks') != null){document.getElementById('refresh-available-networks').addEventListener('click', function() {ajax('/component/networks', 'available-networks')});};\n";
  s += "if (document.getElementById('refresh-available-sensors') != null){document.getElementById('refresh-available-sensors').addEventListener('click', function() {ajax('/component/sensors', 'available-sensors')});};\n";
  s += "}";
  return s;
}


String htmlDocument(String body) {
  // Prepare the response
  String s = "<!DOCTYPE HTML>\r\n<html><head>";
  s += "<title>Manage device</title>";
  s += "<meta charset='utf-8'>";
  s += "<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
  s += "<link rel='stylesheet' href='/base.css'>";
  s += "<link rel='stylesheet' href='/custom.css'>";
  s += "<link rel='stylesheet' href='http://yui.yahooapis.com/pure/0.6.0/pure-min.css'>";
  s += "<link rel='stylesheet' href='http://yui.yahooapis.com/pure/0.6.0/grids-responsive-min.css'>";
  s += "<script type='text/javascript' src='/base.js'></script>";
  s += "<script>\n";

  s += "</script>\n";
  s += "</head><body>";
  s += "</div id='layout' class='pure-g'>";
  s += "<div id='header' class='sidebar pure-u-1 pure-u-md-1-4'></div>";
  
  // Content
  s += "<div id='main' class='content pure-u-1 pure-u-md-3-4'>";
  s += body;
 
  s += "<div id='footer' class=''></div>"; 

  s += "</div>";

  s += "</div>";

  s += "</body></html>";
  
  return s;
}
