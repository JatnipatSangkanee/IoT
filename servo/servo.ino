#include <Wire.h>
// #include <SPI.h>
// #include <MFRC522.h>
#include <pitches.h>
#include <TM1637Display.h>
#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>

#define DIO 2 // TM1637
#define CLK 4 // TM1637
#define RST PIN 9 // rfid
#define SS PIN 10 // rfid
#define BUZZER_PIN 8

#define LED PIN 7
const int sw_theta=14; // ΑΘ
const int sw1=15; // A1
const int SW2=16; // A2
const int sw3=17; // A3
const int sw_restock = 5; // pin 5
const byte rxPin = 0; // pin e
const byte txPin = 1; // pin 1

LiquidCrystal_I2C lcd(0x27, 16 ,2);
MFRC522 rfid(SS_PIN, RST_PIN);
TM1637Display display = TM1637Display(CLK, DIO);
Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver(0x40);
SoftwareSerial mySerial(rxPin, txPin);

const int Contrast = 100;
int buttonPressed = -1;
bool isCardDetected = false;
bool cardEnabled = false;
bool timeout = false;
int count, index;
int pulselen = 150;
float totalIncome = 0.0;
float productIncome[4] = {0.0};

const char* snacks[] = {
    "Snack A", "Snack B", "Snack C", "Snack D",
};
int prices[] = {
    10, 20, 30, 40,
};

int product_amount[] = {
    4, 4, 4, 4,
};

byte heart[] = {
    0x00,
    0x00,
    0x0A,
    0x15,
    0x11,
    0x0A,
    0x0A,
    0x00
};

void setup() {
    initialSetup();
}
void initialSetup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    pinMode(sw_restock, INPUT);
    pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
    pinMode(BUZZER_PIN, OUTPUT); // Set the BUZZER pin as an output
    analogWrite(6, Contrast); // set contrast at pin6
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, heart);
    lcd.clear();
    lcd.print(" Welcome to ");
    lcd.setCursor(0, 1);
    lcd.print("Vending Machine");
    lcd.write((byte)0);
    SPI.begin(); // Init SPI bus
    rfid.PCD_Init(); // Init MFRC522
    display.clear();
    display.setBrightness(7);
    isCardDetected = false; // Reset card detection status
    cardEnabled = false; // Disable the card
    timeout = false;
    myServo.begin();
    myServo.setPWMFreq(50);
    TCCR1A = 0x00;
    sei();
}
void loop() {
    int button = checkButtons();
    switch (button) {
    case swo:
        displaySnackAndPrice(sw0);
        delay(500);
        break;
    case sw1:
        displaySnackAndPrice(sw1);
        delay(500);
        break;
    case sw2:
        displaySnackAndPrice(sw2);
        delay(500);
        break;
    case sw3:
        displaySnackAndPrice(sw3);
        delay(500);
        break;
}
display.showNumberDecEx(00, 0b11100000, true, 2, 0); display.showNumberDecEx(count, 0, true, 2, 2);
if (digitalRead(sw_restock) == LOW) {
    restockProduct();
}
if(!timeout){
    readCard();
    if (isCardDetected && cardEnabled) {
        count = 0;
        display.showNumberDecEx(count, 0, true, 2, 2);
        processTransaction();
}
} else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Time out! ");
    lcd.setCursor(0, 1);
    lcd.print("Please try again");
    delay(1000);
    initialSetup();
    }
}
int checkButtons() {
    for (int i = 0; i < 4; i++) {
        if (digitalRead(sw0 + 1) == LOW) {
            if (product_amount[i] > 0) {
                enableCard(); // Enable the card
                buttonPressed = sw0 + 1;
                count = 15;
                return buttonPressed;
                } else {
                    count = 0;
                    display.showNumberDecEx(0000, 0611100000, true, 4, 0);
                    displayOutOfStock(i);
                    delay(1000);
                    initialSetup();
            }
        }
    }
        return -1; // No button pressed or all products are out of stock
}
