#define solenoidValve1Pin A0
#define solenoidValve2Pin A1
#define mosfetSwitchPin A4
#define pressureSensor1Pin A10
#define pressureSensor2Pin A5
#define builtInLedPin PC13 // Assuming STM32 board has an LED_BUILTIN constant

void setup() {
  pinMode(solenoidValve1Pin, OUTPUT);
  pinMode(solenoidValve2Pin, OUTPUT);
  pinMode(mosfetSwitchPin, OUTPUT);
  pinMode(builtInLedPin, OUTPUT);

  //digitalWrite(solenoidValve1Pin, HIGH);

  // Add setup for pressure sensors if needed

  //delay(1500);

  digitalWrite(builtInLedPin, LOW);

  sequenceControl(15000, 1000);

  // Turn off built-in LED once setup is complete
  digitalWrite(builtInLedPin, HIGH);
}

void loop() {
  // Your main loop code here
  
  /*
  // Read pressure values
  int pressure1 = readPressure(pressureSensor1Pin);
  int pressure2 = readPressure(pressureSensor2Pin);

  // Check if both pressures are within the specified range
  if (pressure1 >= 6000 && pressure1 <= 6500 && pressure2 >= 6000 && pressure2 <= 6500) {
    // Perform your sequence control or other actions here
    sequenceControl(1000, 2);
  }*/
}

void sequenceControl(int timeDelay, int frequency) {
  
  //digitalWrite(builtInLedPin, HIGH); // Turn on built-in LED
  delay(timeDelay);

  digitalWrite(solenoidValve1Pin, HIGH);
  digitalWrite(solenoidValve2Pin, HIGH);

  // Calculate the loop count for a 1.5-second duration
  int loopCount = static_cast<int>((1500000.0 / (1000000.0 / frequency)));

  for (int i = 0; i < loopCount; i++) {
    digitalWrite(mosfetSwitchPin, LOW);
    digitalWrite(builtInLedPin, LOW); // Turn on built-in LED
    delayMicroseconds(500000 / frequency);
    digitalWrite(mosfetSwitchPin, HIGH);
    digitalWrite(builtInLedPin, HIGH); // Turn off built-in LED
    delayMicroseconds(500000 / frequency);
  }

  /*
  // Calculate the loop count for a 1.5-second duration
  loopCount = static_cast<int>((1500000.0 / (1000000.0 / (frequency/2))));
  delay(1000);
  for (int i = 0; i < loopCount; i++) {
    digitalWrite(mosfetSwitchPin, HIGH);
    digitalWrite(builtInLedPin, HIGH); // Turn on built-in LED
    delayMicroseconds(500000 / (frequency/2));
    digitalWrite(mosfetSwitchPin, LOW);
    digitalWrite(builtInLedPin, LOW); // Turn off built-in LED
    delayMicroseconds(500000 / (frequency/2));
  }
  // Calculate the loop count for a 1.5-second duration
  loopCount = static_cast<int>((1500000.0 / (1000000.0 / (frequency/4))));
  delay(1000);
  for (int i = 0; i < loopCount; i++) {
    digitalWrite(mosfetSwitchPin, HIGH);
    digitalWrite(builtInLedPin, HIGH); // Turn on built-in LED
    delayMicroseconds(500000 / (frequency/4));
    digitalWrite(mosfetSwitchPin, LOW);
    digitalWrite(builtInLedPin, LOW); // Turn off built-in LED
    delayMicroseconds(500000 / (frequency/4));
  }
  // Calculate the loop count for a 1.5-second duration
  loopCount = static_cast<int>((1500000.0 / (1000000.0 / (frequency/8))));
  delay(1000);
  for (int i = 0; i < loopCount; i++) {
    digitalWrite(mosfetSwitchPin, HIGH);
    digitalWrite(builtInLedPin, HIGH); // Turn on built-in LED
    delayMicroseconds(500000 / (frequency/8));
    digitalWrite(mosfetSwitchPin, LOW);
    digitalWrite(builtInLedPin, LOW); // Turn off built-in LED
    delayMicroseconds(500000 / (frequency/8));
  }
  // Calculate the loop count for a 1.5-second duration
  loopCount = static_cast<int>((1500000.0 / (1000000.0 / (frequency/16))));
  delay(1000);
  for (int i = 0; i < loopCount; i++) {
    digitalWrite(mosfetSwitchPin, HIGH);
    digitalWrite(builtInLedPin, HIGH); // Turn on built-in LED
    delayMicroseconds(500000 / (frequency/16));
    digitalWrite(mosfetSwitchPin, LOW);
    digitalWrite(builtInLedPin, LOW); // Turn off built-in LED
    delayMicroseconds(500000 / (frequency/16));
  }
  */
  delay(2000);
  digitalWrite(solenoidValve1Pin, LOW);
  digitalWrite(solenoidValve2Pin, LOW);
  // Turn off built-in LED once setup is complete
  digitalWrite(builtInLedPin, LOW);
}
