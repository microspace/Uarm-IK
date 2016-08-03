#include <Servo.h>
#include <SPI.h>  


// This is the main Pixy object 

Servo base; 
Servo shoulder; 
Servo elbow; 

float alphaoffset = 10;
float betaoffset = 35;
float thetaoffset = 0;
float alpha, beta, theta, beta_;
float x_target, y_target, z_target;
float x_offset, y_offset, z_offset;
float x, y, z;

float L3_, L3;
float L1 = 148;
float L2 = 160;



void setup() {
base.attach(3, 700, 2250);
shoulder.attach(10, 700, 2250);
elbow.attach(9, 700, 2250);
Serial.begin(9600);
x_offset = 30;
y_offset = 0;
z_offset = 80;

x_target = 0;
y_target = 150;
z_target = 150;

}

void loop() {


x = x_target - x_offset;
y = y_target - y_offset;
z = z_target - z_offset;  
L3_ = sqrt(x*x + y*y);
theta = acos(x/L3_);
theta =  theta * 180 / 3.1415;
L3 = sqrt(x*x + y*y + z*z);

beta = 3.1415 - acos(((L1*L1 + L2*L2 - L3*L3)/(2 * L1 * L2)));
beta =  beta * 180 / 3.1415;

alpha = (acos((L1*L1+L3*L3-L2*L2)/(2*L1*L3)) + asin(z/L3)) *180 / 3.1415;
beta_ = beta - alpha;

base.write(theta + thetaoffset); 
shoulder.write(alpha + alphaoffset); 
elbow.write(beta_ + betaoffset);


delay(50);
}



