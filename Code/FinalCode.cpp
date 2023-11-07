const int trigPinL = 11;         
const int echoPinL = 12;           
const int trigPinR = 6;
const int echoPinR = 7;
//const int LED = 13;





float distanceL = 0;             
float distanceR = 0;

#include <Servo.h>
#include <LiquidCrystal.h> 


LiquidCrystal lcd(10, 8, 5, 4, 3, 2); 


 Servo myServo;

 int servoPosition; 
 int currServoPosition;



void setup() {
    lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();   

  Serial.begin (9600);        

  pinMode(trigPinL, OUTPUT);  
  pinMode(echoPinL, INPUT);    
  pinMode(trigPinR, OUTPUT);   
  pinMode(echoPinR, INPUT); 
  pinMode(13, OUTPUT);
  myServo.attach(9);
  servoPosition = 90;

  
  lcd.setCursor(0, 0); 
  lcd.print("Initializing....");

  myServo.write(90);
  
  delay(1000);

  for (int i = 10; i <= 170; i++) {
    myServo.write(i);
    delay(10);
  }



  
  

}

void loop() {
   distanceL = getDistanceL();   
   distanceR = getDistanceR();

//   Serial.println("--------------------------");
//   Serial.print("Left Sensor ");
//   Serial.println(distanceL);
//   Serial.print("Right Sensor ");
//   Serial.println(distanceR);

   if (distanceL < 5 && distanceR < 5){

    lcd.setCursor(0, 1);              //set the cursor to the 0,0 position (top left corner)
   lcd.print("Hand over both sensors");
    digitalWrite(13, HIGH);
  
    }

    
   if (distanceL < 5) {
    servoPosition =  servoPosition - (5/distanceL);
        digitalWrite(13, LOW);
   }


    if (distanceR < 5) {
    servoPosition =  servoPosition + (5/distanceR);
        digitalWrite(13, LOW);
   }

//
//  if (newServoPosition != servoPosition){
     Serial.println(servoPosition);
   

   servoPosition = constrain(servoPosition, 10, 170);

  currServoPosition = myServo.read();


  if (currServoPosition != servoPosition){
   myServo.write(servoPosition);}

   if ((servoPosition>= 10) && (servoPosition <= 42)){
    lcd.clear();
    
     lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
      lcd.print("Setting 1");
    }

   if ((servoPosition>= 43) && (servoPosition <= 75)){
    lcd.clear();
     lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
   lcd.print("Setting 2");
    }


   if ((servoPosition>= 76) && (servoPosition <= 108)){
    lcd.clear();
      lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Setting 3");
    }


   
   if ((servoPosition>= 109) && (servoPosition <= 141)){
    lcd.clear();
     lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Setting 4");
    }

      
   if ((servoPosition>= 142) && (servoPosition <= 174)){
    lcd.clear();
     lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Setting 5");
    }

   


   


 delay(50);      

 

}



//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistanceL()
{
  float echoTime;                  
  float calculatedDistance;         


  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);

  echoTime = pulseIn(echoPinL, HIGH);      
                                     

  calculatedDistance = echoTime / 148.0;  

  return calculatedDistance;              
}


float getDistanceR()
{
  float echoTime;                  
  float calculatedDistance;         

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);

  echoTime = pulseIn(echoPinR, HIGH);      
                                         

  calculatedDistance = echoTime / 148.0;  

  return calculatedDistance;            
}