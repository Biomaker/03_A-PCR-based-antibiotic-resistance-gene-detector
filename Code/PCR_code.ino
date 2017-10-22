//Input cycle parameters here:
const int NumberCycle = 35; //Number of PCR Cycles
const int HighTemp = 90; //Peak PCR temperature
const int LowTemp = 60;  //Troth PCR temperature
const int HighTime = 10000; //Time maintained at peak PCR temperature in ms
const int LowTime = 10000;  //Time maintained at troth PCR temperature in ms

//Pin and library set up
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
const int temperaturePin = A0;
const int heat = 5;
const int fan = 8;
const int cool = 9;
//In code variables set up
int counter = 0;
int temperature = 0;

void setup() {
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 255);
  lcd.print("Temperature:");

//Set up Pin Types
  pinMode(heat, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(cool, OUTPUT);
  Serial.begin(9600);
}


void loop(){
  lcd.setCursor(13, 0);
  lcd.print(counter);
  
  if(counter < NumberCycle){

//Rise to Peak
    Serial.println("PhaseOne");
    Rise(HighTemp);
    Serial.println("PhaseOneEnd");
    
//Hold Peak
  Serial.println("PhaseTwo");
  long startTime = millis();
  delay(10);
  while(millis() - startTime <= HighTime){
    Hold(HighTemp);
  }
  Serial.println("PhaseTwoEnd");

  
//Fall to Low
  Serial.println("PhaseThree");
  Fall(LowTemp);
  Serial.println("PhaseThreeEnd");

//Hold at Low
  Serial.println("PhaseFour");
  startTime = millis();
  delay(10);
  while(millis()-startTime <= LowTime){
    Hold(LowTemp);
  }
 Serial.println("PhaseFourEnd");

//Count finished cycle
 counter = counter + 1;
}//if end
//Cool down after all cycles are complete
  Cold;
}//void loop end

//+++++++++++++++++++++++++++++++++++Functions+++++++++++++++++++++++++++++++++++++++++\\

// Temperature collection method
float Temp(int pin){
  
  //Sensor Dependent code 
  int a = analogRead(pin);
  float R = 1023.0/a-1.0;
  R = 100000*R; 
  float temperature = 1.0/(log(R/100000)/4275+1/298.15)-273.15;
  //End of Sensor dependent code
  
  return(temperature);
}

//Holds a desiered temp
void Hold(int control){
  temperature = Display(temperaturePin);
  if ((temperature) > control) {
      Cold;
      }else{
      Hot;
      }
}


//Temperature rise
void Rise(int HighTemp){
  temperature = Display(temperaturePin);
  while( (temperature) <= HighTemp){
        Hot;
        temperature = Display(temperaturePin);
  }
}


//Fall in temperature till LowTemp
void Fall(int LowTemp){
  temperature = Display(temperaturePin);
  while((temperature - 5) > LowTemp){
      Cold; 
      temperature = Display(temperaturePin);
  }
}

//Cooling function
void Cold(){
  digitalWrite(heat, LOW);
      digitalWrite(fan, HIGH);
      digitalWrite(cool, LOW);
      lcd.setRGB(0, 0, 255);  
}

//Heating function
void Hot(){
  digitalWrite(heat, HIGH);
        digitalWrite(fan, LOW);
        digitalWrite(cool, HIGH);
        lcd.setRGB(255, 0, 0);
}

//Check and display temperature
float Display(int temperaturePin){
  temperature = Temp(temperaturePin);
  Serial.println(temperature);
        lcd.setCursor(0, 1);
          lcd.print(temperature);
          lcd.setCursor(7, 1);
          lcd.print("Degrees C");
        delay(10);
        return(temperature);
}
