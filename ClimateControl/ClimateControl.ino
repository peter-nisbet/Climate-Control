#include <SparkFun_Si7021_Breakout_Library.h>
#include <Wire.h>

float humidity = 0;
float tempC = 0;
int speedVal1 = 20;   //Speed value for exhaust fan
int speedVal2 = 0;    //Speed value for stimulation fan
int speedVal3 = 0;    //Speed value for input fan

long entry = 0;

//Change time of polling system in ms intervals.
unsigned long timeVal = 20000;  

char fanSpeed[7];

int fan1 = 3;   //Exhaust Fan
int fan2 = 5;   //Stimulation Fan
int fan3 = 6;   //Input Fan

Weather sensor;

//Function prototypes
void tempVal();
void printText();
void fanControlLoop();

void setup() {

  Serial.begin(9600); //Serial port begin at 9600 baud

  //Pin mode setup//

  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);

  //Begin Silabs sensor
  sensor.begin();
}

void loop() {
  
  tempVal();      //Get current temp value

  fanControlLoop();
  
  entry++;
  printText();

  delay(timeVal); //Sampling delay
}

void tempVal(){
  humidity = sensor.getRH();  //Triggers reading temperature and humidity
  tempC = sensor.getTemp();   //Reading temperature value from last humidity reading
}

int fanSpeedCon(int a){

  if(a == 0){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = a; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
     
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }
  else if(a == 70){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = a; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }
  else if(a == 100){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = a; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }
  else if(a == 130){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = 0; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }      
  else if(a == 170){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = 0; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }    
  else if(a == 255){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = 0; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }  
}

/*int fanSpeedCon(int a){

  if(a == 0){
     speedVal1 = a+23; //As the exhaust fan can't be off.
     speedVal2 = a+73; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
     
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }
  else if(a == 64){
     speedVal1 = a+35; //As the exhaust fan can't be off.
     speedVal2 = a-12; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }
  else if(a == 192){
     speedVal1 = a+40; //As the exhaust fan can't be off.
     speedVal2 = a-152; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }
  else if(a == 255){
     speedVal1 = a; //As the exhaust fan can't be off.
     speedVal2 = 0; //Keeps stimulation fan running a speed because the input fan is off.
     speedVal3 = a-25;   //Input fan is off.
         
     analogWrite(fan1, speedVal1);
     analogWrite(fan2, speedVal2);
     analogWrite(fan3, speedVal3);    
  }  
}*/

void printText(){
  Serial.print("Entry:");
  Serial.println(entry);
  Serial.print("Temp:");
  Serial.print(tempC);
  Serial.println("C");
  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Current Fan Speed:");
  Serial.println(fanSpeed); 
  Serial.print("Fan 1 speed:");
  Serial.println(speedVal1); 
  Serial.print("Fan 2 speed:");
  Serial.println(speedVal2);
  Serial.print("Fan 3 speed:");
  Serial.print(speedVal3);        
  Serial.print("\n\n");
}

void fanControlLoop(){

    memset(fanSpeed, 0, sizeof(fanSpeed));
    
    /*if(tempC>=18 && tempC<22){
      fanSpeedCon(64); //25% duty cycle
      strcpy(fanSpeed, "Low");
    }
    else if(tempC>=22 && tempC<30){
       fanSpeedCon(192); //75% duty cycle
       strcpy(fanSpeed, "Medium");
    }
    else if(tempC<18){
       fanSpeedCon(0); //0% duty cycle
       strcpy(fanSpeed, "Off");
    }
    else if(tempC>=30){
       fanSpeedCon(255);  //100% duty cycle
       strcpy(fanSpeed, "High");
    } */

    if(tempC>=21 && tempC<22){
      fanSpeedCon(70); //25% duty cycle
      strcpy(fanSpeed, "Low");
    }
    else if(tempC>=22 && tempC<23){
       fanSpeedCon(100); //75% duty cycle
       strcpy(fanSpeed, "Low-Medium");
    }   
    else if(tempC>=23 && tempC<24){
       fanSpeedCon(130); //75% duty cycle
       strcpy(fanSpeed, "Medium");
    }
    else if(tempC>=24 && tempC<25){
       fanSpeedCon(170); //75% duty cycle
       strcpy(fanSpeed, "Medium-High");
    }
    else if(tempC<21){
       fanSpeedCon(0); //0% duty cycle
       strcpy(fanSpeed, "Off");
    }
    else if(tempC>=25){
       fanSpeedCon(255);  //100% duty cycle
       strcpy(fanSpeed, "Max!");
    }       
}

