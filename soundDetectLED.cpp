const int soundSensor = 7; 
const int ledPinBlue = 2;      
const int ledPinGreen = 3;     
const int ledPinRed = 4;       

boolean LEDStatus=false;
unsigned long lastSoundTime = 0;

void setup() {
 pinMode(soundSensor,INPUT);
 pinMode(ledPinBlue,OUTPUT);
 pinMode(ledPinGreen,OUTPUT);
 pinMode(ledPinRed,OUTPUT);
}

void loop() {
  int SensorData = digitalRead(soundSensor);

  if (SensorData == HIGH) { // Adjust this condition based on your sensor behavior
    if (millis() - lastSoundTime >= 250) { // Only proceed if at least 1 second has passed since last sound
      LEDStatus = !LEDStatus; // Toggle the LEDStatus

      if (LEDStatus) {
        // Turn on the green LED and turn off the others
        digitalWrite(ledPinGreen, HIGH);
        digitalWrite(ledPinBlue, LOW);
        digitalWrite(ledPinRed, LOW);
      } else {
        // Turn off all LEDs
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinBlue, LOW);
        digitalWrite(ledPinRed, LOW);
      }

      lastSoundTime = millis(); // Update the last sound time
    }
  }
}
