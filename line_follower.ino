#include<math.h>
int const_duration=200;
int en1=3;
int en2=5;
int int1=4;
int int2=7;
int int3=6;
int int4=2;
int mot_speed1=90;
int mot_speed2=90;
int s1=A1;
int s2=A2;
int s3=A0;
int s4=A3;
int s5=A4;
int a[5];
void setup() {
  // put your setup code here, to run once:
pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);
pinMode(int1,OUTPUT);
pinMode(int2,OUTPUT);
pinMode(int3,OUTPUT);
pinMode(int4,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
long reading=get_values();
float factor=time_factor(reading);
int duration=factor*const_duration;
Serial.println(duration);
//delay(const_duration*8);
Serial.println();
if(a[0]==0 && a[1]==0 && a[2]==0){delay(100);sharp_left();}
if(a[2]==0 && a[3]==0 && a[4]==0){delay(100);forward();}
if(a[0]==0 && a[1]==0){delay(100);sharp_right();}
if(a[0]==0 && a[1]==0 && a[2]==0 && a[3]==0 && a[4]==0){delay(100);reverse();}
decide(duration,reading);
}

void forward(){
analogWrite(en1,mot_speed1);
analogWrite(en2,mot_speed2);
digitalWrite(int1,HIGH);
digitalWrite(int2,LOW);
digitalWrite(int3,LOW);
digitalWrite(int4,HIGH);
delay(const_duration);
}

void right(int duration){
analogWrite(en1,mot_speed1);
analogWrite(en2,mot_speed2);
digitalWrite(int1,LOW);
digitalWrite(int2,HIGH);
digitalWrite(int3,LOW);
digitalWrite(int4,HIGH);
delay(duration);
}
void sharp_right(){
analogWrite(en1,255);
analogWrite(en2,255);
digitalWrite(int1,LOW);
digitalWrite(int2,HIGH);
digitalWrite(int3,LOW);
digitalWrite(int4,HIGH);
delay(const_duration);
}
void left(int duration){
analogWrite(en1,mot_speed1);
analogWrite(en2,mot_speed2);
digitalWrite(int1,HIGH);
digitalWrite(int2,LOW);
digitalWrite(int3,HIGH);
digitalWrite(int4,LOW);
delay(duration);
}
void sharp_left(){
analogWrite(en1,255);
analogWrite(en2,255);
digitalWrite(int1,HIGH);
digitalWrite(int2,LOW);
digitalWrite(int3,HIGH);
digitalWrite(int4,LOW);
delay(const_duration);
}

void reverse(){
analogWrite(en1,255);
analogWrite(en2,255);
digitalWrite(int1,LOW);
digitalWrite(int2,HIGH);
digitalWrite(int3,LOW);
digitalWrite(int4,HIGH);
delay(6*const_duration);
}
void stop_robot(int duration){
analogWrite(en1,0);
analogWrite(en2,0);
digitalWrite(int1,HIGH);
digitalWrite(int2,LOW);
digitalWrite(int3,LOW);
digitalWrite(int4,HIGH);
delay(duration);
}

void halt(int const_duration){
analogWrite(en1,0);
analogWrite(en2,0);
digitalWrite(int1,HIGH);
digitalWrite(int2,LOW);
digitalWrite(int3,LOW);
digitalWrite(int4,HIGH);
delay(const_duration*4);
}

long get_values(){
a[0]=analogRead(s1);
a[1]=analogRead(s2);
a[2]=analogRead(s3);
a[3]=analogRead(s4);
a[4]=analogRead(s5);
int threshold=512;
if(a[0]<threshold) a[0]=0;
else if(a[0]>threshold) a[0]=1;

if(a[1]<threshold) a[1]=0;
else if(a[1]>threshold) a[1]=1;

if(a[2]<threshold) a[2]=0;
else if(a[2]>threshold) a[2]=1;

if(a[3]<threshold) a[3]=0;
else if(a[3]>threshold) a[3]=1;

if(a[4]<threshold) a[4]=0;
else if(a[4]>threshold) a[4]=1;

Serial.println(a[0]);
Serial.println(a[1]);
Serial.println(a[2]);
Serial.println(a[3]);
Serial.println(a[4]);
long v=(5000*a[0]+4000*a[1]+3000*a[2]+2000*a[3]+1000*a[4])/(a[0]+a[1]+a[2]+a[3]+a[4]);
long mean_v = (int)v - 3000;
Serial.println(mean_v);
return mean_v;
}  

float time_factor(long mean_v){
    float factor=(float)mean_v/(float)1500;
    factor=abs(factor);
    Serial.println(factor);
    return factor;
}

void decide(int duration,long reading){
  if(reading>0 && reading<2000){
    right(duration);
  }
  else if(reading<0 && reading>-2000){
    left(duration);  
  }
  else{
    forward();
  }
}