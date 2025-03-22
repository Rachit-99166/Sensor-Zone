#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
int led=D3;
int ss=A0;      


const char* ssid = "RONYSLENNY 0279";
const char* password = "10101010";

ESP8266WebServer server(80);
int variable = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(ss,INPUT);
  pinMode(led,OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

  randomSeed(analogRead(A0));

  // Start the web server
  server.on("/setVariable", HTTP_GET, handleSetVariable);
  server.on("/getVariable", HTTP_GET, handleGetVariable);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleSetVariable() {
  if (server.hasArg("value")) {
    String value = server.arg("value");
    variable = value.toInt();
    Serial.print("Variable set to: ");
    Serial.println(variable);
    server.send(200, "text/plain", "Variable set successfully");
    Serial.print("successfully send");
  } else {
    server.send(400, "text/plain", "Invalid request");
    Serial.print("Invalid request");
  }
}

void handleGetVariable() {
  // variable = random(501); // Generate a random number between 0 and 500
  int variable=analogRead(ss);
  String variableValue = String(variable);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", variableValue);
   if(variable>100)
 {
  digitalWrite(led,1);
  delay(3000);
 }
 else
 {
  digitalWrite(led,0);
 }
 Serial.println(variable);
  delay(200);

}
