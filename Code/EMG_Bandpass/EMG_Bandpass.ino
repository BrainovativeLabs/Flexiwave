// Define constants
#define BAUD_RATE 9600
#define INPUT_PIN1 A0

void setup() {
  // Initialize serial communication
  Serial.begin(BAUD_RATE);
  // Uncomment the line below if you need to set analog read resolution
  // analogReadResolution(12);
}

void loop() {
  // Read sensor value from the specified analog pin
  long sensorValue1 = analogRead(INPUT_PIN1);
  
  // Filter the sensor value using the EMGFilter function
  float filteredSignal1 = EMGFilter(sensorValue1);

  // Print the filtered signal to the serial monitor
  Serial.println(filteredSignal1);
  
  // If there is noise in the signal due to a laptop connected to charging or a PC connected to power,
  // try adjusting the delay to 1 ms or 10 ms.
  delay(10);
}

// Function to apply EMG filtering
float EMGFilter(float input) {
  float output = input;

  // First filter section
  {
    static float z1, z2; // Filter section state
    float x = output - 0.05159732 * z1 - 0.36347401 * z2;
    output = 0.01856301 * x + 0.03712602 * z1 + 0.01856301 * z2;
    z2 = z1;
    z1 = x;
  }

  // Second filter section
  {
    static float z1, z2; // Filter section state
    float x = output - (-0.53945795) * z1 - 0.39764934 * z2;
    output = 1.00000000 * x + (-2.00000000) * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }

  // Third filter section
  {
    static float z1, z2; // Filter section state
    float x = output - 0.47319594 * z1 - 0.70744137 * z2;
    output = 1.00000000 * x + 2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }

  // Fourth filter section
  {
    static float z1, z2; // Filter section state
    float x = output - (-1.00211112) * z1 - 0.74520226 * z2;
    output = 1.00000000 * x + (-2.00000000) * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }

  return output;
}
 
