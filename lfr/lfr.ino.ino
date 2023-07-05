
#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 

#define L_S A0 //ir sensor Left
#define C_S A1 //ir sensor centre
#define R_S A2 //ir sensor Right

#define echo A2    //Echo pin
#define trigger A3 //Trigger pin

//#define servo A5

//int Set=15;
//int distance_L, distance_F, distance_R; 

void setup(){ // put your setup code here, to run once

Serial.begin(9600); // start serial communication at 9600bps

pinMode(R_S, INPUT);//declare ir sensor input
pinMode(C_S, INPUT);// declare ir sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

analogWrite(enA, 200); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 200); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

//pinMode(servo, OUTPUT);

/* for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
 for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }

 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }

distance_F = Ultrasonic_read(); */

delay(500);
}


void loop(){  
//==============================================
//     Line Follower and Obstacle Avoiding
//==============================================  

//distance_F = Ultrasonic_read();
Serial.print(digitalRead(L_S));
Serial.print("left ");
Serial.print(digitalRead(C_S));
Serial.print("center ");
Serial.print(digitalRead(R_S));
Serial.print("right ");
Serial.print(digitalRead(2));
Serial.print("\n");




//if Right Sensor and Left Sensor are at White color then it will call forword function
 if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)&&(digitalRead(C_S) == 1)){
  forward();
                    
 }  

 if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)&&(digitalRead(C_S) == 1)){
  forward();
                    
 }  
//if Right Sensor is Black and Left Sensor is White then it will call turn Right function
 if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)&&(digitalRead(C_S) == 1)){
  turnRight();
                    
 }  
 if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)&&(digitalRead(C_S) == 0)){
  turnRight();
                    
 }  
 if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(C_S) == 1)){
  turnLeft();
                    
 }  
  if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)&&(digitalRead(C_S) == 0)){
  turnLeft();
                    
 }  
delay(10);
}




//**********************Ultrasonic_read****************************

void forward(){  //forword
analogWrite(enA, 200); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 200); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}

void backword(){ //backword
analogWrite(enA, 125); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 125); 
digitalWrite(in1, HIGH); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}

void turnRight(){ //turnRight
analogWrite(enA, 125); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 125);
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}

void turnLeft(){ //turnLeft
analogWrite(enA, 125); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 125);
digitalWrite(in1, HIGH); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
