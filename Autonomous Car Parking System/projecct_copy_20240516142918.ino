#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>

Servo myservo1;
int m_pin=8;
int s1_echo=6;
int s1_trig=7;
int s2_echo=12;
int s2_trig=11;
int s3_echo=10;
int s3_trig=9;
float s1_duration, s2_duration, s3_duration;
int s1_distance, s2_distance, s3_distance;
int IR1 = 2;
int IR2 = 3;
int Slot = 3;
int flag1 = 0;
int flag2 = 0;
String c1="mt",c2="mt",c3="mt";
void u1(){
  digitalWrite(s1_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(s1_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(s1_trig,LOW);
  s1_duration= pulseIn(s1_echo,HIGH);
  s1_distance=(s1_duration*0.0343)/2;
}
void u2(){
  digitalWrite(s2_trig,LOW);
  delayMicroseconds(2);
   digitalWrite(s2_trig,HIGH);
   delayMicroseconds(10);
  
  digitalWrite(s2_trig,LOW);
  s2_duration= pulseIn(s2_echo,HIGH);
    s2_distance=(s2_duration*0.0343)/2;
}
void u3(){
   digitalWrite(s3_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(s3_trig,HIGH);   
  delayMicroseconds(10);
  digitalWrite(s3_trig,LOW);
    s3_duration= pulseIn(s3_echo,HIGH);
  

  s3_distance=(s3_duration*0.0343)/2;
  
}
void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(s1_trig, OUTPUT);
  pinMode(s2_trig, OUTPUT);
  pinMode(s3_trig, OUTPUT);
pinMode(s1_echo,INPUT);
pinMode(s2_echo,INPUT );
pinMode(s3_echo,INPUT);
myservo1.attach(m_pin);
myservo1.write(-2);

lcd.setCursor(0, 0);
lcd.print("  Autonomous    ");
lcd.setCursor(0, 1);
lcd.print(" PARKING SYSTEM ");
delay(2000);
lcd.clear();
Serial.begin(115200);
}

void loop() {
  u1();
  u2();
  u3();
  Serial.print("Distance s1 :  ");
  Serial.println(s1_distance);
  Serial.print("Distance s2 :  ");
  Serial.println(s2_distance);
  Serial.print("Distance s3 :  ");
  Serial.println(s3_distance); 
  if((s1_distance<18)){
    c1="Fill";
  }else{
    c1="null";
  }
  if(s2_distance<18){
    c2="Fill";
  }
  else{
    c2="null";
  }
   if(s3_distance<18){  
    c3="Fill";
  }
  else{
    c3="null";
  }
  if (digitalRead(IR2) == LOW && flag1 == 0) {
    if (!((c1=="Fill")&&(c2=="Fill")&&(c3=="Fill"))) {
      flag1 = 1;
      if (flag2 == 0) {
        for (int j = 0; j <= 90; j += 1) {
          myservo1.write(j);
          delay(20);
        }
        Slot = Slot - 1;
        
      }
    }  else {
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }
  }
  

  if (digitalRead(IR1) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      for (int k = 0; k <= 90; k++) {
        myservo1.write(k);
        delay(19);
      }
      Slot = Slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    for (int k = 91; k >= 0; k--) {
      myservo1.write(k);
      delay(17);
    }
    flag1 = 0, flag2 = 0;
  }

  // lcd.setCursor(0, 0);
  // lcd.print("    WELCOME!    ");
  // lcd.setCursor(0, 1);
  // lcd.print("Slot Left: ");
  // lcd.print(Slot);
  // delay(2000);

  lcd.setCursor(0,0);
  lcd.print("L1:");
  lcd.print(c1);
  lcd.setCursor(8,0);
  lcd.print("L2:");
  lcd.print(c2);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
  lcd.setCursor(0,1);
  lcd.print("L3:");
  lcd.print(c3);
   
}