/**
 * Laboratory 1: LED Brightness Control Using a Push button/wire
 * 
 * Objective: Control LED brightness in 25% steps using a push button.
 * 
 * Sequence:
 * 1. Start: LED is OFF.
 * 2. Press switch: LED turns on at 25%.
 * 3. Every 3 seconds: Brightness increases by 25% (25% -> 50% -> 75% -> 100%).
 * 4. At 100%: LED remains ON.
 * 5. Press button again: Reset sequence (LED OFF, wait for press).
 */

// Pin definitions
const int LED_PIN = 2;     // Connect LED long leg (via 470 ohm resistor) to D2
const int BUTTON_PIN = 4;  // Connect Button (via 1K ohm pull-down) to D4

// Sequence states
enum SequenceState {
  STATE_OFF,        // LED is OFF, waiting for button press
  STATE_25,         // LED is at 25% brightness
  STATE_50,         // LED is at 50% brightness
  STATE_75,         // LED is at 75% brightness
  STATE_100         // LED is at 100% brightness (ON)
};

// Variable declarations
SequenceState currentState = STATE_OFF;
unsigned long lastStepTime = 0;       // Keeps track of the 3-second timer
const unsigned long stepInterval = 3000; // 3 seconds in milliseconds

// Button debouncing variables
bool lastButtonState = LOW;
bool currentButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // 50ms to filter button noise

void setup() {
  Serial.begin(115200);
  
  // Set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT); // Expecting external 1K pull-down resistor
  
  // Ensure LED starts OFF
  analogWrite(LED_PIN, 0);
  Serial.println("System initialized. LED is OFF. Press button to start.");
}

void loop() {
  // Read the button state
  int reading = digitalRead(BUTTON_PIN);

  // Check if button state changed (noise or actual press)
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // If the state has persisted longer than the debounce delay, accept it
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // Detect button press (transition from LOW to HIGH)
      if (currentButtonState == HIGH) {
        handleButtonPress();
      }
    }
  }

  // Save the reading for next loop iteration
  lastButtonState = reading;

  // Handle the automatic brightness increase every 3 seconds
  handleTimer();
}

/**
 * Triggered whenever the button is pressed.
 */
void handleButtonPress() {
  if (currentState == STATE_OFF) {
    // Start the sequence at 25%
    currentState = STATE_25;
    analogWrite(LED_PIN, 64); // 25% of 255 is ~64
    lastStepTime = millis();  // Reset the 3-second timer
    Serial.println("Sequence started: LED at 25% brightness.");
  } else {
    // If the sequence is already running or complete, pressing resets it
    currentState = STATE_OFF;
    analogWrite(LED_PIN, 0); // Turn LED OFF
    Serial.println("Sequence reset: LED is OFF.");
  }
}

/**
 * Handles the automatic brightness increment every 3 seconds.
 */
void handleTimer() {
  // Only increment if we are in a running state and NOT at 100% yet
  if (currentState != STATE_OFF && currentState != STATE_100) {
    if (millis() - lastStepTime >= stepInterval) {
      lastStepTime = millis(); // Reset step timer

      switch (currentState) {
        case STATE_25:
          currentState = STATE_50;
          analogWrite(LED_PIN, 128); // 50% of 255 is ~128
          Serial.println("3 seconds elapsed: LED at 50% brightness.");
          break;
          
        case STATE_50:
          currentState = STATE_75;
          analogWrite(LED_PIN, 191); // 75% of 255 is ~191
          Serial.println("3 seconds elapsed: LED at 75% brightness.");
          break;
          
        case STATE_75:
          currentState = STATE_100;
          analogWrite(LED_PIN, 255); // 100% of 255 is 255
          Serial.println("3 seconds elapsed: LED at 100% brightness (Remain ON).");
          break;
          
        default:
          break;
      }
    }
  }
}
