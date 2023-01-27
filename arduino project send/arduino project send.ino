#include <SoftwareSerial.h>
#include <IRremote.h>

int trig = 4;
int echo = 5;
int trig2 = 8;
int echo2 = 9;
int red = 10;
int green = 11;

SoftwareSerial P_Serial(6,7);//pin 6 RX 7 TX 로 사용하겠다
int state = 0;
int RECV_pin = 2;
IRrecv irrecv(RECV_pin);
decode_results results;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green,OUTPUT);

  irrecv.enableIRIn();
  P_Serial.begin(9600);//pin 6,7
  Serial.begin(9600);
}

void loop() {
  float cycletime,cycletime2;
  int distance, distance2;

  int remote = 0;
  if(irrecv.decode(&results)){//디코드 2번 이상 하면 에러
    remote = results.value;
    Serial.println(remote);
    irrecv.resume();//reset

    if(remote==26775){//리모컨 0 -> on
      state = HIGH;
    }
    else if(remote == 14535){//리모컨 5 -> off
      state = LOW;
    }
    digitalWrite(red,!state);
    digitalWrite(green,state);
  }

  if(state == HIGH){
    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);
  
    cycletime = pulseIn(echo, HIGH); 
    distance = ((340 * cycletime) / 10000) / 2;

    digitalWrite(trig2, HIGH);
    delay(10);
    digitalWrite(trig2, LOW);
  
    cycletime2 = pulseIn(echo2, HIGH); 
    distance2 = ((340 * cycletime2) / 10000) / 2;  

    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.print(", state : ");
    Serial.print(state);
    Serial.print("Distance2 : ");
    Serial.println(distance2);
  }

  String str = (String)distance + "#" + (String)state + "#" + (String)distance2;
  //if(state == 1){
    //Serial.println(str);
    P_Serial.println(str);
    //delay(500);
  //}
  delay(100);
}