#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "sul";
const char* password = "123456789";



// IPAddress staticIP(192, 168, 11, 200);  // ESP32 static IP
// IPAddress gateway(192, 168, 11, 48);   // IP Address of your network gateway (router)
// IPAddress subnet(255, 255, 255, 0);    // Subnet mask
// IPAddress primaryDNS(192, 168, 11, 48);// Primary DNS
// IPAddress secondaryDNS(0, 0, 0, 0);    // Secondary DNS (optional)



WebServer server(80);

const int motorPins[9] = {2, 4, 5, 12, 13, 14, 25, 26, 27};

int motorIndexPepsi = 0;
int motorIndexCola = 3;
int motorIndex7up = 6;

int cansDispensed[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

const int cansPerMotor = 3;

void handleRoot() {
  server.send(200, "text/plain", "Use /pepsi, /cola, or /7up to dispense a can.");
}

void dispenseCan(int &motorIndex) {
  int motorPin = motorPins[motorIndex];
  digitalWrite(motorPin, HIGH);
  delay(500); 
  digitalWrite(motorPin, LOW);
  delay(500); 

  cansDispensed[motorIndex]++;
  
  if (cansDispensed[motorIndex] >= cansPerMotor) {
    cansDispensed[motorIndex] = 0;
    motorIndex = (motorIndex + 1) % 3 + (motorIndex / 3) * 3;
  }
}

void handlePepsi() {
  dispenseCan(motorIndexPepsi);
  server.send(200, "text/plain", "Dispensing a can of Pepsi.");
}

void handleCola() {
  dispenseCan(motorIndexCola);
  server.send(200, "text/plain", "Dispensing a can of Cola.");
}

void handle7up() {
  dispenseCan(motorIndex7up);
  server.send(200, "text/plain", "Dispensing a can of 7up.");
}




void setup() {
    Serial.begin(115200);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  for (int i = 0; i < 9; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }

  

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
Serial.println("");
  Serial.println("Connected..!");
 
  Serial.print("Current ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway (router) IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Subnet Mask: " );
  Serial.println(WiFi.subnetMask());
  Serial.print("Primary DNS: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("Secondary DNS: ");
  Serial.println(WiFi.dnsIP(1));


  server.on("/", handleRoot);
  server.on("/pepsi", handlePepsi);
  server.on("/cola", handleCola);
  server.on("/7up", handle7up);

  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}
