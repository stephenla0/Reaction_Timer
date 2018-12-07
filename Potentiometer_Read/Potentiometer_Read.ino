#define ledPinRed 7
#define ledPinGreen 6
#define ledPinYellow 5
#define butPinRed 4
#define butPinGreen 3
#define butPinYellow 2
unsigned long time;
int buttonStateYellow = 1; //detect button state
int buttonStateGreen = 1;
int buttonStateRed = 1;
int currentButton = 1;
bool buttonReady = false; //if the game is running
int ledStartTime;
int reactionTime;
int avgTime;
bool gameStart = false; //if game has started
int potPin = A0;    // select the input pin for the potentiometer
float potVal = 0;    // variable to store the value coming from the potentiometer
float potPrev = -1; //previous potentiometer value
int difficultyTime = 0;

void setup() {
  pinMode(ledPinYellow, OUTPUT); //set inputs and outputs
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(butPinRed, INPUT_PULLUP);
  pinMode(butPinYellow, INPUT_PULLUP);
  pinMode(butPinGreen, INPUT_PULLUP);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonStateYellow = digitalRead(butPinYellow); //set button pins
  buttonStateGreen = digitalRead(butPinGreen);
  buttonStateRed = digitalRead(butPinRed);
  potVal = analogRead(potPin);    // read the value from the sensor
  potVal = (potVal * (1.00 / 1023)); //modify potVal to be 0-1

  time = millis();
  if (millis() - difficultyTime > 500) { //print difficulty if changed
    if (abs((potPrev - potVal) * 100) > 1) { //if difficulty changed more than 1%
      Serial.println((String)"Difficulty: " + (int)(potVal * 100) + "%"); //print difficulty
      Serial.println("Press red to start");
    }
    difficultyTime = time;
    potPrev = potVal;
  }
  if (buttonStateRed == 0) { //start game
    gameStart = true;
    delay(10);
  }

  if (gameStart == true) { //if game has been started, run this
    if (buttonReady == false) { //if the game is not already running
      if (buttonStateYellow == 1) {
        if (buttonStateGreen == 1) {
          if (buttonStateRed == 1) {
            currentButton = random(0, 3);
            if (currentButton == 0) {
              delay(random(100, 600) * (11 - (10 * potVal) + .5)); //set timer
              delay(10);
              digitalWrite(ledPinYellow, HIGH);   // turn on LED
              Serial.println("Start");
              time = millis();
              ledStartTime = time;
              buttonReady = true;
            } else if (currentButton == 1) {
              delay(random(100, 600) * (11 - (10 * potVal) + .5)); //set timer
              delay(10);
              digitalWrite(ledPinGreen, HIGH);   // turn on LED
              Serial.println("Start");
              time = millis();
              ledStartTime = time;
              buttonReady = true;
            } else if (currentButton == 2) {
              delay(random(100, 600) * (11 - (10 * potVal) + .5)); //set timer
              delay(10);
              digitalWrite(ledPinRed, HIGH);   // turn on LED
              Serial.println("Start");
              time = millis();
              ledStartTime = time;
              buttonReady = true;
            }
          }
        }
      }
    }
    if (buttonReady == true) {
      if (buttonStateYellow == 0) {
        if (currentButton == 0) {
          Serial.print("Time: ");
          time = millis();
          reactionTime = time - ledStartTime;
          Serial.println(reactionTime);    //prints time since program started
          digitalWrite(ledPinYellow, LOW);
          buttonReady = false;
          delay(100);
        } else {
          gameStart = false;
          buttonReady = false;
          digitalWrite(ledPinYellow, LOW); //turn off LED
          digitalWrite(ledPinGreen, LOW); //turn off LED
          digitalWrite(ledPinRed, LOW); //turn off LED
          Serial.println("End Round");
          potPrev = -1;
          delay(10);
        }
      }
      if (buttonStateGreen == 0) {
        if (currentButton == 1) {
          Serial.print("Time: ");
          time = millis();
          reactionTime = time - ledStartTime;
          Serial.println(reactionTime);    //prints time since program started
          digitalWrite(ledPinGreen, LOW);
          buttonReady = false;
          delay(100);
        } else {
          gameStart = false;
          buttonReady = false;
          digitalWrite(ledPinYellow, LOW); //turn off LED
          digitalWrite(ledPinGreen, LOW); //turn off LED
          digitalWrite(ledPinRed, LOW); //turn off LED
          Serial.println("End Round");
          potPrev = -1;
          delay(10);
        }
      }
      if (buttonStateRed == 0) {
        if (currentButton == 2) {
          Serial.print("Time: ");
          time = millis();
          reactionTime = time - ledStartTime;
          Serial.println(reactionTime);    //prints time since program started
          digitalWrite(ledPinRed, LOW);
          buttonReady = false;
          delay(100);
        } else {
          gameStart = false;
          buttonReady = false;
          digitalWrite(ledPinYellow, LOW); //turn off LED
          digitalWrite(ledPinGreen, LOW); //turn off LED
          digitalWrite(ledPinRed, LOW); //turn off LED
          Serial.println("End Round");
          potPrev = -1;
          delay(10);
        }
      }
    }
  }
}
