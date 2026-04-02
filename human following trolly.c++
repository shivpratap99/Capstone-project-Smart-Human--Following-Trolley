#define ENA 5  
#define IN1 8
#define IN2 9
#define ENB 6   
#define IN3 10
#define IN4 11

#define TRIG_FRONT 12
#define ECHO_FRONT 13

#define TRIG_SIDE 7
#define ECHO_SIDE 4   

const int TARGET_DISTANCE = 20;     // Follow at 20 cm
const int TOLERANCE = 5;            // Range buffer
const int MAX_SPEED = 200;          // Max PWM
const int MIN_SPEED = 100;          // Minimum movement
const int LOST_TIMEOUT = 3000;      // 3 seconds wait when customer disappears
const float KP = 4.5;               // Proportional gain

unsigned long lastSeenTime = 0;

/
long readDistanceCM(int trigPin, int echoPin);
void moveForward(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void stopMotors();

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_SIDE, OUTPUT);
  pinMode(ECHO_SIDE, INPUT);

  stopMotors();
  delay(1000);
  Serial.println(" Human Following Trolley Ready!");
}

void loop() {
  long frontDist = readDistanceCM(TRIG_FRONT, ECHO_FRONT);
  long sideDist = readDistanceCM(TRIG_SIDE, ECHO_SIDE);

  Serial.print("Front: ");
  Serial.print(frontDist);
  Serial.print(" cm | Side: ");
  Serial.println(sideDist);

  // ------- HANDLE FRONT DISTANCE -------
  if (frontDist > 0 && frontDist < 300) {
    lastSeenTime = millis();  // Person found
  }

  // If person is missing for 3 seconds
  if (millis() - lastSeenTime > LOST_TIMEOUT) {
    stopMotors();
    Serial.println(" Customer Lost — Waiting...");
    delay(100);
    return;
  }

  // ------- FOLLOWING LOGIC -------
  if (frontDist > 0 && frontDist < TARGET_DISTANCE - TOLERANCE) {
    // Too close
    stopMotors();
    Serial.println(" Too Close — Stopped!");
  } 
  else if (frontDist > TARGET_DISTANCE + TOLERANCE && frontDist < 250) {
    // Too far → follow forward
    int error = frontDist - TARGET_DISTANCE;
    int pwm = constrain(error * KP, MIN_SPEED, MAX_SPEED);
    moveForward(pwm);

    Serial.print("⬆ Following | Speed = ");
    Serial.println(pwm);
  }
  else if (frontDist > 0) {
    // Perfect zone
    stopMotors();
    Serial.println("Holding Position...");
  }

  // ------- SIDE TURNING LOGIC -------
  if (sideDist > 5 && sideDist < 120) {  
    // Close object on side → turn RIGHT
    if (sideDist < 30) {
      Serial.println("↪ Turning RIGHT to follow customer...");
      turnRight(150);
      delay(500);
      stopMotors();
      delay(3000);
    }
    // Far object on side → turn LEFT
    else if (sideDist > 60) {
      Serial.println("↩ Turning LEFT to follow customer...");
      turnLeft(150);
      delay(500);
      stopMotors();
      delay(3000);
    }
  }

  delay(100);
}



long readDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000UL);
  if (duration == 0) return -1;

  return duration / 58;
}

void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void turnLeft(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void turnRight(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}