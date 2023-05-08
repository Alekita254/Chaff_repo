/*
 * this project was done by Engineer Alex Murimi, 
 * Simply connect the signal pin of the relay to arduino digital pin 3 of the arduino
 * Connect the trig pin of the ultra sonic sensor to arduino digital pin 12;
 * connect the echo pin of the ultra sonic sensor to arduino digital pin 11;
 *    
 *    //////    //       //////     //             // 
 *    //  //    //       //         //  //     //  //
 *    //  //    //       //         //   //  //    // 
 *    //////    //       //////     //    //       //
 *    //  //    //       //         //             //
 *    //  //    //       //         //             //
 *    //  //    //////   //////     //             // 
 *  
 */

// pin 3 == relay
// pin 4 == pir
// coiled wire == no
//smooth wire == com
int relaypin=3;
int trigpin=12;
int echopin=11;
int speakerpin=10;
int redpin=5;
int yellowpin=9;
int greenpin=7;
int fanpin=6;

int pingTravelTime; 
float pingTravelDistance;
float distanceToTarget;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(speakerpin, OUTPUT);
  pinMode(redpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(fanpin, OUTPUT);
  pinMode(relaypin, OUTPUT);

  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  measureDistance();
  if(distanceToTarget < 20.00) {
    redWarning();
    relayPinOff();
    digitalWrite(speakerpin,HIGH);
  }else{
    redSafe();
    relayPinOn();
  }
  // the second condition
   if(distanceToTarget <= 28.00){
   yellowWarning();
    }else{
   yellowSafe();
     }   
//     the last condition  
  if(distanceToTarget < 35.00){
    greenWarning();
  }else{
    greenSafe();
  }
}

void relayPinOn() {
   digitalWrite(relaypin, HIGH);
}
void relayPinOff() {
  digitalWrite(relaypin, LOW);
}

void measureDistance(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  pingTravelTime=pulseIn(echopin, HIGH);
  delay(25);
  pingTravelDistance=(pingTravelTime*765.*5280.*12) / (3600.*1000000);
  distanceToTarget=pingTravelDistance/2;

  Serial.print("your distance: ");
  Serial.print(distanceToTarget);
  Serial.println("inches.");

  return distanceToTarget;
}
void greenWarning(){
  digitalWrite(greenpin, HIGH);
//  delay(500);

  
}
void greenSafe() {
digitalWrite(greenpin, LOW);
  digitalWrite(speakerpin, LOW);
}

void yellowWarning(){
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, HIGH);
}

void yellowSafe() {
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, LOW);
  digitalWrite(speakerpin, LOW);
}

void redWarning() {
  digitalWrite(redpin, HIGH);
  digitalWrite(speakerpin, HIGH);
}
void redSafe() {
  digitalWrite(redpin, LOW);
  digitalWrite(speakerpin, LOW);
}

void lightsOn() {
  digitalWrite(greenpin, HIGH);
  digitalWrite(redpin, HIGH);
  digitalWrite(yellowpin, HIGH);
}

void lightsOff() {
digitalWrite(greenpin, LOW);
digitalWrite(redpin,LOW);
digitalWrite(yellowpin,LOW);
digitalWrite(speakerpin,LOW);
}
