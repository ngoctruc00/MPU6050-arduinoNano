// giải mã mpu6050 ra góc.
#include "mpu6050.h"
#define  PI 3.141592654
#define  RAD2DEC 57.29577951
uint8_t data;
uint8_t data_raw[13];
#define accel_factor 16384.0
#define gyro_factor 16.4
#define alpha 0.98
float Goc_lech_X,Goc_lech_Y,Goc_lech_Z ;// khai báo biến 
float gyr_x, gyr_y,gyr_z;
float pwm_X, pwm_Y, pwm_Z,roll,pitch,yaw;
int pwmOut_X=9 ;
int pwmOut_Y=10 ;
int pwmOut_Z =11 ;
void setup() {
  // put your setup code here, to run once:
mpu6050();
Serial.begin(9600);


// set chân output pwm 
pinMode(pwmOut_X, OUTPUT); //Set chân 9 là output
pinMode(pwmOut_Y, OUTPUT); //Set chân 10 là output
pinMode(pwmOut_Z, OUTPUT); //Set chân 11 là output
}

void loop() {
 // put your main code here, to run repeatedly:
// Goc_lech_X = map(get_accx(),-16384,16384,0,180.0);// giải mã giá trị MPU 6050 sang độ ở trục X
// Goc_lech_Y = map(get_accy(),-16384,16384,0,180.0);// giải mã giá trị MPU 6050 sang độ ở trục Y
// Goc_lech_Z = map(get_accz(),-16384,16384,0,180.0);// giải mã giá trị MPU 6050 sang độ ở trục Z
Goc_lech_X = get_accx();
Goc_lech_Y = get_accy();
Goc_lech_Z = get_accz(); 
gyr_x = get_gyrox();


//
roll = atan2(Goc_lech_Y,Goc_lech_Z)*RAD2DEC;

pitch = atan(-Goc_lech_X/sqrt(Goc_lech_Y*Goc_lech_Y+Goc_lech_Z*Goc_lech_Z))*RAD2DEC;

yaw = atan ( sqrt (Goc_lech_X * Goc_lech_X + Goc_lech_Y * Goc_lech_Y)/ Goc_lech_Z)* RAD2DEC;

//roll = alpha*(roll+gyr_x*0.01)+(1-alpha)*atan(Goc_lech_Y/Goc_lech_Z)*180/3.141592654;

Serial.print("Góc lệch X là :");Serial.print(roll);// in ra màng hình góc lệch 
Serial.print(" Góc lệch Y là :");Serial.print(pitch);// in ra màng hình góc lệch 
Serial.print(" Góc lệch Z là :");Serial.println(yaw);// in ra màng hình góc lệch 

//pwm_X = map(roll, -180.00,180.00,0.0,200);
//pwm_Y = map(pitch,-180.00,180.00,0.0,221);// con này khác biệt tại thiết bị 
//pwm_Z = map(yaw,-180.00,180.00,0.0,200);

pwm_X = map(roll, -90.00,90.00,0.0,200);
pwm_Y = map(pitch,-90.00,90.00,0.0,221);// con này khác biệt tại thiết bị 
pwm_Z = map(yaw,-90.00,90.00,0.0,200);


  //Serial.print(" Xung X ");Serial.print(pwm_X);Serial.print("\n");  


// xuất PWM ra chân trên arduino nano
analogWrite(pwmOut_X, pwm_X);//D9
analogWrite(pwmOut_Y, pwm_Y);// D10
analogWrite(pwmOut_Z, pwm_Z);//D11
Serial.print("\n");
Serial.print("   ////x_pwm :");Serial.print(pwm_X);
Serial.print(" y_pwm : ");Serial.print(pwm_Y);
Serial.print(" z_pwm : ");Serial.print(pwm_Z);
Serial.print("\n");


delay(200);



}    
