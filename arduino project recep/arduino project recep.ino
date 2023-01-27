#include <SoftwareSerial.h> //아두이노 수신
#include <Stepper.h>

int red = 4;
int green = 3;
int state = 0;

SoftwareSerial P_Serial(6,7);
unsigned long current = 0;
unsigned long previous = 0;

char str[50]; //전체값저장
char *sArr[7]; //각각의 세싱 값 저장하는 변수
int stepsPerRev = 2048; //한바퀴
Stepper stepper (stepsPerRev, 11,9,10,8);

void setup() {
  Serial.begin(9600);
  P_Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  stepper.setSpeed(15);
}

void loop() {
  // put your main code here, to run repeatedly:
  int turn =0;
  int index = 0, i=0;
  char * ptr = NULL;
  while(P_Serial.available())
  {
    str[index++]=P_Serial.read();
  }
  str[index] = '\0';
  ptr = strtok(str, "#"); 

  while(ptr != NULL)
  {
    sArr[i++] = ptr;
    ptr = strtok(NULL, "#"); 
  }
  int a = atoi(sArr[0]);
  int b = atoi(sArr[1]);
  int c = atoi(sArr[2]);
  Serial.print("a : ");//왼쪽이 a, 오른쪽이 b
  Serial.print(a);
  Serial.print("  b : ");
  Serial.print(b);
  Serial.print("  c : ");
  Serial.println(c);
  delay(100);

if(b==1)
{
  if(a>10 && c<=10){
      turn = (stepsPerRev/8);
  }
  else if(a<=10 && c>10){
      turn = -(stepsPerRev/8);
  }
  else if(a>10 && c>10){
      digitalWrite(green, 1);
  }
  else if(a==0 && c==0) {
    digitalWrite(red, 0);
    digitalWrite(green, 0);
  }
  else{
      digitalWrite(red, 1);
  }
  stepper.step(turn);
  //delay(100);
  stepper.step(-turn);
   
  //delay(1000);
  digitalWrite(red, 0);
  digitalWrite(green, 0);
}
else if (b==0) 
{
  turn = 0;
  digitalWrite(red, 0);
  digitalWrite(green, 0);
}
}