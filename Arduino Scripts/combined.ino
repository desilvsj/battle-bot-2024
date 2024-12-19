#include <Ps3Controller.h>

// Motor A pins
int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;

// PS3 controller variables
int player = 0;
int battery = 0;
int dutyCycle = 200;  // Initial speed for PWM control

// PWM settings
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;

void notify() {
  // PS3 controller button events to control motor direction and speed
  if (Ps3.event.button_down.cross) {
    Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel, dutyCycle);  // Control speed with dutyCycle
  }

  if (Ps3.event.button_down.circle) {
    Serial.println("Moving Backward");
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel, dutyCycle);  // Control speed with dutyCycle
  }

  if (Ps3.event.button_down.triangle) {
    Serial.println("Stopping Motor");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
  }

  // Use the up and down D-pad buttons to increase or decrease speed
  if (Ps3.event.button_down.up) {
    dutyCycle += 10;
    if (dutyCycle > 255) dutyCycle = 255; // Max speed
    Serial.print("Increasing speed: ");
    Serial.println(dutyCycle);
    ledcWrite(pwmChannel, dutyCycle);
  }

  if (Ps3.event.button_down.down) {
    dutyCycle -= 10;
    if (dutyCycle < 0) dutyCycle = 0; // Min speed
    Serial.print("Decreasing speed: ");
    Serial.println(dutyCycle);
    ledcWrite(pwmChannel, dutyCycle);
  }
}

void onConnect() {
  Serial.println("PS3 Controller Connected.");
}

void setup() {
  // Motor setup
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // PWM setup
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcWrite(pwmChannel, dutyCycle);  // Set initial speed

  // Serial and PS3 controller setup
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("a0:5a:5b:a0:07:c4");  // Replace with your PS3 controller’s MAC address

  Serial.println("Ready to control DC motor with PS3 controller.");
}

void loop() {
  if (!Ps3.isConnected()) {
    return;
  }

  // Set player LEDs to indicate controller is active
  Ps3.setPlayer(player);
  player = (player + 1) % 10; // Cycle player indicator LEDs
  delay(100);
}

