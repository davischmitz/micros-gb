#include "WiFi.h"
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>

// Replace with your network credentials
const char* ssid = "*";
const char* password = "*";

//DHT 11 config
#define DHTPIN 5 // Pino conectado ao DHT 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const uint16_t IRSENDERLEDPIN = 4;

IRsend irsend(IRSENDERLEDPIN);

#define IR_DATA_LENGTH 99
#define IR_FREQUENCY 38 // IR data will be sent at 38kHz
uint16_t AC_POWER_BUTTON[IR_DATA_LENGTH] = {8960, 4576,  530, 1714,  530, 1716,  528, 590,  
412, 686,  528, 634,  528, 632,  528, 636,  530, 1720,  524, 634,  528, 
1712,  530, 1716,  528, 632,  528, 634,  524, 634,  528, 632,  528, 632,  
528, 634,  528, 636,  528, 1716,  526, 630,  530, 636,  528, 636,  528, 
630,  530, 636,  524, 638,  522, 1712,  528, 634,  526, 632,  532, 628,  
528, 1718,  472, 1662,  528, 632,  528, 632,  530, 632,  530, 630,  528, 
632,  528, 632,  526, 636,  526, 640,  520, 632,  526, 632,  528, 636,  
528, 594,  528, 632,  530, 630,  530, 634,  528, 634,  526, 596,  528};


bool isAcOn = false;

// Web server config
AsyncWebServer server(80);

void toggleAc() {
  irsend.sendRaw(AC_POWER_BUTTON, IR_DATA_LENGTH, IR_FREQUENCY);  
  isAcOn = !isAcOn;
  if (isAcOn) {
    Serial.println("AC turned ON");
  } else {
    Serial.println("AC turned OFF");
  }
}

void handleAcControl(float temperature) {
  if (temperature <= 16 && !isAcOn) {
    toggleAc();
  } else if (temperature >= 20 && isAcOn) {
    toggleAc();
  }
}

String readDHTTemperature() {
  // Temperatura lida em Celcius por default
  float t = dht.readTemperature();
  // A leitura do sensor pode demorar até 2s para ser feita, nesse caso é exibido o erro na serial
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    handleAcControl(t);  
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  float h = dht.readHumidity();
  // A leitura do sensor pode demorar até 2s para ser feita, nesse caso é exibido o erro na serial
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    Serial.println(h);
    return String(h);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 5000 );

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 5000 );
</script>
</html>)rawliteral";

// Substitui os placeholders pelas leituras do sensor ao carregar a pagina
String processor(const String& var){
  if (var == "TEMPERATURE") {
    return readDHTTemperature();
  }
  else if (var == "HUMIDITY") {
    return readDHTHumidity();
  }
  return String();
}

void setup() {
  // Serial port config
  Serial.begin(115200);

  dht.begin();

  irsend.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
