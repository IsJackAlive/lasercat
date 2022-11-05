/*
  07.08.2022
  PabloLaser v1.5
  
  Servo SG90:
  +5V, D2, GND 
  
  Laser:
  D11, GND

  Servo max angle: 60 (+1)  - dMax
  Servo speed (time): 200   - sTime
 */
 
#include <Servo.h>

Servo servo;

const int laserPin = 11;
const int dMax = 61;
const int sTime = 200;
int servoAngle = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("\nPablo 1.5");
  Serial.print("max angle: ");
  Serial.println(dMax);
  Serial.print("min time: ");
  Serial.println(sTime);
  
  pinMode(laserPin, OUTPUT);
  servo.attach(2);
  servo.write(0);
  delay(200);
}

void loop() {  
  pablo();

  digitalWrite(laserPin, LOW);  // Laser OFF
  Serial.println("========================\n");
  delay(2000);
}

void movdeg(int deg) {
//  int w = (deg+80)*3;
  printF("movdeg", deg, 0);
  for (servoAngle = 0; servoAngle <= dMax; servoAngle += deg) {
    digitalWrite(laserPin, LOW);
    servo.write(servoAngle);
    delay(400);
    digitalWrite(laserPin, HIGH);
    blinkk(3);
    delay(1000);
  }
  for (servoAngle -= deg; servoAngle >= 0; servoAngle -= deg) {
    digitalWrite(laserPin, LOW);
    servo.write(servoAngle);
//    delay(w);
    delay(400);
    digitalWrite(laserPin, HIGH);
    blinkk(3);
    delay(1000);
  }
}

void movrnd() {
  int rndang = random(0, dMax);
  printF("movrnd", rndang, 0);  
  digitalWrite(laserPin, LOW);
  servo.write(rndang);
  digitalWrite(laserPin, HIGH);
  delay(3000);
  servoAngle = servo.read();
}

void movlit(int a, int b, int m) {
  digitalWrite(laserPin, HIGH);
  int i;
  printF("movlit", a, b);  
  if (a > b) {
    for (int i = a; i > b; i--) {
      servo.write(i);
      delay(m);
    }
  }
  else {
    for (int i = a; i < b; i++) {
      servo.write(i);
      delay(m);
    }
  }
  digitalWrite(laserPin, LOW);
  servoAngle = servo.read();
}

void movstop(int a, int b, int n) {
  int i;
  int deg;
  printF("movstop", n, servoAngle);
  if (a > b) {
    deg = (a-b) / n;
    for (i = 0; i < n; i++) {
      a = servo.read();
      digitalWrite(laserPin, LOW);
      movlit(a, a-deg, 30);
      digitalWrite(laserPin, HIGH);
      delay(sTime*3);
    }
  }
  else {
    deg = (b-a) / n;
    for (i = 0; i < n; i++) {
      a = servo.read();
      digitalWrite(laserPin, LOW);
      movlit(a, a+deg, 30);
      digitalWrite(laserPin, HIGH);
      delay(sTime*3);
    }
  }
  servoAngle = servo.read();
}

void blinkk(int n) {
  printF("blinkk", n, 0);
  int i;
  for (i = 0; i < n; i++) {
    digitalWrite(laserPin, HIGH);  
    delay(200);
    digitalWrite(laserPin, LOW);
    delay(200);
  }
}

void printF(String namef, int p1, int p2) {
  Serial.print(namef);
  Serial.print("\tp1: ");
  Serial.print(p1);
  Serial.print("\tp2: ");
  Serial.println(p2);
}

void pablo() {
  int mode = random(2, 5);        // 2 - 4
//  int aang = random(179, 181);    // 179, 180 TODO
  printF("pablo", mode, 0);
  switch (mode) {
    case 2: {
      hideseek();
      break; }
      
    case 3: {
      shootingstars();
      break; }
      
    case 4: {
      lasercat();
      break; }    
  }
}

void hideseek() {
  int a = random(dMax);
  int b = random(dMax-20);
  int c = random(dMax-10);
  int hime = random(sTime, 500);
  int bb = random(7);
  printF("hideseek", 5, hime);

  movlit(b, a, hime);
  blinkk(bb);
  movlit(c, b, hime-50);
  movlit(a, c, hime+30);  
  blinkk(bb);
}

void shootingstars() {
  int a = random(dMax/2);
  int b = random(dMax);
  
  movdeg(a);
  movlit(0, a, sTime);
  movlit(a, dMax, sTime);
  movlit(a, 0, sTime);
  movrnd();
  movlit(servoAngle, a, sTime);
}

void lasercat() {
  int a = random(dMax);
  int b = random(dMax/2);
  int c = random(10);
  int t = sTime/2;
  
  movstop(a, b, c);
  movlit(a, b/2, t);
  movlit(b/2, a, t);
  movlit(a, b, t);
  movlit(b, a/2, t);
  movlit(servoAngle, 0, t);
}
