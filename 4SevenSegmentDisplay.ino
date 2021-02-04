// Make sure the TimerOne library is installed on the IDE.
// Also, make sure that the segments and COMMON CATHODES are
// wired to the pins listed below

#include "TimerOne.h"

int A = 13;
int B = 12;
int C = 11;
int D = 10;
int E = 9;
int F = 8;
int G = 7;
int DP = 6;

int D4 = 5;
int D3 = 4;
int D2 = 3;
int D1 = 2;

long n = 0;
int count = 0;

int segments[8] = {A, B, C, D, E, F, G, DP};
int displays[4] = {D1, D2, D3, D4};

int numbers[][8] =  {{1,1,1,1,1,1,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},
  {1,0,1,1,1,1,1,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,0,0,1,1,0}
};

void setup() {
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  Timer1.initialize(10000);
  Timer1.attachInterrupt(add);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  inputNumber(8196);
  countTo10000();
}

void inputNumber(int x) {
  if (x/1000 >= 1){
    digit(0);
  pickNumber(x/1000);
  delay(5);
  }
  
  if ((x%1000/100) >= 1 ) {
    digit(1);
    pickNumber(x%1000/100);
    delay(5);
  }
  

  if ((x%100/10) >= 1) {
    digit(2);
    pickNumber(x%100/10);
    delay(5);
  }
  
  if ((x%10) >= 1) {
    digit(3);
    pickNumber(x%10);
    delay(5);
  }
  
}

void countTo10000() {
  clearLEDs();
  digit(0);
  pickNumber(n/1000);
  delay(5);
  
  clearLEDs();
  digit(1);
  pickNumber(n%1000/100);
  delay(5);

  clearLEDs();
  digit(2);
  pickNumber(n%100/10);
  delay(5);

  clearLEDs();
  digit(3);
  pickNumber(n%10);
  delay(5);
}

void add() {
  count++;
  if (count == 10){
    count = 0;
    n++;
    if (n==10000) {
      n = 0;
    }
  }
}

void digit(int d) {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  switch(d) {
    case 0:
      digitalWrite(D1, LOW);
      break;
    case 1:
      digitalWrite(D2, LOW);
      break;
    case 2:
      digitalWrite(D3, LOW);
      break;
    default:
      digitalWrite(D4, LOW);
      break;
  } 
}

void clearLEDs() {
  digitalWrite(A, LOW);
  digitalWrite(D, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
}

void pickNumber(int x) {
  for (int i = 0; i < sizeof(numbers[0])/sizeof(numbers[0][0]); i++) {
    digitalWrite(segments[i],numbers[x][i]); 
  }
}
