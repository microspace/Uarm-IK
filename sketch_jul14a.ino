#include <Servo.h>
#include <SPI.h>  
#include <Pixy.h>
//#include <StackArray.h>
#include <QueueArray.h>

//StackArray <float> stackx;
QueueArray <float> queuex;
// This is the main Pixy object 
Pixy pixy;
Servo base; 
Servo shoulder; 
Servo elbow; 
float alphaoffset = 10;
float betaoffset = 35;
float thetaoffset = 0; //need review
float alpha, beta, theta, beta_;
float x_target, y_target, z_target;
float x_offset, y_offset, z_offset;
float x, y, z;
float L3_, L3;
float L1 = 148;
float L2 = 160;
int xman,yman;
int xcar,ycar;
float averagex;
char command;

bool fillflag = false;
void setup() {
pinMode(7, OUTPUT);

queuex.setPrinter (Serial);
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
Serial.print("Starting...\n");
pixy.init();
}


void loop() {
  uint16_t blocks;
  blocks = pixy.getBlocks();
  if (blocks){
    x_target = pixy.blocks[0].x;
    y_target = pixy.blocks[0].y;
    queuex.enqueue (pixy.blocks[0].x);
    Serial.println(x_target);
  }
//    stacky.push(y_target);
if (queuex.count()>5) {
//Serial.println(stackx.pop()-stackx.pop());

if (abs(queuex.dequeue() - queuex.dequeue()) < 2 && fillflag == false) {
// этап заправки
digitalWrite(7, HIGH);
Serial.println("start ");
delay(2000);
digitalWrite(7, LOW);
fillflag = true;
command = 'n';
}

}

x = -1 * (x_target - 150);
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

if (Serial.available() > 0) {
       char incoming = Serial.read(); 
       if (incoming == 'f') {
        command = 'f';
        }
}


//if (command == 'f') {
        base.write(theta + thetaoffset); 
        shoulder.write(alpha + alphaoffset); 
        elbow.write(beta_ + betaoffset);
        delay(50);
//        fillflag = false;
//        }

  delay(100);
}
