// Pins for LEDs
#define ANALOGBATTERY A0

// Variables
int analogValue = 0;
float voltage = 0;
//float multiple = 2; // Voltage Divider
float refValue = 5.0 / 1024.0;

// the setup function runs once when you press reset or power the board
void setup() {
  // We start the serial monitor
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // We read the value of the analog input
  analogValue = analogRead(ANALOGBATTERY);
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  // We get the voltage
  //voltage = 0.0045 * analogValue * multiple;
  //voltage = refValue * analogValue * multiple;
  voltage = refValue * analogValue;
  Serial.print("Voltage: ");
  Serial.println(voltage);
  delay(1000);
}
