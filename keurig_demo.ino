/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int STATUS_WATER = 6;     // the number of the pushbutton pin
const int STATUS_POWER = 5;      // the number of the LED pin
const int STATUS_HEATING = 4;
const int STATUS_8OZ = 3;
const int STATUS_12OZ = 2;
const int BUTTON_READ = 7;
const int BUTTON_WRITE = 8;

int t; 
int MACHINE_READY;
int LAST_12OZ;
int COUNT_12OZ;
int SAME_COUNT_12OZ;

void setup() {

  Serial.begin(9600);

  for (int i=2; i<=7; i++)
  {
    pinMode(i, INPUT);
  }
  
  pinMode(BUTTON_WRITE,OUTPUT);
  digitalWrite(BUTTON_WRITE, LOW);
  
  MACHINE_READY = 0;
  COUNT_12OZ = 0;
}

void loop(){
  
  //Read all status and buttons
  for (int i=2; i<=7; i++)
  {
    t = digitalRead(i);
    Serial.print(t);
  }
  Serial.print(MACHINE_READY);
  Serial.println();

  //Read 12oz and compare to last read. If constantly changing, we know it's blinking
  t = digitalRead(STATUS_12OZ);
  if (t != LAST_12OZ)
  {
    COUNT_12OZ++; 
  }
  else
  {
    SAME_COUNT_12OZ++;
  }

  LAST_12OZ = t;

  if (COUNT_12OZ > 3 || SAME_COUNT_12OZ > 3)
  {
    if (COUNT_12OZ > 3)
    {MACHINE_READY = 1;}
    else 
    {MACHINE_READY = 0;}
 
    COUNT_12OZ = 0;
    SAME_COUNT_12OZ = 0;
  }
  
  //Once button pressed, reset MACHINE_READY
  if (digitalRead(BUTTON_READ) == HIGH)
  {
     MACHINE_READY = 0;
     COUNT_12OZ = 0; 
  }
  
}
