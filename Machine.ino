// Spathoulas Dimitris 92206 : 3/11/2022 ®

// libraries
#include <Servo.h>
#include <AccelStepper.h>
#include <time.h>
#include <Stdlib.h>
#include <stdio.h>


// steppers
AccelStepper step2( 4 ,8,10,9,11);
AccelStepper step1( 4 ,2,5,3,6);
float maxs=512.;
float spd=256.;
float ac=64.;
float s1=0,s2=0;

// servo
int srv=A4; //pin analog
double pos=90.0; // deg 0.-180.
double pos2=45.0;
Servo servo; //call

// leds
int R=A0; // dig
int G=A2; // dig
int B=A1; // dig


//button
int b; // 0 || 1
int br=7; // pin

// variables
int i,j;
int n,m;
int dt=1000; // 1 sec 
int *a;



void setup() {
  // put your setup code here, to run once:
  
   srand(time(0));
   Serial.begin(9600);
  
  // motor 1
    step1.setSpeed(spd);
    step1.setAcceleration(ac);
    step1.setMaxSpeed(maxs);
  // motor 2
    step2.setSpeed(spd);
    step2.setAcceleration(ac);
    step2.setMaxSpeed(maxs);

  // servo
    servo.attach(srv,500,2400);
    
  // leds
      pinMode(R,OUTPUT);
      pinMode(G,OUTPUT);
      pinMode(B,OUTPUT);
      
  // button
      pinMode(br,INPUT);

    analogWrite(R,0);
    analogWrite(G,0);
    analogWrite(B,0);



    // !!!!!!!!!! HERE STARTS THE MAIN CODE !!!!!!!!

  
      Serial.println("Enter row of matrix (<=5) ");
      while (Serial.available()==0) {
    
  }

  m=Serial.parseInt();
  Serial.print("rows : ");
  Serial.println(m);
  Serial.println();
  Serial.println("Enter collum number (<=5) ");
  while (Serial.available()==0) {
    
  }

  n=Serial.parseInt();
  Serial.print("collums : ");
  Serial.println(n);
  Serial.println();
  if ( (n<=0) || (m<=0) ) {
    Serial.println("Size is negative or zero. Please restart program.");
    exit(1);
  }
  int *A=malloc((m*n)*sizeof(int));


  for (i<0;i<m;i++) {
    Serial.print("|");
    for (j=0;j<n;j++) {
     A[(i*n)+j]=rand()%2;
     Serial.print(A[(i*n)+j]);
     Serial.print("|");
    }
   Serial.println();
  }

  Serial.println();
  Serial.println();
  Serial.println("Enter any character to start proccess");
  while (Serial.available()==0) {
    
  }
  Serial.println("Initializing...");
   EXEC(A);
   EXIT(i);
}




void EXEC(int a[]) {
  
  i=0;
  j=0;
  
    /*s1=step1.currentPosition();
    s2=step2.currentPosition();
    analogWrite(R,255);
    delay(dt*3);
    step2.moveTo((n-1)*2048.); 
    step2.runToPosition();
    step2.moveTo(s2*2048.);
    step2.runToPosition();  */
  
    servo.write(0.0);
    analogWrite(R,0);
    analogWrite(G,255);
    analogWrite(B,0);
    Serial.println();
    Serial.println("Execution starts now!");
    Serial.println();
    b=digitalRead(br);
    while ( ( i < m ) && (b==1)  ) {
         analogWrite(G,0);
          step1.moveTo(i*2048.);
          step1.runToPosition();
          Serial.print("pos motor_1 :");
          Serial.println(step1.currentPosition());
          Serial.println();
           b=digitalRead(br);
          if (i%2==0) { j=0; 
            Serial.print("row is :"); Serial.println(i);  b=digitalRead(br);
            while ( (j<n) && (b==1)  ) { 
              if ( a[(i*n)+j]==1 ) { Serial.print("colum is :"); Serial.println(j);  b=digitalRead(br);
                step2.moveTo(j*2048.);
                step2.runToPosition();
                Serial.print("pos of motor 2 : ");
                Serial.println(step2.currentPosition());
                b=digitalRead(br);
                ser(); 
                b=digitalRead(br);
              }
            j++;
            }
             step2.moveTo((n-1)*2048.); step2.runToPosition(); 
          }
        
            if (i%2!=0) { j=n-1; 
                Serial.print("row is :"); Serial.println(i); 
                while ( (j>=0) && (b==1) ) { 
                  if ( a[(i*n)+j]==1 ) { Serial.print("colum is :"); Serial.println(j);
                    step2.moveTo(j*2048.); 
                    step2.runToPosition();
                    Serial.print("pos of motor 2 : ");
                    Serial.println(step2.currentPosition());
                    b=digitalRead(br);
                    ser();
                    b=digitalRead(br);
                  }
              j--;
              }
              step2.moveTo(s2*2048.); step2.runToPosition(); b=digitalRead(br);
           }
             
        i++; j=0; 
        }  
  
}


void EXIT(int I){
   analogWrite(R,255);
   analogWrite(G,0);
   analogWrite(B,0);
   step1.moveTo(s2);
   step1.runToPosition();
   step2.moveTo(s1);
   step2.runToPosition();
   Serial.println(I);
   if (I==m) {
     Serial.println("Procedure Executed Sucessfully");
     Serial.println("Please Exit Program");
 }
  if ( I<m ) {
    Serial.println("Program Interrupted..."); Serial.println("Please Exit Program");
  }

}



int ser() {
  
        delay(dt/2);
        servo.write(pos2);
        servo.write(pos);
        delay(dt*2);
        servo.write(pos2);
        servo.write(0.0);
        delay(dt*3);
        
}
