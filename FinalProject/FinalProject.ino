// Sharp IR GP2Y0A41SK0F Distance Test
// http://tinkcore.com/sharp-ir-gp2y0a41-skf/

#define sensorLeft A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

 
 
 #define pwmA    3
 #define dirA    12
 #define pwmB    11
 #define dirB    13

 #define ForwardPin 7
 #define BackwardPin 6
 #define RightPin 5
 #define LeftPin 4
 #define turnPower 65
    

 const int Limit = 30;
 bool CanGoForward = true;

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

}

void loop() {

  
  float voltsFront = analogRead(sensorLeft)*0.0048828125;  // value from sensor * (5/1024)
  float distanceLeft = 13*pow(voltsFront, -1); // worked out from datasheet graph

  if (distanceLeft <= Limit){
    CanGoForward = false;
  }
  else{
    CanGoForward = true;
    }
  Serial.print("LEFT SENSOR");
  Serial.println(distanceLeft);
  
  
 
 Serial.print("RIGHT");
 Serial.println(digitalRead(RightPin));
  Serial.print("LEFT");
 Serial.println(digitalRead(LeftPin));
   Serial.print("FORWARD");
 Serial.println(digitalRead(ForwardPin));
   Serial.print("BACK");
 Serial.println(digitalRead(BackwardPin));
  delay(1000);
  Serial.println();
  
  if(digitalRead(RightPin) == 1){
    Right();
  }
  else if(digitalRead(LeftPin) == 1){
    Left();
  }
  else if (digitalRead(LeftPin) == 0 || digitalRead(RightPin) == 0){
    StopAmotor();
  }
  
  
  if(digitalRead(ForwardPin) == 1){
    Forward(CanGoForward);
  }
  else if(digitalRead(BackwardPin) == 1){
    Backward();
  }
  else if (digitalRead(BackwardPin) == 0 || digitalRead(ForwardPin) == 0){
    StopBmotor();
  }

 
}


void Forward(bool can){
   if(can){
   Bmotor(100);
   }
   else{
    Bmotor(0);
    }
}

void Backward(){
   Bmotor(-100);
}
void StopBmotor(){
    Bmotor(0);
  }
void Left(){
   Amotor(-turnPower);
   delay(250);
   Amotor(0); 
}

void Right(){
   Amotor(turnPower);  
   delay(250);
   Amotor(0);
   }
void StopAmotor(){
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
