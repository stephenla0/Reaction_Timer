unsigned long time;
int buttonStateYellow = 0; //detect button state
int ledPinYellow = 5;
int buttonStateGreen = 0;
int ledPinGreen = 6;
int buttonStateRed = 0;
int ledPinRed = 7;
int buttonStateBlack = 0;
bool buttonReady = false; //if the game is running
int ledStartTime;
int reactionTime;
int avgTime;
bool gameStart = false; //if game has started

int potPin = A0;    // select the input pin for the potentiometer
float potVal = 0;    // variable to store the value coming from the potentiometer
float potPrev = -1; //previous potentiometer value
int difficultyTime=0;

void setup() {
  pinMode(ledPinYellow,OUTPUT); //set inputs and outputs
  pinMode(ledPinGreen,OUTPUT); 
  pinMode(ledPinRed,OUTPUT); 
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonStateYellow = digitalRead(2); //set button pins
  buttonStateGreen = digitalRead(3);
  buttonStateRed = digitalRead(4);
  potVal = analogRead(potPin);    // read the value from the sensor
  potVal = (potVal*(1.00/1023)); //modify potVal to be 0-1
  
  time = millis();
    if(millis()-difficultyTime > 500){ //print difficulty if changed
      if(abs((potPrev - potVal)*100) > 1){ //if difficulty changed more than 1%
         Serial.println((String)"Difficulty: " + (int)(potVal*100) + "%"); //print difficulty
         Serial.println("Press red to start");
        }
       difficultyTime = time;
       potPrev = potVal;
    }
if(buttonStateRed==1){ //start game
  gameStart=true;
  delay(100);
}


if(gameStart==true){ //if game has been started, run this
    if(buttonReady==false){ //if the game is not already running
      if(buttonStateYellow==0){
        if(buttonStateGreen==0){
          if(buttonStateRed==0){
            if(random(0,2)==0){
              delay(random(300,3000)*(2-(potVal+.5))); //set timer
              delay(100);
              digitalWrite(ledPinYellow, HIGH);   // turn on LED
              Serial.println("Start");
              time = millis();
              ledStartTime = time;
              buttonReady=true; 
            }else{
              delay(random(300,3000)*(2-(potVal+.5))); //set timer
              delay(100);
              digitalWrite(ledPinGreen, HIGH);   // turn on LED
              Serial.println("Start");
              time = millis();
              ledStartTime = time;
              buttonReady=true; 
            }
          }
        }
      }
    }
  if(buttonReady == true){
    if(buttonStateRed==1){ //end game
      gameStart=false;
      buttonReady=false;
      digitalWrite(ledPinYellow, LOW); //turn off LED
      digitalWrite(ledPinGreen, LOW); //turn off LED
      Serial.println("End Round");
      potPrev = -1;
      delay(100);
    }
    if(buttonStateYellow==1){
      Serial.print("Time: ");
      time = millis();
      reactionTime = time-ledStartTime;
      Serial.println(reactionTime);    //prints time since program started       
      digitalWrite(ledPinYellow, LOW);
      buttonReady=false;
      delay(100); 
    }
    if(buttonStateGreen==1){
      Serial.print("Time: ");
      time = millis();
      reactionTime = time-ledStartTime;
      Serial.println(reactionTime);    //prints time since program started       
      digitalWrite(ledPinGreen, LOW);
      buttonReady=false;
      delay(100); 
    }
    //delay(10); 
  }
} 
  
  /*Serial.print(buttonStateYellow);            // print the potentimeter value
  Serial.print(buttonStateGreen);
  Serial.println(buttonStateRed);
  Serial.println(potVal);*/
}
