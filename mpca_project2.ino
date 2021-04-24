#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 	//initialising the pins for lcd display

void setup() {
  lcd.begin(16, 2);			//sets the lcd to hold 16 characters
  							//and 2 lines
  lcd.setCursor(0,0);		//setting the cursor to the first point 
  							//in the lcd 
  lcd.print("Temperature: ");
  Wire.begin(4);                
  Wire.onReceive(receiveEvent); 	//on receiving the data, receiveEvent
  									//function is called	
  Serial.begin(9600); 
}


void loop() {
  delay(10);
}

 
void receiveEvent(int howMany)
{
  int c = Wire.read(); 
  Serial.println(c);  
  lcd.setCursor(0,1);		//setting the cursor to second line to write
  							//the temperature received
  lcd.print(c);
}