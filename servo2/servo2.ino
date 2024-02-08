#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// #define SERVO_1 2
// #define SERVO_2 4
// #define SERVO_3 6

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);  // 60Hz

  delay(10);

  // ตั้งค่า Servo ให้หยุดหมุนทั้ง 3 ตัว
  setServoSpeed(SERVO_1, 0);
  setServoSpeed(SERVO_2, 0);
  // setServoSpeed(SERVO_3, 0);
}

void loop() {
  // ทดสอบหมุน Servo 1 ทุก 1 วินาที
  setServoSpeed(SERVO_1, 180);  // 360 คือหมุนทั้งหมด
  delay(10000);
  // หยุดหมุน Servo 1
  setServoSpeed(SERVO_1, 0);
  delay(10000);

  setServoSpeed(SERVO_2, 360);  // 360 คือหมุนทั้งหมด
  delay(5000);
  // หยุดหมุน Servo 1
  setServoSpeed(SERVO_2, 0);
  delay(1000);
  
  // pwm.setPWM(SERVO_1, 1, 150);
  // pwm.setPWM(SERVO_2, 1,0);
}

void setServoSpeed(uint8_t servoNum, int speed) {
  // speed คือความเร็วของ Servo (0-360)
  // 0 คือหยุด, 360 คือหมุนทั้งหมด

  if (speed < 0) {
    speed = 0;
  } else if (speed > 360) {
    speed = 360;
  }

  // แปลงความเร็วของ Servo จากองศา (0-360) เป็น PWM Pulse Length (150-600)
  int pulseLength = map(speed, 0, 360,0 , 600);
  
  // ใช้ PWM Servo Driver ส่งคำสั่งไปยัง Servo
  pwm.setPWM(servoNum, 0, pulseLength);
}
