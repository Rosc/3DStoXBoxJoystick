
float GateSize = 0.7;

int IdleVal;
int  MaxReading;
  
// the setup routine runs once when you press reset:
void setup() {
   Serial.begin(9600);
  IdleVal = analogRead(A1) / 1023 * 255;
  MaxReading = analogRead(A3) * GateSize / 1023 * 255;
  //MaxReading = analogRead(A3);
  Serial.print("Idle:");Serial.println(GateSize);
  Serial.print("Voltage:");Serial.println(MaxReading);
}

void loop() {
 //   Serial.print("Idle:");Serial.println(GateSize);
 // Serial.print("Voltage:");Serial.println(MaxReading);
}
