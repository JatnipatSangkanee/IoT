#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <PubSubClient.h>
#include <ArduinoHttpClient.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "CoEIoT";
const char* password = "iot.coe.psu.ac.th";

const char* mqttServer = "172.30.81.197";
const int mqttPort = 1883;
const char* mqttTopic = "iot1";

String wifiMac;
WiFiClient espClient;
PubSubClient client;


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void callback(char* topic, byte* payload, unsigned int length);


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqttServer, mqttPort);
  client.setClient(espClient);
  client.setCallback(callback);
  
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
    // Serial.print("MQTT Server: ");
    // Serial.println(mqttServer);
    // Serial.print("MQTT Port: ");
    // Serial.println(mqttPort);
    // Serial.print("MQTT Topic: ");
    // Serial.println(mqttTopic);

    if (client.connect(wifiMac.c_str())) {
      Serial.println("Connected to MQTT Broker");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed to connect to MQTT Broker, retrying in 5 seconds...");
      delay(5000);
    }
  }
}
//Servo Code 
// void controlServo(int servoChannel,int delaytime) {
//   // คำนวณค่า PWM สำหรับตำแหน่งของ Servo จากองศา (0-180)
//   int pulse = map(servoChannel, 0, 6, 180, 360);
//   pwm.setPWM(servoChannel, 0, pulse);

//   delay(delaytime); // 10 seconds

//   // Stop servo by setting PWM to 0
//   pwm.setPWM(servoChannel, 0, 0);

// }

void controlServo(int servoChannel, int delayTime) {
  Serial.print("Controlling servo on channel: ");
  Serial.print(servoChannel);
  Serial.print(" with delay: ");
  Serial.print(delayTime);
  Serial.println(" milliseconds.");

  // สมมติว่าเราคำนวณค่า PWM จากองศา (0-180) และส่งค่าไปยังเซอร์โว
  int pulse = map(servoChannel, 0, 6, 180, 360);
  pwm.setPWM(servoChannel, 0, pulse);


  // บันทึกเวลาเริ่มต้น
  unsigned long startTime = millis();
  Serial.print("Starting delay at: ");
  Serial.println(startTime);

  delay(delayTime); // ใช้เวลา delay

  // บันทึกเวลาหลังจาก delay
  unsigned long endTime = millis();
  Serial.print("Ending delay at: ");
  Serial.println(endTime);

  // คำนวณและแสดงเวลาที่ใช้จริง
  Serial.print("Actual delay time: ");
  Serial.print(endTime - startTime);
  Serial.println(" milliseconds.");

  // หยุดเซอร์โว
  pwm.setPWM(servoChannel, 0, 0);
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
    controlServo(1,5000);
  } else if (payloadStr == "2BATH") {
    controlServo(2,6500);
  } else if (payloadStr == "3BATH") {
    controlServo(3,5000);
  } else if (payloadStr == "4BATH") {
    controlServo(4,7000);
  } else if (payloadStr == "5BATH") {
    controlServo(5,10000);
  } else if (payloadStr == "6BATH") {
    controlServo(0,3500);
  }
  Serial.println("Callback executed.");  // Add this line for debugging

}




