#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int trigPin = 23; //Trig - green Jumper
int echoPin = 22; //Echo - yellow Jumper
long duration, cm;

void setup() 
  {
      myservo.attach(5);  // attaches the servo on pin 9 to the servo object
      Serial.begin (9600);
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
      pinMode(52, INPUT_PULLUP);
      pinMode(8, OUTPUT); // pin out lampu hijau
      pinMode(9, OUTPUT); // pin out lampu biru
      pinMode(10, OUTPUT); // pin out lampu kuning
      pinMode(11, OUTPUT); // pin out lampu merah
      pinMode(4, OUTPUT);  // pin out relay
  }

void loop()
  {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      cm = (duration/2) / 29.1;
      Serial.print(cm);
      Serial.print("cm");
      Serial.println();
      delay(300);

/////////////////kondisi led hijau on////////////////////        
      if(cm>16 && cm<19)
        {
           myservo.write(0);              // tell servo to go to position in variable 'pos'
           digitalWrite(8,1);
          digitalWrite(9,0);
          digitalWrite(10,0);
          digitalWrite(11,0);
        }
/////////////////kondisi led biru on////////////////////        
      else if(cm>13 && cm<15)
        {
           myservo.write(30);
          digitalWrite(8,0);
          digitalWrite(9,1);
          digitalWrite(10,0);
          digitalWrite(11,0);
        }
/////////////////kondisi led kuning on////////////////////        
      else if(cm>9 && cm<12)
        {
           myservo.write(55);
          digitalWrite(8,0);
          digitalWrite(9,0);
          digitalWrite(10,1);
          digitalWrite(11,0);
        }
/////////////////kondisi led merah on////////////////////        
      else if(cm>4 && cm<8)
        {
          myservo.write(80);
          digitalWrite(8,0);
          digitalWrite(9,0);
          digitalWrite(10,0);
          digitalWrite(11,1);
          digitalWrite(4,1);
          delay(300);
          digitalWrite(4,0);
          int x=1;
///////////// LED MERAH ON DAN SPIKER ON//////////////////
          while(x==1)
          {
              digitalWrite(trigPin, LOW);
              delayMicroseconds(5);
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigPin, LOW);
              pinMode(echoPin, INPUT);
              duration = pulseIn(echoPin, HIGH);
              cm = (duration/2) / 29.1;
              Serial.print(cm);
              Serial.print("cm");
              Serial.println();
              delay(300);
              
              int mm = digitalRead(52);
              if(mm==0)
                {
                  digitalWrite(4, 1);
                  }
/////////////BACA ULANG SENSOR UNTUK KEMBALI KE LED KUNING DAN SPEAKER OFF/////////////////
              else if(cm>9 && cm<11)
                  {
                     x=0;
                     int z=1;
                     myservo.write(55);   
                     digitalWrite(8,0);
                    digitalWrite(9,0);
                    digitalWrite(10,1);
                    digitalWrite(11,0);
                    digitalWrite(12,0);
                    //digitalWrite(4,1);
////////////////////KEMBALI KE PROGRAM AWAL////////////////////////
                    while(z==1)
                     {
                       digitalWrite(4,1);
                       delay(50);
                       digitalWrite(4,0);
                       delay(50);
                       digitalWrite(trigPin, LOW);
                       delayMicroseconds(5);
                       digitalWrite(trigPin, HIGH);
                       delayMicroseconds(10);
                       digitalWrite(trigPin, LOW);
                       pinMode(echoPin, INPUT);
                       duration = pulseIn(echoPin, HIGH);
                       delay(300);
                       if(cm>9 && cm<11)
                          {
                             x=0;
                             z=0;
                           }
                      }
                  }

               else
                   {
                  digitalWrite(4, 0);
                  }
          
          }          
        }
/////////////////kondisi push button////////////////////      
      int mm = digitalRead(52);
      if(mm==0)
        {
          digitalWrite(4, 1);
          }
     else
      {
         digitalWrite(4, 0);
      }
  }
