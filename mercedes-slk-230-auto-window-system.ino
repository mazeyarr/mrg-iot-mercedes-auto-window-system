const int LEFT_DOOR_SIGNAL_PIN = 4; 
const int LEFT_WINDOW_UP_PIN = 15;
const int LEFT_WINDOW_DOWN_PIN = 13;

const int RIGHT_DOOR_SIGNAL_PIN = 5; 
const int RIGHT_WINDOW_UP_PIN = 12;
const int RIGHT_WINDOW_DOWN_PIN = 14;

const int LED_STATUS_PIN = 0;

const unsigned long WINDOW_MOVE_DURATION_UP = 1000; // Duration for moving window up (in milliseconds)
const unsigned long WINDOW_MOVE_DURATION_DOWN = 1000; // Duration for moving window down (in milliseconds)

bool leftDoorState = false;
bool rightDoorState = false;

void setup() {
  Serial.begin(115200);

  Serial.println("Mercedes SLK 230 - Auto window system");
  Serial.println("Version: 1.0");
  Serial.println("Author: Mazeyar Rezaei Ghavamabadi");
  Serial.println("---------------------------------------");
  Serial.println("");

  pinMode(LEFT_DOOR_SIGNAL_PIN, INPUT);
  pinMode(LEFT_WINDOW_UP_PIN, OUTPUT);
  pinMode(LEFT_WINDOW_DOWN_PIN, OUTPUT);

  pinMode(RIGHT_DOOR_SIGNAL_PIN, INPUT);
  pinMode(RIGHT_WINDOW_UP_PIN, OUTPUT);
  pinMode(RIGHT_WINDOW_DOWN_PIN, OUTPUT);

  pinMode(LED_STATUS_PIN, OUTPUT);
  
  Serial.println("Setup completed.");
}

void loop() {
  // Read left door state
  bool newLeftDoorState = digitalRead(LEFT_DOOR_SIGNAL_PIN);
  
  // If left door state changed
  if (newLeftDoorState != leftDoorState) {
    leftDoorState = newLeftDoorState;
    Serial.print("Left door state changed. New state: ");
    Serial.println(leftDoorState);
    if (leftDoorState) {
      moveWindow(LEFT_WINDOW_DOWN_PIN, LEFT_WINDOW_UP_PIN, WINDOW_MOVE_DURATION_DOWN); // Move left window down
    } else {
      moveWindow(LEFT_WINDOW_UP_PIN, LEFT_WINDOW_DOWN_PIN, WINDOW_MOVE_DURATION_UP); // Move left window up
    }
    updateStatusLED(leftDoorState); // Update LED based on left window state
  }

  // Read right door state
  bool newRightDoorState = digitalRead(RIGHT_DOOR_SIGNAL_PIN);
  
  // If right door state changed
  if (newRightDoorState != rightDoorState) {
    rightDoorState = newRightDoorState;
    Serial.print("Right door state changed. New state: ");
    Serial.println(rightDoorState);
    if (rightDoorState) {
      moveWindow(RIGHT_WINDOW_DOWN_PIN, RIGHT_WINDOW_UP_PIN, WINDOW_MOVE_DURATION_DOWN); // Move right window down
    } else {
      moveWindow(RIGHT_WINDOW_UP_PIN, RIGHT_WINDOW_DOWN_PIN, WINDOW_MOVE_DURATION_UP); // Move right window up
    }
    updateStatusLED(rightDoorState); // Update LED based on right window state
  }
}

void moveWindow(int pin1, int pin2, unsigned long duration) {
  Serial.println("Moving window...");
  digitalWrite(pin1, HIGH); // Activate window motor
  digitalWrite(pin2, LOW); // Activate window motor
  delay(duration); // Wait for specified duration
  digitalWrite(pin1, LOW); // Deactivate window motor
  digitalWrite(pin2, LOW); // Deactivate window motor
  Serial.println("Window movement completed.");
}

void updateStatusLED(bool windowMovingDown) {
  Serial.println("Updating status LED...");
  if (windowMovingDown) {
    digitalWrite(LED_STATUS_PIN, HIGH); // Turn on status LED if window is moving down
  } else {
    digitalWrite(LED_STATUS_PIN, LOW); // Turn off status LED if window is moving up
  }
  Serial.println("Status LED updated.");
}
