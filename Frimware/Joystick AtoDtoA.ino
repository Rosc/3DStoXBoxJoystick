/*
  Untitled Controller Project
  
  Description Here

*/


// Percentage that the joystick range that's still usable after adding the 3d-printed gate
float GateSize = 0.70;

//  Deadzone Parameters: Upper boun and Lower bounds as a percentage (out of 1).  Anything in between will be returned as an idle stick
float DZUpper = 0.60;
float DZLower = 0.40;

// Percentage of the output to return as an idle stick.  This *should* be 0.5, but ymmv
float DZIdle = 0.47;

// Invert Axis. 1 = true, 0 = false
int XInv = 1;
int YInv = 0;

// System Globals.  There shouldn't be any reason to edit below this line
int MaxOut;
int Margin;

void setup() {
//Serial.begin(9600);
//analogReference(EXTERNAL);

  // Initialize PWM pins
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  // Recalibrate. This has to be done regularly because the 3.3v rail will dip under battery power.1  11111111
  calibrate();

  

//Serial.print("outText:");Serial.println(outText);
  analogWrite(1, Normalize(analogRead(A1),XInv)); 
  analogWrite(0, Normalize(analogRead(A2),YInv)); 

  delay(1);        // delay in between reads for stability
}

/*
  Recalibrate the PWM levels based on the joystick voltage reference and 3.3v
*/
void calibrate() {
  // Calculate the PWM needed to match the attiny's logic voltage to the max range on the analog circuit.
  MaxOut = analogRead(A3) * 0.25;
//Serial.print("MaxOut:");Serial.println(MaxOut);      
  // Calulate how much to shave of the joystick reading later. Might not be necessary, but hopefully will save some processing time.
  Margin = ((1 - GateSize)) * 1023;
//Serial.print("Margin:");Serial.println(Margin);  
}

/*
  Calculate the PWM output based on the ADC input calculated against the restrictor gate
*/
int Normalize(int Level, int Invert){
  int outText = ((abs((1023 * Invert) - Level) - Margin) / ((1023 * GateSize) - Margin)) * MaxOut;
  if (outText < 0) { outText = 0; }
  if (outText > MaxOut) { outText = MaxOut; }  
  if (outText < (DZUpper * MaxOut) && outText > (DZLower * MaxOut)) { outText = DZIdle * MaxOut; } 
  return outText;
}
