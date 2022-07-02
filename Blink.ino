#define DHTPIN D4     
#define DHTTYPE DHT11   

#define BLYNK_TEMPLATE_ID "TMPLJovgCf_A"
#define BLYNK_DEVICE_NAME "DHT22 Blynk"
#define BLYNK_AUTH_TOKEN "u6wWLTLMm_MWZLramu3fel6aDn2Ep6TI"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

DHT dht(DHTPIN, DHTTYPE);

int trig = 4;
int echo = 5;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "AAA";
char pass[] = "00000000";


BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print(t);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);

  double distance = getDistance();

  
 
  Blynk.virtualWrite(V2, distance);
}


void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, sendSensor);

  dht.begin();
}


void loop() {
  Blynk.run();
  timer.run();   
}

int getDistance()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH) / 58;
}
 

