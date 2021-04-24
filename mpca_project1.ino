#include <Adafruit_NeoPixel.h>
#include <Wire.h>


int ledPin= 3;	//pin for neopixel LED
int ledNo= 12;	
int tempPin = 1;	//pin used for temperature sensor (A1)
float temp;

Adafruit_NeoPixel strip= Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);

int minDistance = 100;
int maxDistance = 300;


int buzzerPin= 2;	//pin used for piezo buzzer(2)
int echoPin= 6;		//pin used for distance sensor (~6)
int trigPin= 5;


void setup(){
  
  //set the pin modes for buzzer, trigger, echo
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial. begin(9600);  
  
  strip.begin();
  for(int i = 0; i < ledNo; i++){
   strip.setPixelColor(i,strip.Color(0,0,0));	//setting color on led
  }
  strip.show();
  
  Wire.begin();		//start wire transmission
}

void loop() {
  
  int distance = calcDist();
  //function to calculate distance between sensor and nearest person 
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1);
  //if all leds are glowing, then the object is too close, 
  //buzzer rings
  if(ledsToGlow == 12){
    digitalWrite(buzzerPin, HIGH);
  }
  else{
    digitalWrite(buzzerPin, LOW);
  }
  
  //-----SETTING COLOURS ACC TO DISTANCE-------
  for(int i = 0; i < ledsToGlow; i++){
    if(i < 4){		//green colour
      strip.setPixelColor(i,strip.Color(50,0,0));//G,R,B
    }
    else if(i >= 4 && i < 8){	//yellow colour
      strip.setPixelColor(i,strip.Color(50,50,0));//G,R,B
    }
    else if(i >= 8 && i < 12){	//red colour
      strip.setPixelColor(i,strip.Color(0,50,0));//G,R,B
    }
  }
  
  for(int i = ledsToGlow; i < ledNo; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(25);
  
  
  //------------TEMP DETECTION----------------
  int itemp;
  temp = analogRead(tempPin);
  // read analog volt from sensor and save to variable temp
  temp = temp * 0.48828125;
  itemp = int(temp);
  //------------------------------------------
  
  
  //------------SEND DATA---------------------
  Wire.beginTransmission(4); 
  Wire.write(itemp);        
  Wire.endTransmission();   
  delay(100);
  //-------------------------------------------
  
}

int calcDist()
{
  long dist,duration;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  //echo is used to calculate distance between the object 
  //and sensor
  dist = duration / 29 / 2;
  
  if(dist >= maxDistance){
    dist = maxDistance;
  }
  
  if(dist <= minDistance){
    dist = minDistance;
  }
  return dist;
}