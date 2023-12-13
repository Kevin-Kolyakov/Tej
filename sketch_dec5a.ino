#include <Servo.h>

bool on = false;
const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 5;
const int redLED2 = 8;
const int yellowLED2 = 9;
const int greenLED2 = 10;
const int button = 6;
const int whiteLed1 = 7;

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
long redDuration = 6000;
long yellowDuration = 2000;
long greenDuration = 2000;

int currentState = 0;
int currentState2 = 0;
long callCurrentMillis;

int pos = 0;

Servo servo_11;

void setup() {
  Serial.begin(9600);
  servo_11.attach(11, 500, 2500);
  pinMode(A0, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED2, OUTPUT);
  pinMode(yellowLED2, OUTPUT);
  pinMode(greenLED2, OUTPUT);
  pinMode(whiteLed1, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(button, ledchange, RISING);
}

void loop() {

  // for (pos = 0; pos <= 180; pos += 1) {
  //   // tell servo to go to position in variable 'pos'
  //   servo_11.write(pos);
  //   // wait 15 ms for servo to reach the position
  //   delay(15); // Wait for 15 millisecond(s)
  // }

  if (analogRead(A0) > 1000) {
    digitalWrite(whiteLed1, HIGH);
  } else if (analogRead(A0) < 900) {
    digitalWrite(whiteLed1, LOW);
  }

  unsigned long currentMillis = millis();
  callCurrentMillis = currentMillis;

  if (digitalRead(button) == LOW) {
    Serial.println("Button pressed!");
    Serial.println(on);
  }

  if (currentState == 0) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    if (currentMillis - previousMillis >= redDuration) {
      previousMillis = currentMillis;
      currentState = 1;
    }
  } else if (currentState == 1) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    if (currentMillis - previousMillis >= yellowDuration) {
      previousMillis = currentMillis;
      currentState = 2;
    }
  } else if (currentState == 2) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    if (currentMillis - previousMillis >= greenDuration) {
      previousMillis = currentMillis;
      currentState = 0;
    }
  }

  if (currentState2 == 0) {
    digitalWrite(redLED2, LOW);
    digitalWrite(yellowLED2, LOW);
    digitalWrite(greenLED2, HIGH);
    if (currentMillis - previousMillis2 >= greenDuration) {
      previousMillis2 = currentMillis;
      currentState2 = 1;
    }
  } else if (currentState2 == 1) {
    digitalWrite(redLED2, LOW);
    digitalWrite(greenLED2, LOW);
    digitalWrite(yellowLED2, HIGH);
    if (currentMillis - previousMillis2 >= yellowDuration) {
      previousMillis2 = currentMillis;
      currentState2 = 2;
    }
  } else if (currentState2 == 2) {
    digitalWrite(redLED2, HIGH);
    digitalWrite(yellowLED2, LOW);
    digitalWrite(greenLED2, LOW);
    if (currentMillis - previousMillis2 >= redDuration) {
      previousMillis2 = currentMillis;
      currentState2 = 0;
    }
  }
}

void ledchange() {
  on = true;
  // if (on) {
  //   digitalWrite(whiteLed1, LOW);
  // } else {
  //   digitalWrite(whiteLed1, HIGH);
  // }
  // Serial.println("aslihflwiuefhs");
  // if(currentState == 0){
  //   redDuration = (callCurrentMillis - previousMillis)/2;
  //   yellowDuration = (callCurrentMillis - previousMillis)/2;
  //   greenDuration = (callCurrentMillis - previousMillis)*2;
  // }
}