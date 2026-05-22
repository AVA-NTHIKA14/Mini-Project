// ---------------- MOTOR PINS ----------------
#define RPWM 18
#define LPWM 19

// ---------------- RAIN SENSOR ----------------
#define RAIN_SENSOR 34

// ---------------- BUTTON ----------------
#define buttonPin 13

// ---------------- PWM CONFIG ----------------
int freq = 1000;
int resolution = 8;

// ---------------- SYSTEM STATE ----------------
bool autoMode = true;
bool lastButtonState = HIGH;

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);

  pinMode(LPWM, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // ESP32 PWM ATTACH
  ledcAttach(RPWM, freq, resolution);

  digitalWrite(LPWM, LOW);
  ledcWrite(RPWM, 0);

  Serial.println("System Ready - AUTO MODE");
}

// ---------------- BUTTON TOGGLE ----------------
void handleButton() {

  bool currentState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentState == LOW) {

    autoMode = !autoMode;

    if (autoMode)
      Serial.println("AUTO MODE ON");
    else
      Serial.println("MANUAL OFF MODE");

    delay(300); // debounce
  }

  lastButtonState = currentState;
}

// ---------------- MOTOR CONTROL ----------------
void motorRun(int speedVal) {

  digitalWrite(LPWM, LOW);
  ledcWrite(RPWM, speedVal);
}

void motorStop() {

  ledcWrite(RPWM, 0);
  digitalWrite(LPWM, LOW);
}

// ---------------- LOOP ----------------
void loop() {

  handleButton();

  int rain = analogRead(RAIN_SENSOR);

  Serial.print("Rain Value : ");
  Serial.println(rain);

  // ===== MANUAL MODE =====
  if (!autoMode) {

    Serial.println("MANUAL MODE - WIPER OFF");

    motorStop();

    delay(200);

    return;
  }

  // ===== DRY CONDITION =====
  if (rain > 3500) {

    Serial.println("DRY - WIPER OFF");

    motorStop();

    delay(200);

    return;
  }

  // ===== HEAVY RAIN =====
  if (rain < 1200) {

    Serial.println("HEAVY RAIN - HIGH SPEED");

    motorRun(255);
  }

  // ===== MEDIUM RAIN =====
  else if (rain < 2500) {

    Serial.println("MEDIUM RAIN - MED SPEED");

    motorRun(170);

    delay(400);

    motorStop();

    delay(200);
  }

  // ===== LIGHT RAIN =====
  else {

    Serial.println("LIGHT RAIN - LOW SPEED");

    motorRun(100);

    delay(800);

    motorStop();

    delay(500);
  }
}

