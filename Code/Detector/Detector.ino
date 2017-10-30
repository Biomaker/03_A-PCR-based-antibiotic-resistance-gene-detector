int Detector = 0;

void setup() {
Serial.begin(9600);
}

void loop() {
 float Light = analogRead(Detector);
 Serial.println(Light);
 delay(100);
}
