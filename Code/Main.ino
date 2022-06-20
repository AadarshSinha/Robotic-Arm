#include <ESP32Servo.h>
#include <WiFi.h>;
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>;
#include <ArduinoJson.h>;
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define BLYNK_PRINT Serial
//Keyboard data//////////////////////////////////////
int KEY[8][4]={                                                                                                                                                                                                                                                      
               {130,112,56,78},          //space         
               {150,87,67,77},          // H
               {153,64,77,101},          // E
               {140,82,69,61},          // L
               {127,78,71,65},          // O
               {141,68,75,108},          // W
               {144,70,72,94},          // R
               {142,83,66,99},          // D
                          };
int hello[11]={1,2,3,3,4,0,5,4,6,3,7};
//wifi setup ///////////////////////////////////////
char ssid[] = "Saloni"; 
char pass[] = "Saloni123@";
char auth[] = "iq5cPxycufuZ5Zhh9wV5CE1Dr52wpbwE";

//Setup//////////////////////////////////////////////

Servo myservo[4];

//Pinouts////////////////////////////////////////////

const int servoPin[4]={5,19,18,23};  // servo pins
const int dfault[4]={70,70,40,90};  // servo pins


void setup() {
  Serial.begin(115200);
  
  // Servo Setup/////////////////////////////////////////
  
  Serial.println("Servo Motor setup started");
  for(int i=0;i<4;i++){  
      myservo[i].setPeriodHertz(50); 
      myservo[i].attach(servoPin[i]);  
  }
  Serial.println("Servo Motor setup Successful");
  
  //LIDAR setup///////////////////////////////////////////
  
  Serial.println("LIDAR setup started");
  while (! Serial) {
    delay(1);
  }
  if (!lox.begin()) {
    Serial.println("LIDAR setup Unuccessful");
  }
  else
  Serial.println("LIDAR setup Successful");


  // default position////////////////////////////////////// 
  Serial.println("Default setup started");
  for(int i=0;i<4;i++){
    myservo[i].write(dfault[i]);
  }
  Serial.println("DEFAULT setup Successful");
  // Blynk setup 
  Serial.println("BLYNK setup started");
    Blynk.begin(auth, ssid, pass,"blynk-cloud.com", 8080);
  Serial.println("BLYNK setup Successful");

 ////////HELLO WORLD CODE//////////////////////// 
 delay(2000);
  Serial.println("Typing Hello World");
  for(auto x : hello){
    for(int i=0;i<=3;i++){
      if(i!=2){
        servo(i,KEY[x][i]);
      }
    }
    servo(2,KEY[x][2]-5);
    servo(2,KEY[x][2]+1);    
    servo(2,dfault[2]);
  }
  Serial.println("Hello World Typed");
  
}
// Blynk pins
BLYNK_WRITE(V0){
  servo(0,param.asInt());
}
BLYNK_WRITE(V1){
  servo(1,param.asInt());
}
BLYNK_WRITE(V2){
  servo(2,param.asInt());
}
BLYNK_WRITE(V3){
  servo(3,param.asInt());
}
/////////////////////Slow motion/////////////////
void servo(int number,int degree){
  int temp=myservo[number].read();
  
  while(1){
    if(temp==degree)break;
    if(temp>degree)temp-=1;
    else temp+=1;
    myservo[number].write(temp);
    delay(20);
  }
}
////////////////////MAIN CODE //////////////////
void loop() {
  Blynk.run();
}
