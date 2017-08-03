#include <SparkFun_Si7021_Breakout_Library.h>
#include <Wire.h>

#define ThermocoupleUse 1

//float humidity = 0;
float tempC = 0;
int speedVal = 0;
long entry = 0;
unsigned long timeVal = 10000;

int power = A3;
int GND = A2;

#ifdef ThermocoupleUse
int tempSense = A4;
char fanSpeed[7];
#endif

int fan1 = 3;
int fan2 = 5;
int fan3 = 6;

Weather sensor;

//Function prototypes
void tempVal();
void printText();
#ifdef ThermocoupleUse
  void thermocoupleTemp();
  void fanControlLoop();
#endif

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //Serial port begin at 9600 baud

  //Pin mode setup//
  pinMode(power, HIGH);             //Power
  pinMode(GND, LOW);              //GND

  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);

  digitalWrite(power, HIGH);
  digitalWrite(GND, LOW);

  //Begin Silabs sensor
  #ifndef ThermocoupleUse
    sensor.begin();
  #endif

}

void loop() {
  // put your main code here, to run repeatedly:
  #ifndef ThermocoupleUse
   tempVal();      //Get current temp value
  #else
    thermocoupleTemp();
  #endif

  fanControlLoop();
  
  entry++;
  printText();

  delay(timeVal); //5 minute delay
 /*if(tempC>=25 && tempC<30){
    fanSpeedCon(256); //25% duty cycle
 }
 else if(tempC>=30 && tempC<40){
    fanSpeedCon(768); //75% duty cycle
 }
 else if(tempC<25){
    fanSpeedCon(0); //0% duty cycle
 }
 else if(tempC>=40){
    fanSpeedCon(1023);  //100% duty cycle
 }*/
}

void tempVal(){
 // humidity = sensor.getRH();  //Triggers reading temperature and humidity
  tempC = sensor.getTemp();   //Reading temperature value from last humidity reading
}

int fanSpeedCon(int a){
  analogWrite(fan1, a);
  analogWrite(fan2, a);
  analogWrite(fan3, a);
}

void printText(){
  Serial.print("Entry:");
  Serial.print(entry);
  Serial.print("\n");
  Serial.print("Temp:");
  Serial.print(tempC);
  #ifndef ThermocoupleUse
    Serial.print("C\n");
  #else
    Serial.print("\n");
  #endif
    Serial.print("Current Fan Speed:");
    Serial.print(fanSpeed);  
    Serial.print("\n\n");
}

void thermocoupleTemp(){
  tempC = analogRead(tempSense);  //Raw ADC value, Need to convert to actual temp
}

void fanControlLoop(){
  #ifdef  ThermocoupleUse
    memset(fanSpeed, 0, sizeof(fanSpeed));
    
     if(tempC>=220 && tempC<420){
       fanSpeedCon(256); //25% duty cycle
       strcpy(fanSpeed, "Low");
     }
     else if(tempC>=420 && tempC<600){
       fanSpeedCon(768); //75% duty cycle
       strcpy(fanSpeed, "Medium");
     }
     else if(tempC<220){
       fanSpeedCon(0); //0% duty cycle
       strcpy(fanSpeed, "Off");
     }
     else if(tempC>=600){
       fanSpeedCon(1023);  //100% duty cycle
       strcpy(fanSpeed, "High");
     }
  #else
    if(tempC>=25 && tempC<30){
      fanSpeedCon(256); //25% duty cycle
    }
    else if(tempC>=30 && tempC<40){
       fanSpeedCon(768); //75% duty cycle
    }
    else if(tempC<25){
       fanSpeedCon(0); //0% duty cycle
    }
    else if(tempC>=40){
       fanSpeedCon(1023);  //100% duty cycle
    } 
  #endif 
}

