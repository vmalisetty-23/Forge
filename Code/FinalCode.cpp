const int trigPinL = 24;         
const int echoPinL = 25; 

const int trigPinR = 22;
const int echoPinR = 23;

          

const int switchPin = 26; 

int switch_read;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const int PIXEL_PIN  = A0; // Digital IO pin connected to the NeoPixels.

const int PIXEL_COUNT = 16;  // Number of NeoPixels

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

const int threshold = 5; 

float distanceL = 0;             
float distanceR = 0;

#include <Servo.h>
#include <LiquidCrystal.h> 


LiquidCrystal lcd(52, 53, 50, 51, 48, 49); 


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
  pinMode(switchPin, INPUT_PULLUP);
  myServo.attach(9);
  servoPosition = 90;



  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'


  lcd.setCursor(0, 0); 
  lcd.print("Initializing....");


  
  delay(1000);

  for (int i = 10; i <= 170; i++) {
    myServo.write(i);
    delay(10);
  }

    for (int i = 170; i >= 10; i--) {
    myServo.write(i);
    delay(10);
  }

  myServo.write(90);



}

void loop() {

  switch_read = digitalRead(switchPin);
 




  if (switch_read == LOW){
    lcd.clear();     
    lcd.setCursor(0, 0);              
    lcd.print("The device is");
    lcd.setCursor(0, 1);              
    lcd.print("turned off!");            
  }

  
  else{
  
  distanceL = getDistanceL();   
  distanceR = getDistanceR();

  servoPosition = constrain(servoPosition, 10, 170);
   
  if ((distanceL < threshold) && (distanceR < threshold)){
      lcd.clear();     
      lcd.setCursor(0, 1);              
      lcd.print("Hand over both sensors");
          
   }

   else if ((distanceL >=  threshold) && (distanceR >= threshold)){
     servoPosition += 0;
   }
 
   else if (distanceL < threshold) {
    servoPosition -= 10;
 
   }
   
   else if (distanceR < threshold) {
    servoPosition += 10;
    
   }

   


  currServoPosition = myServo.read();

  Serial.println(servoPosition);
  if (currServoPosition != servoPosition){
   myServo.write(servoPosition);}
//   



  printLCD(servoPosition);
  LED_Color(servoPosition);
  delay(200);  
  }


   

  



}



//------------------FUNCTIONS-------------------------------
void printLCD(int dial_pos){
  switch(dial_pos){
    case 10 ... 42:
      lcd.clear();
      lcd.setCursor(0, 0);              
      lcd.print("Setting 1");
      break; 

    case 43 ... 75:
      lcd.clear();
      lcd.setCursor(0, 0);              
      lcd.print("Setting 2");
      break;  

    case 76 ... 108:
      lcd.clear();
      lcd.setCursor(0, 0);              
      lcd.print("Setting 3");
      break; 

    case 109 ... 141:
      lcd.clear();
      lcd.setCursor(0, 0);              
      lcd.print("Setting 4");
      break;

    case 142 ... 174:
      lcd.clear();
      lcd.setCursor(0, 0);              
      lcd.print("Setting 5");
      break; 
  }
}

void LED_Color(int dial_pos){
  //To do
  switch(dial_pos){
    case 10 ... 42:
      colorWipe(strip.Color(  255,   100, 55));     
      break; 

    case 43 ... 75:
      colorWipe(strip.Color(  4,   30, 55));
      break;  

    case 76 ... 108:
      colorWipe(strip.Color(  55,   11, 255));

      break; 

    case 109 ... 141:
      colorWipe(strip.Color(  78,   150, 95));   
      break;

    case 142 ... 174:
       colorWipe(strip.Color(  0,   255, 0));
      break; 
  }
}

void colorWipe(uint32_t color) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
  }
}

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
