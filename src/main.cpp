#include <Arduino.h>

// -------------------- BLYNK --------------------
#define BLYNK_TEMPLATE_ID "TMPL3dhubxO2f"
#define BLYNK_DEVICE_NAME "fire robot"
#define BLYNK_AUTH_TOKEN "_lTTJGvSRJTxNZIl2LaQDpCCZRFyyg_J"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// ------------------------------------------------

#include <DHT.h>
#include <DHT_U.h>
#include <ESP32Servo.h>

// Pin definitions
#define FLAME_SENSOR 19
#define MQ2_SENSOR 34
#define RELAY 23
#define BUZZER 5
#define LED 2
#define LED1 12
#define LED2 13

#define SERVO_PIN 18
#define SERVO_PIN2 22
#define DHTPIN 4
#define DHTTYPE DHT11

// Create objects
Servo servo1;
Servo servo2;
DHT dht(DHTPIN, DHTTYPE);

// Servo movement variables
unsigned long previousMillis = 0;
const long servoInterval = 30;
int servoAngle = 0;
int servoDirection = 1;

// --------------------- WIFI ---------------------------
char ssid[] = "YourWiFiName";       // CHANGE
char pass[] = "YourWiFiPassword";   // CHANGE
// ------------------------------------------------------

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_SENSOR, INPUT);
  pinMode(MQ2_SENSOR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  servo1.attach(SERVO_PIN);
  servo2.attach(SERVO_PIN2);

  dht.begin();

  digitalWrite(RELAY, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  Serial.println("🔥 Fire & Smoke Detection System Started...");

  // ----------- Blynk Start --------------
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // ---------------------------------------
}

void loop() {
  Blynk.run(); // IMPORTANT

  int flame = digitalRead(FLAME_SENSOR);
  int smoke = analogRead(MQ2_SENSOR);
  float temp = dht.readTemperature();

  if (isnan(temp)) temp = 25.0;

  Serial.print("Flame: ");
  Serial.print(flame ? "No Fire" : "FIRE!");
  Serial.print(" | Smoke: ");
  Serial.print(smoke);
  Serial.print(" | Temp: ");
  Serial.print(temp);
  Serial.println(" °C");

  // ------------- SEND TO BLYNK -------------
  Blynk.virtualWrite(V1, flame == 0 ? 1 : 0);  // Fire status
  Blynk.virtualWrite(V2, smoke);               // Smoke value
  Blynk.virtualWrite(V3, temp);                // Temperature
  // ------------------------------------------

  bool fireDetected = (flame == 0 || smoke > 2000 || temp > 28);

  if (fireDetected) {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(RELAY, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(RELAY, LOW);
  }

  // --- Non-blocking Servo Movement ---
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= servoInterval) {
    previousMillis = currentMillis;

    servoAngle += servoDirection * 2;
    if (servoAngle >= 180) {
      servoAngle = 180;
      servoDirection = -1;
    } else if (servoAngle <= 0) {
      servoAngle = 0;
      servoDirection = 1;
    }

    servo1.write(servoAngle);
    servo2.write(servoAngle);
  }

  delay(100);
}