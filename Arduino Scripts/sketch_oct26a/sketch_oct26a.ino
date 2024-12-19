const int outputPin = 13;   // PWM output pin
float X = 1.0;              // Multiplier for output voltage, ranges from 0.0 to 1.0

void setup() {
    pinMode(outputPin, OUTPUT);
}

void loop() {
    // Calculate the PWM duty cycle based on X
    int dutyCycle = int(255 * X);  // Scale X to the PWM range (0 to 255)
    
    // Output the PWM signal
    analogWrite(outputPin, dutyCycle);

    //Example: Toggle X between 1.0 and 0.0 every 1.5 seconds
    X = (X == 1.0) ? 0.0 : 1.0;
    delay(1500);
}
