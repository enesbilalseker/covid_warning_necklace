#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>

int sensor = A0;
// Set the initial sensorValue to 0
int sensorValue = 0;
// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
//WiFi connection
const char* ssid = "Enes";
const char* password = "enesbilal77";

const char* host = "maker.ifttt.com";
const int httpsPort = 443;

const char* key = "b871167c629f5eaa3346832a7e95ad4be6b2b807";

// defines variables
long duration;
int distance;
BearSSL::WiFiClientSecure client;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
  client.setInsecure();
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Uzaklık: ");
  Serial.println(distance);

  // Read the input on analog pin 0 (named 'sensor')
  // Print out the value you read
  sensorValue = analogRead(sensor);
  Serial.print("CO2 Miktarı: ");
  Serial.println(sensorValue, DEC);

  if (distance<=100){
    Serial.print("connecting to ");
    Serial.println(host);
    Serial.print("Using key: ");
    Serial.println(key);
    client.setFingerprint(key);

    if(!client.connect(host, httpsPort))
    {
    Serial.println("connection failed");
    return;
    }

    String url = "/trigger/warning/with/key/dFytRWs5rsEqtZxA0--fCy";
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "User-Agent: BuildFailureDetectorESP8266\r\n" +
      "Connection: close\r\n\r\n");

    Serial.println("request sent");
   }


    if (sensorValue>=1000){
    Serial.print("connecting to ");
    Serial.println(host);
    Serial.print("Using key: ");
    Serial.println(key);
    client.setFingerprint(key);

    if(!client.connect(host, httpsPort))
    {
    Serial.println("connection failed");
    return;
    }

    String url = "/trigger/warning2/with/key/dFytRWs5rsEqtZxA0--fCy";
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "User-Agent: BuildFailureDetectorESP8266\r\n" +
      "Connection: close\r\n\r\n");

    Serial.println("request sent");
   }
    
  
delay(2000);
}
