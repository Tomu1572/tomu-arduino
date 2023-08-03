#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int i = 0;
int j = 0;
int randomnum;
int z = 0;
int k = 0;
int array1[] = { 5, 5, 3, 4, 1, 2, 5, 5, 5, 5, 3, 4, 1, 2, 5, 5, 5, 5, 3, 4, 1, 2, 5, 5, 5, 5, 3, 4, 1, 2, 5, 5 };
int array2[] = { 3, 4, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 1, 2 };
byte customChar1[] = {
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B
};

byte customChar2[] = {
  0x18,
  0x18,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B
};

byte customChar3[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x18,
  0x1B,
  0x1B
};

byte customChar4[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x03,
  0x03,
  0x1B,
  0x1B
};

byte customChar5[] = {
  0x03,
  0x03,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B
};

byte customChar6[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

const int soundSensor = 7;
const int ledPinBlue = 2;
const int ledPinGreen = 3;
const int ledPinRed = 4;
const int threshold = 500; // Adjust this threshold based on your sound sensor

boolean LEDStatus = false;
boolean isSoundDetected = false;
unsigned long lastSoundTime = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar1);
  lcd.createChar(1, customChar2);
  lcd.createChar(2, customChar3);
  lcd.createChar(3, customChar4);
  lcd.createChar(4, customChar5);
  lcd.createChar(5, customChar6);
  lcd.setCursor(4, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  delay(2000);
  lcd.clear();
  pinMode(soundSensor, INPUT);
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
}

void loop() {
  int SensorData = digitalRead(soundSensor); // Read sound sensor data

  if (SensorData == HIGH) { // Adjust this condition based on your sensor behavior
    if (millis() - lastSoundTime >= 250) { // Only proceed if at least 1 second has passed since the last sound
      LEDStatus = !LEDStatus; // Toggle the LEDStatus

      if (LEDStatus) {
        // Turn on the green LED and turn off the others
        digitalWrite(ledPinGreen, HIGH);
        digitalWrite(ledPinBlue, LOW);
        digitalWrite(ledPinRed, LOW);
        animateSineWave();
        isSoundDetected = true;
      } else {
        // Turn off all LEDs
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinBlue, LOW);
        digitalWrite(ledPinRed, LOW);
      }

      lastSoundTime = millis(); // Update the last sound time
      isSoundDetected = false; // Reset sound detection flag
      displayStraightLine();
       
    }
  }
}

void displayStraightLine() {
  // Display a straight line on the LCD
  for (z = 7; z >= 0; z--) {
    i = z;
    for (k = 0; k < 16; k++) {
      lcd.setCursor(k, 0);
      lcd.write(array1[i]);
      lcd.setCursor(k, 1);
      lcd.write(array2[i]);
      i++;
    }
    delay(100);
    lcd.clear();
  }
}

void animateSineWave() {
  // Display the sine wave on the LCD
  for (int t = 0; t < 16; t++) {
    int y = 1 + sin(2 * PI * t / 16) * 1; // Adjust the amplitude (1) as needed
    lcd.setCursor(t, 0);
    lcd.write(y);
    lcd.setCursor(t, 1);
    lcd.write(y);
  }
  delay(100);
  lcd.clear();
}

