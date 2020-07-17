#include <LiquidCrystal.h>

#include <Servo.h>

#include <Keypad.h>


int C;
int L1=40;
int L2=20;
float Q1,Q2,M;
float X,Y,q1,q2;
int Q=60;
#include <Servo.h>
Servo motor1; 
Servo motor2;
#include <Keypad.h> 
const byte rows =4;
const byte cols =3;
char hexaKeys[rows][cols]={
  {'1','2','3'},
  {'4','5','6'},
  {' ','0',' '}
};
byte rowPins[rows]= {A2, A3, A4, A5};
byte colPins[cols]= {5, 6, 7};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, rows, cols);
#include <LiquidCrystal.h>
const int rs =13, en=12, d4=11, d5=10, d6=9, d7=8;
LiquidCrystal lcd(rs, en, d4, d5, d6,d7);

void setup() {
  // put your setup code here, to run once:
motor1.attach(3);
motor2.attach(4);
lcd.begin(16, 2);
lcd.print(" Warm Welcome to ");
lcd.setCursor(0,1);
lcd.println(" PNU Control Arm ");
delay(2000);}

void loop() {
  // put your main code here, to run repeatedly:
lcd.clear();
C= FI();
if (C==1){
  int G1=0, G2=0;
  int H1=0, H2=0;
  lcd.clear();
  lcd.print(" Please Enter angle Q1 ");
  while (G1==0) { G1=customKeypad.getKey();}
  lcd.setCursor(0,1);
  G1=G1-48;
  lcd.print(G2);
  delay(1000);
  q1=G1*10+G2;
  lcd.clear();
  lcd.print(" Please Enter angle Q2");
  while (H1==0) {H1=customKeypad.getKey();}
  H1=H1-48;
  lcd.setCursor(0,1);
  lcd.print(H1);
  while (H2==0) {H2=customKeypad.getKey();}
  H2= H2-48;
  lcd.print(H2);
  delay(1000);
  q2=H1*10+H2;
  forward();
}
else if (C==2){
  int U1=0 , U2=0;
  int R1=0, R2=0;
  lcd.clear();
  lcd.print(" Please Enter Value of X ");
  while (U1==0) { U1=customKeypad.getKey();}
  U1=U1-48;
  lcd.setCursor(0,1);
  lcd.print(U1);
  while (U2==0) {U2=customKeypad.getKey();}
  U2=U2-48;
  lcd.print(U2);
  delay(1000);
  X=U1*10+U2;
  lcd.clear();
  lcd.print(" Please Enter Value of Y ");
  while (R1==0) {R1=customKeypad.getKey();}
  R1=R1-48;
  lcd.setCursor(0,1);
  lcd.print(R1);
  while (R2==0) {R2=customKeypad.getKey();}
  R2= R2-48;
  lcd.print(R2);
  delay(1000);
  Y+R1*10+R2;
  invers();
}}
  int FI(){
    char kp=0;
    motor1.write(0);
    motor2.write(0);
    lcd.clear();
    lcd.print("Press 1 Forward");
    lcd.setCursor(0,1);
    lcd.print("Or 2 For Inverse");
    while(kp==0) {kp = customKeypad.getKey();}
    kp=kp-48;
    if(kp==1){
      lcd.clear();
      lcd.print(" Forward Kinematic ");
      lcd.setCursor(0,1);
      lcd.print(1);
      delay(3000);
      return 1;}
     else if (kp==2){
      lcd.clear();
      lcd.print(" Inverse Kinematic ");
      lcd.setCursor(0,1);
      lcd.print(2);
      delay(3000);
      return 2;}

      }
void forward(){
  motor1.write(q1);
  motor2.write(q2);
  lcd.clear();
  Q1=q1*PI/180;
  Q2=q2*PI/180;
  X=(L1*cos(Q1))+(L2*cos(Q1+Q2));
  Y=(L1*sin(Q1))+(L2*sin(Q1+Q2));
  lcd.print("END Point");
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(0,1);
  lcd.print(X);
  lcd.setCursor(6,1);
  lcd.print(Y);
  Serial.print("Q1");
  Serial.println(q1);
  Serial.print("Q2");
  Serial.println(q2);
  delay(7000);}

  void invers(){
    lcd.clear();
    M=(pow(X,2)+pow(Y,2)-pow(L1,2)-pow(L2,2)/(2*L1*L2));
    q2=acos(M);
    Q2=q2*180/PI;
    Q1=Q-Q1;
    lcd.print("Angle Of Arm:");
    lcd.setCursor(0,1);
    lcd.print("Q1=");
    lcd.print(Q1);
    lcd.setCursor(8,1);
    lcd.print("&");
    lcd.setCursor(9,1);
    lcd.print("Q2=");
    lcd.print(Q2);
    Serial.print(Q1);
    motor1.write(Q1);
    motor2.write(Q2);
    delay(7000);

}
