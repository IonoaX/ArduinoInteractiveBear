#include <Servo.h>
#include <MaxMatrix.h>

Servo movement;



const int CS = 5;
const int CLK = 6;
const int DIN = 7;
const int button = 2;
int maxInUse = 1;
int sequencestuptme = 125;
int addittime = 500;
int mvmt = 500;
int buttonstatus = 0;

MaxMatrix m(DIN, CS, CLK, maxInUse);

char start1[] = {8, 8, 
B00000000,
B00000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000000,
B00000000
};

char start2[] = {8, 8, 
B00000000,
B00000000,
B00011000,
B00100100,
B00100100,
B00011000,
B00000000,
B00000000
};

char start3[] = {8, 8, 
B00000000,
B00111100,
B01000010,
B01000010,
B01000010,
B01000010,
B00111100,
B00000000
};

char start4[] = {8, 8, 
B11111111,
B10000001,
B10000001,
B10000001,
B10000001,
B10000001,
B10000001,
B11111111
};

char sqr[] = {8, 8, 
B10000001,
B00000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000000,
B10000001
};

char sqr1[] = {8, 8, 
B10011001,
B00000000,
B00000000,
B10011001,
B10011001,
B00000000,
B00000000,
B10011001
};

void SerialINIT() {
  Serial.println("***************************");
  Serial.println("*                         *");
  Serial.println("*         Arduino         *");
  Serial.println("*     System Initalizer   *");
  Serial.println("*                         *");
  Serial.println("*                         *");
  Serial.println("***************************");
  Serial.println("ArduinoIDE: V1.8.5");
  Serial.println("Arduino Rev: Arduino / Genuino R1");
  Serial.println("ProjectVer: V1.01 Beta 10");
  }

void startupsequence() {
 for (int i=0; i<10; i++) {
    m.writeSprite(0, 0, start1);
    delay(sequencestuptme);
    m.writeSprite(0, 0, start2);
    delay(sequencestuptme);
    m.writeSprite(0, 0, start3);
    delay(sequencestuptme);
    m.writeSprite(0, 0, start4);  
    delay(sequencestuptme);
    }
    delay(sequencestuptme + addittime);
    m.clear();
    
  }


void setup() {
  Serial.begin(9600);
  SerialINIT();
  m.init();
  m.setIntensity(10);
  movement.attach(8);
  startupsequence();
  pinMode(button, INPUT);
  
  }

void menu() {
  Serial.println("Called menu()");
          m.writeSprite(0, 0, sqr);
          delay(2500);
          m.clear();
          for (int x; x<3; x++){
           if (buttonstatus == HIGH) {
            m.writeSprite(0, 0, sqr1);
            }
          }
  }

 void loop() {
  buttonstatus = digitalRead(button);

  if (buttonstatus == HIGH){
          menu();
          }
}


