#include <Arduino.h>
#line 1 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <PubSubClient.h>
#define MQTT_MAX_PACKET_SIZE 512

const char* ssid = "CoEIoT";
const char* password = "iot.coe.psu.ac.th";

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "iot1";

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#line 20 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
void setup();
#line 36 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
void loop();
#line 43 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
void reconnect();
#line 63 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
void callback(char* topic, byte* payload, unsigned int length);
#line 91 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
void setServoPosition(uint8_t channel, uint16_t angle);
#line 20 "D:\\Project-371\\mqtt\\mqtt\\mqtt.ino"
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqttServer, mqttPort);
  
  // ติดต่อ PCA9685
  pwm.begin();
  pwm.setPWMFreq(60);  // ตั้งค่าความถี่ PWM (สามารถเปลี่ยนเป็นค่าอื่นตามต้องการ)
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    Serial.print("MQTT Server: ");
    Serial.println(mqttServer);
    Serial.print("MQTT Port: ");
    Serial.println(mqttPort);
    Serial.print("MQTT Topic: ");
    Serial.println(mqttTopic);

    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed to connect to MQTT Broker, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Callback triggered!");

  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  
  String payloadStr = "";
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }
  Serial.println(payloadStr);
  
  // ทำการควบคุม Servo 2, 4, 6 ตามค่าที่รับมาจาก MQTT
  if (payloadStr == "1BATH") {
    Serial.println("Selected Servo 2 for 1 BATH");

    setServoPosition(2, 0);  // ตำแหน่งสำหรับ 1 บาท
  } else if (payloadStr == "2BATH") {
    setServoPosition(4, 0);  // ตำแหน่งสำหรับ 2 บาท
  } else if (payloadStr == "3BATH") {
    setServoPosition(6, 0);  // ตำแหน่งสำหรับ 3 บาท
  }
  Serial.println("Callback executed.");  // Add this line for debugging

}

// ฟังก์ชันในการตั้งค่าตำแหน่งของ Servo
void setServoPosition(uint8_t channel, uint16_t angle) {
  // คำนวณค่า PWM สำหรับตำแหน่งของ Servo จากองศา (0-180)
  uint16_t pulse = map(angle, 0, 180, 150, 600);
  
  // ส่งค่า PWM ไปยัง PCA9685
  pwm.setPWM(channel, 0, pulse);

  // พิมพ์ข้อความ Debugging ใน Serial Monitor
  Serial.print("Servo ");
  Serial.print(channel);
  Serial.println(" rotated.");
}
