// Sharp IR GP2Y0A41SK0F Distance Test
// http://tinkcore.com/sharp-ir-gp2y0a41-skf/

#define sensorFront A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensorRight A0
 
 
 #define pwmA    3
 #define dirA    12
 #define pwmB    11
 #define dirB    13

 #define ForwardPin 7
  #define BackwardPin 6
   #define RightPin 5
    #define LeftPin 4
    

 const int rightLimit = 15;
 const int frontLimit = 15;

void setup() {
  Serial.begin(9600); // start the serial port
  pinMode(pwmA, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(dirB, OUTPUT);

  pinMode(ForwardPin, INPUT);
  pinMode(BackwardPin, INPUT);
  pinMode(RightPin, INPUT);
  pinMode(LeftPin, INPUT);

  digitalWrite(ForwardPin, LOW);
  digitalWrite(BackwardPin, LOW);
  digitalWrite(RightPin, LOW);
  digitalWrite(LeftPin, LOW);
     


}

void loop() {

  float voltsFront = analogRead(sensorFront)*0.0048828125;  // value from sensor * (5/1024)
  float distanceFront = 13*pow(voltsFront, -1); // worked out from datasheet graph
  float voltsRight = analogRead(sensorRight)*0.0048828125;  // value from sensor * (5/1024)
  float distanceRight = 13*pow(voltsRight, -1); // worked out from datasheet graph
  delay(100); // slow down serial port 
  Serial.println(distanceFront);   // print the distance
  delay(1000);
    
    

  if(digitalRead(RightPin) == HIGH){
    Right();
  }
  if(digitalRead(LeftPin) == HIGH){
    Left();
  }
  if(digitalRead(ForwardPin) == HIGH){
    Forward();
  }
    if(digitalRead(BackwardPin) == HIGH){
    Backward();
  }

 
}


void Forward(){
   Bmotor(100);
   delay(10);
   Bmotor(0);
}

void Backward(){
   Bmotor(-100);
   delay(10);
   Bmotor(0);
}

void Left(){
   Amotor(100);
   delay(10);
   Amotor(0);
  
  }

void Right(){
   Amotor(100);
   delay(10);
   Amotor(0);
  
  }


void Amotor(int pwm){

  

    if(pwm > 0){
    digitalWrite(dirA, HIGH);
    analogWrite(pwmA, pwm);
    }
    else if(pwm < 0){
      digitalWrite(dirA, LOW);
      analogWrite(pwmA, -pwm);
      }
    else{
      analogWrite(pwmA, 0);
    }
}

void Bmotor(int pwm){

  

    if(pwm > 0){
    digitalWrite(dirB, HIGH);
    analogWrite(pwmB, pwm);
    }
    else if(pwm < 0){
      digitalWrite(dirB, LOW);
      analogWrite(pwmB, -pwm);
      }
    else{
      analogWrite(pwmB, 0);
    }
}
