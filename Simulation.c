const int rainSensor = 34;   // potentiometer (rain simulation)
const int motorPin = 25;     // motor / LED
const int modeButton = 14;   // override button

const int speedBtn1 = 27;    // speed low
const int speedBtn2 = 26;    // speed medium
const int speedBtn3 = 33;    // speed high

bool manualMode = false;
int speed = 0;

void setup() {

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(speedBtn1, INPUT_PULLUP);
  pinMode(speedBtn2, INPUT_PULLUP);
  pinMode(speedBtn3, INPUT_PULLUP);

  pinMode(motorPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  int rainValue = analogRead(rainSensor);

  // Toggle manual/auto mode
  if (digitalRead(modeButton) == LOW) {
    manualMode = !manualMode;
    delay(300);
  }

  // AUTO MODE
  if (!manualMode) {

    speed = map(rainValue, 0, 4095, 0, 255);
    analogWrite(motorPin, speed);

    Serial.print("AUTO MODE  Rain: ");
    Serial.print(rainValue);
    Serial.print("  Speed: ");
    Serial.println(speed);

  }

  // MANUAL MODE
  else {

    if (digitalRead(speedBtn1) == LOW) speed = 85;
    if (digitalRead(speedBtn2) == LOW) speed = 170;
    if (digitalRead(speedBtn3) == LOW) speed = 255;

    analogWrite(motorPin, speed);

    Serial.print("MANUAL MODE Speed: ");
    Serial.println(speed);
  }

  delay(100);
}
