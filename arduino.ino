const int ledPin = 13; 
int incomingByte;
String command;     

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  command = Serial.readStringUntil('\n');
  if (command == "1") {
      digitalWrite(ledPin, HIGH);
      Serial.println("Lamp enabled");
  }
    else if (command == "2") {
      digitalWrite(ledPin, LOW);
      Serial.println("Lamp disabled");
  }
}
