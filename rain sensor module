int rainPin = 34;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Rain Intensity Detection");
}

void loop() {
  int value = analogRead(rainPin);

  Serial.print("Rain Value: ");
  Serial.println(value);

  // Adjust thresholds based on your sensor
  if (value > 3500) {
    Serial.println(" No Rain");
  }
  else if (value > 2000) {
    Serial.println(" Light Rain");
  }
  else if (value > 1000) {
    Serial.println(" Medium Rain");
  }
  else {
    Serial.println(" Heavy Rain");
  }

  Serial.println("----------------------");
  delay(1000);
}
