# 1 "D:\\Project-371\\mqtt-1\\mqtt\\mqtt.ino"
# 2 "D:\\Project-371\\mqtt-1\\mqtt\\mqtt.ino" 2
# 3 "D:\\Project-371\\mqtt-1\\mqtt\\mqtt.ino" 2
# 4 "D:\\Project-371\\mqtt-1\\mqtt\\mqtt.ino" 2
# 5 "D:\\Project-371\\mqtt-1\\mqtt\\mqtt.ino" 2
# 6 "D:\\Project-371\\mqtt-1\\mqtt\\mqtt.ino" 2

const char* ssid = "CoEIoT";
const char* password = "iot.coe.psu.ac.th";

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "iot1";

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
  pwm.setPWMFreq(60); // ตั้งค่าความถี่ PWM (สามารถเปลี่ยนเป็นค่าอื่นตามต้องการ)
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

    if (client.connect("clientId-mE31npwVE9")) {
      Serial.println("Connected to MQTT Broker");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed to connect to MQTT Broker, retrying in 5 seconds...");
      delay(5000);
    }
  }
}
void controlServo(int servoChannel) {
  // คำนวณค่า PWM สำหรับตำแหน่งของ Servo จากองศา (0-180)
  int pulse = map(servoChannel, 0, 6, 150, 600);
  pwm.setPWM(servoChannel, 0, pulse);

  delay(10000); // 10 seconds

  // Stop servo by setting PWM to 0
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

    controlServo(2);
  } else if (payloadStr == "2BATH") {
    controlServo(5);
  } else if (payloadStr == "3BATH") {
    controlServo(6);
  }
  Serial.println("Callback executed."); // Add this line for debugging

}
