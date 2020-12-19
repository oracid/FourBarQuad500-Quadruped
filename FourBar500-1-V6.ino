// FourBar500-1-V6 reprend le code de:// C:\Users\charl\OneDrive\Documents\01-Robots\FourBar525-nwKine-1\Pgm\FourBar525-nwKine-1-V2 - 08/12/2020

void(* resetFunc) (void) = 0;           // soft reset
#include <Servo.h>
unsigned long start;
int Speed=500;            // Speed determines le speed
const int nb=8;                         // Number of servos
Servo Srv[nb];                          // Servos table
int OnOff[nb]={1,1,1,1,1,1,1,1};        // Servos table on/off
//int OnOff[nb]={0,0,0,0,0,0,0,0};        // Servos table on/off

int FRLS=0, FRRS=1, FLLS=2, FLRS=3, BRLS=4, BRRS=5, BLLS=6, BLRS=7;
//***************** Correction for 50° LS and RS servos position     **************************************
// servos      FRLS  FRRS  FLLS  FLRS  BRLS  BRRS  BLLS  BLRS modify these values according to your servos
int Err[nb]={   0,    2,    5,    5,    4,    7,    12,   2    };  
//*********************************************************************************************************
// 13/12/2020 - symetric Soucoupe volante V13-6 - Ay=160, a1=120, c1=88, Speed=500, 510cm/8V 
// 13/12/2020 - symetric Soucoupe volante V13-6 - Ay=165, a1=120, c1=88, Speed=500, 520cm/8V
// 13/12/2020 - symetric Soucoupe volante V13-6 - Ay=170, a1=120, c1=88, Speed=500, 500cm/8V
int FRx[]= { 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10,  5,  0, -5,-10,-15,-20,-25,-30,-35,-40,-45,-50,-55,-60,-65,-70,-75,-80,-85,    -85,-80,-75,-70,-65,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10, -5,  0,  5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85};
int FLx[]= { 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10,  5,  0, -5,-10,-15,-20,-25,-30,-35,-40,-45,-50,-55,-60,-65,-70,-75,-80,-85,    -85,-80,-75,-70,-65,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10, -5,  0,  5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85};
int BRx[]= {-85,-80,-75,-70,-65,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10, -5,  0,  5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85,     85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10,  5,  0, -5,-10,-15,-20,-25,-30,-35,-40,-45,-50,-55,-60,-65,-70,-75,-80,-85};
int BLx[]= {-85,-80,-75,-70,-65,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10, -5,  0,  5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85,     85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10,  5,  0, -5,-10,-15,-20,-25,-30,-35,-40,-45,-50,-55,-60,-65,-70,-75,-80,-85};

int FRy[]= {  0,-10,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-10,  0,      0,  3,  6,  8, 10, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 25, 25, 25, 25, 25, 25, 24, 23, 22, 21, 20, 18, 16, 14, 12, 10,  8,  6,  3,  0};
int FLy[]= {  0,  3,  6,  8, 10, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 25, 25, 25, 25, 25, 25, 24, 23, 22, 21, 20, 18, 16, 14, 12, 10,  8,  6,  3,  0,      0,-10,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-10,  0};
int BRy[]= {  0,  3,  6,  8, 10, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 25, 25, 25, 25, 25, 25, 24, 23, 22, 21, 20, 18, 16, 14, 12, 10,  8,  6,  3,  0,      0,-10,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-10,  0};
int BLy[]= {  0,-10,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-10,  0,      0,  3,  6,  8, 10, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 25, 25, 25, 25, 25, 25, 24, 23, 22, 21, 20, 18, 16, 14, 12, 10,  8,  6,  3,  0};

int lgTab = sizeof(FRx)/sizeof(int);
         
void  setup() {
  delay(900);                             // for reset consideration
  Serial.begin(9600);

  // Servos angle initialization
  int a=50;
  if(OnOff[FRLS]){ Srv[FRLS].attach(2); Srv[FRLS].write(    a+Err[FRLS]); } // FR Front Right leg - LS Left   Servo
  if(OnOff[FRRS]){ Srv[FRRS].attach(3); Srv[FRRS].write(180-a+Err[FRRS]); } // FR Front Right leg - RS Right  Servo
  if(OnOff[FLLS]){ Srv[FLLS].attach(4); Srv[FLLS].write(    a+Err[FLLS]); } // FL Front Left  leg - LS Left   Servo
  if(OnOff[FLRS]){ Srv[FLRS].attach(5); Srv[FLRS].write(180-a+Err[FLRS]); } // FL Front Left  leg - RS Right  Servo
  if(OnOff[BRLS]){ Srv[BRLS].attach(6); Srv[BRLS].write(    a+Err[BRLS]); } // BR Back  Right leg - LS Left   Servo
  if(OnOff[BRRS]){ Srv[BRRS].attach(7); Srv[BRRS].write(180-a+Err[BRRS]); } // BR Back  Right leg - RS Right  Servo
  if(OnOff[BLLS]){ Srv[BLLS].attach(8); Srv[BLLS].write(    a+Err[BLLS]); } // BL Back  Left  leg - LS Left   Servo
  if(OnOff[BLRS]){ Srv[BLRS].attach(9); Srv[BLRS].write(180-a+Err[BLRS]); } // BL Back  Left  leg - RS Right  Servo

  Serial.print("\n\t To start, click on the Start button");
  while( digitalRead(0) );  delay(400);       // waiting for start button pressed 
  Serial.print("\n\t Started");
  delay(10000);
  start=millis();
}

void loop() {
  if (! digitalRead(0)) resetFunc();
  if( millis()-start < 10000)  Forward();
//  Serial.print("\n\t start= ");Serial.print(start);Serial.print("\t\t temp= ");Serial.print(millis());Serial.print("\t\t diff= ");Serial.print(millis()-start);
}


void Walk(){
//  Forward();
//  for(int i=0;i<=10;i++) Forward();
//  for(int i=0;i<=5;i++) TurnLeft();
//  for(int i=0;i<=18;i++) TurnRight();
//  for(int i=0;i<=10;i++) Backward();
//  for(int i=0;i<=20;i++) Clockwise(4);
//  for(int i=0;i<=10;i++) Counterclockwise(4);
//  Circle(20);
}

void Circle(int r){
  for(int i=0;i<=8;i++) Clockwise(r);
}

void Forward(){
  for(int i=0;i<lgTab;i++){
    InverseKinematics(FRx[i],FRy[i],FRLS,FRRS);
    InverseKinematics(BLx[i],BLy[i],BLLS,BLRS);
    InverseKinematics(FLx[i],FLy[i],FLLS,FLRS);
    InverseKinematics(BRx[i],BRy[i],BRLS,BRRS);
  }
}

void Backward(){
  for(int i=0;i<lgTab;i++){
    InverseKinematics(FRx[i],FRy[i],BLLS,BLRS);
    InverseKinematics(BRx[i],BRy[i],FLLS,FLRS);
    InverseKinematics(FLx[i],FLy[i],BRLS,BRRS);
    InverseKinematics(BLx[i],BLy[i],FRLS,FRRS);
  }
}

void TurnLeft(){
  int savSpeed=Speed;
  Speed=1300;
  Clockwise(10);
  Speed=savSpeed;
}

void TurnRight(){
  int savSpeed=Speed;
  Speed=1300;
  Counterclockwise(10);
  Speed=savSpeed;
}

void Clockwise(int r){
  for(int i=0;i<lgTab;i++){
    InverseKinematics(FRx[i]  ,FRy[i],FRLS,FRRS);
    InverseKinematics(BRx[i]  ,BRy[i],BRLS,BRRS);
    InverseKinematics(FLx[i]/r,FLy[i],FLLS,FLRS);
    InverseKinematics(BLx[i]/r,BLy[i],BLLS,BLRS);
  }
}

void Counterclockwise(int r){
  for(int i=0;i<lgTab;i++){
    InverseKinematics(FRx[i]/r,FRy[i],FRLS,FRRS);
    InverseKinematics(BRx[i]/r,BRy[i],BRLS,BRRS);
    InverseKinematics(FLx[i]  ,FLy[i],FLLS,FLRS);
    InverseKinematics(BLx[i]  ,BLy[i],BLLS,BLRS);
  }
}

void InverseKinematics(int Px, int Py, int LS, int RS){
  const float A1x=0, A1y=165, A2x=0, A2y=165;                   // Values of servos positions
  const float a1=120, c1=88, a2=120, c2=88;                     // Values of leg sizes lengths

  float d=A1y-Py, e=Px;                                   // Calculation of inverse kinematics
  float b=sqrt((d*d)+(e*e));                              // Calculation of inverse kinematics
  float S=acos(d/b);  if(e<0)S=(-S);                      // Calculation of inverse kinematics
  float A12=acos(((b*b)+(c1*c1)-(a1*a1))/(2*b*c1));       // Calculation of inverse kinematics
  float A22=acos(((b*b)+(c2*c2)-(a2*a2))/(2*b*c2));       // Calculation of inverse kinematics
  float A11=(PI/2)-A12+S;                                 // Calculation of inverse kinematics
  float A21=(PI/2)-A22-S;                                 // Calculation of inverse kinematics
  int S1=round(A11*57.296);                               // left servo angle in degree
  int S2=round(180-(A21*57.296));                         // right servo angle in degree

// DEBUG
//  Serial.print("\n\n\t Position to reach : Px=");Serial.print(Px);Serial.print("  Py=");Serial.print(Py);
//  Serial.print("\n\t d=");Serial.print(d);Serial.print("\t\t e=");Serial.print(e);
//  Serial.print("\t\t b=");Serial.print(b);Serial.print("\t\t S=");Serial.print(S*57.296);
//  Serial.print("\n\t A11=");Serial.print(A11*57.296);Serial.print("\t\t A12=");Serial.print(A12*57.296);
//  Serial.print("\t\t A22=");Serial.print(A22*57.296);Serial.print("\t\t A21=");Serial.print(A21*57.296);
//  Serial.print("\n\t Result of calculations, angles of the servos");
//  Serial.print("\n\t S1=");Serial.print(S1);Serial.print("°\t\t\t S2=");Serial.print(S2);Serial.print("°");

  if ( b>(a1+c1) ){
    Serial.print("\n\t Target point Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print("\t b=");Serial.print(b);Serial.print(" > ");
    Serial.print(a1+c1);Serial.print(" is too long. Target impossible to reach   !!!!!");
    return;
  }
  if (S1+Err[LS]<0){
    Serial.print("\n\t Position to reach : Px=");Serial.print(Px);Serial.print("  Py=");Serial.print(Py);Serial.print("\t angle S1<0° is not reachable   !!!!!");
    return;
  }
  if (S2+Err[RS]>180){
    Serial.print("\n\t Position to reach : Px=");Serial.print(Px);Serial.print("  Py=");Serial.print(Py);Serial.print("\t angle S2<0° is not reachable   !!!!!");
    return;
  }
  if (S1+Err[LS]>120){
    Serial.print("\n\t Position to reach : Px=");Serial.print(Px);Serial.print("  Py=");Serial.print(Py);Serial.print("\t angle S1>140° is not reachable   !!!!!");
    return;
  }
  if (S2+Err[RS]<60){
    Serial.print("\n\t Position to reach : Px=");Serial.print(Px);Serial.print("  Py=");Serial.print(Py);Serial.print("\t angle S2<40° is not reachable   !!!!!");
    return;
  }
//  Serial.print("\t executed command");
  if (OnOff[LS]) Srv[LS].write(S1+Err[LS]);   // set target Left servo position if servo switch is On
  if (OnOff[RS]) Srv[RS].write(S2+Err[RS]);   // set target Right servo position if servo switch is On
  delayMicroseconds(Speed); 
}
