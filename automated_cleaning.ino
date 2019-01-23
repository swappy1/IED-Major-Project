#include <SoftwareSerial.h>
#include <Servo.h>
// FIRST INPUT THE APPROPRIATE PIN NUMBERS

Servo ser;

SoftwareSerial mySerial(10,11);   //BLE 4.0 
int Data;       
int flag=0;

int enA=9;
int enB=0;

int en_mop=1;
const int mop1=8;
const int mop2=12;

const int trigger=2;    //Ultrasonic Sensor
const int echo=13;

int time_taken;
int dist;

int obstacle=100;      //distance of the machine from the obstacle    

const int motorPin1=4;   //const denotes that it can be used as int but its value can't be changed 
const int motorPin2=5;   //DC Motor
const int motorPin3=6;
const int motorPin4=7;

void setup() {
  // put your setup code here, to run once:
   mySerial.begin(9600);
   Serial.begin(9600);
   //pinMode(trigger,OUTPUT);
   //pinMode(echo,INPUT);

   pinMode(enA,OUTPUT);
   pinMode(enB,OUTPUT);
   pinMode(motorPin1,OUTPUT);    //See whether motor pins are to be intialized here or not
   pinMode(motorPin2,OUTPUT);
   pinMode(motorPin3,OUTPUT);
   pinMode(motorPin4,OUTPUT);

   pinMode(trigger,OUTPUT);
   pinMode(echo,INPUT);
   
   pinMode(en_mop,OUTPUT);
   pinMode(mop1,OUTPUT);
   pinMode(mop2,OUTPUT);
   
   ser.attach(3);
   ser.write(90);
   delay(1500);
   
   
   obstacle=distance();
   delay(100);
}

int left_look(){
  ser.write(35);
  delay(400);
  
  int d=distance();
  delay(110);

  ser.write(90);
  return d;
  
}

int right_look(){
  ser.write(145);
  delay(400);

  int d=distance();
  delay(110);

  ser.write(90);
  return d;
}


void loop() {
  // put your main code here, to run repeatedly:
    
   if (mySerial.available()>0)
  {
    Data=mySerial.read();
    flag=0;
    //Serial.print(Data);
    //Serial.println();
  

  int right_dist=0;
  int left_dist=0;
  delay(40);
  
//  if(obstacle<=10){    
//    stopmove();
//    delay(500);
//               // goes backward for 300/1500 milliseconds (whatever be the delay), might have to change in case want to go some centimeters backward
//    //right();
//    //stopmove();
//    //delay(200);
//  
//    //right();
//    //stopmove();
//    
//    right_dist=right_look();    // write code for right_look and left_look function
//    delay(200);
//    left_dist=left_look();
//    delay(200);
//
//    if(right_dist>=left_dist){
//      backward();
//      delay(1000);
//      right();
//      delay(500);
//      stopmove();
//    }
//
//    else{
//      backward();
//      delay(1000);
//      left();
//      delay(500);
//      stopmove();
//    }
//  }
//  else{
//    //left();
//    forward();
//    //right();
//  }

  if(Data=='1'){
    forward();
    delay(1000);
    flag=1;
  }
  else if(Data=='2'){
    left();
    delay(1000);
    flag=1;
  }
  else if(Data=='3'){
    backward();
    delay(1000);
    flag=1;
  }
  else if(Data=='4'){
    right();
    delay(1000);
    flag=1;
  }

  //up=1,left=2,down=3,right=4
  } 

  obstacle=distance();        //no delay specified

}
//int right_look{
//  ser.write(50);
//  delay(400);
//  
//  int d=distance();
//  delay(110);
//
//  ser.write(105);
//  return d;
//  
//}
//
//int left_look{
//  ser.write(170);
//  delay(400);
//
//  int d=distance();
//  delay(110);
//
//  ser.write(105);
//  return d;
//}

int distance(){
  
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  time_taken=pulseIn(echo,HIGH);
  dist=time_taken*0.034/2;
  //Serial.print(dist);
  //Serial.println();
  return dist;
}

void stopmove(){
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,LOW);
}

void backward(){
  analogWrite(enA,255);
  analogWrite(enB,255);
  //analogWrite(enA,0);
  //analogWrite(enB,0);
  digitalWrite(motorPin1,LOW); // LOW earlier
  digitalWrite(motorPin2,HIGH);
  digitalWrite(motorPin3,HIGH);
  digitalWrite(motorPin4,LOW);
}

void forward(){
  analogWrite(enA,255);
  analogWrite(enB,255);
  digitalWrite(motorPin1,HIGH);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,HIGH);
}

void right(){
  analogWrite(enA,255);
  analogWrite(enB,255);
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,HIGH);
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,HIGH);
}

void left(){
  analogWrite(enA,255);
  analogWrite(enB,255);
  digitalWrite(motorPin1,HIGH);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,HIGH);
  digitalWrite(motorPin4,LOW);
}

