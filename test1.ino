#include "mpu6050.h"
float Goc_lech_X ;// khai báo biến 
float Goc_lech_Y ;
float Goc_lech_Z ;
float pwm_X, pwm_Y, pwm_Z;
int pwmOut_X=8 ;
int pwmOut_Y=9 ;
int pwmOut_Z =10 ;
void setup() {
  // put your setup code here, to run once:
mpu6050();
Serial.begin(9600);
pinMode(pwmOut_X, OUTPUT); //Set chân 9 là output
pinMode(pwmOut_Y, OUTPUT); //Set chân 9 là output
pinMode(pwmOut_Z, OUTPUT); //Set chân 9 là output
}

void loop() {
 // put your main code here, to run repeatedly:
 Goc_lech_X = map(get_accx(),-16384,16384,0,180.0);// giải mã giá trị MPU 6050 sang độ ở trục X
 Goc_lech_Y = map(get_accy(),-16384,16384,0,180.0);// giải mã giá trị MPU 6050 sang độ ở trục Y
 Goc_lech_Z = map(get_accz(),-16384,16384,0,180.0);// giải mã giá trị MPU 6050 sang độ ở trục Z


Serial.print("Góc lệch X là :");Serial.print(Goc_lech_X);// in ra màng hình góc lệch 
Serial.print(" Góc lệch Y là :");Serial.print(Goc_lech_Y);// in ra màng hình góc lệch 
Serial.print(" Góc lệch Z là :");Serial.print(Goc_lech_Z);Serial.print("\n");// in ra màng hình góc lệch 

pwm_X = map(Goc_lech_X,0,180.0,0.0,200);
pwm_Y = map(Goc_lech_Y,-0,180.0,0.0,221);// con này khác biệt tại thiết bị 
pwm_Z = map(Goc_lech_Z,0,180.0,0.0,200);

//Serial.print(" Xung X ");Serial.print(pwm_X);Serial.print("\n");


// xuất PWM ra chân trên arduino nano
analogWrite(pwmOut_X, pwm_X);//D8
analogWrite(pwmOut_Y, pwm_Y);// D9 
analogWrite(pwmOut_Z, pwm_Z);//D10


delay(200);



}    
