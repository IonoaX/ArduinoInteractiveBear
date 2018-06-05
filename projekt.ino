#include <MaxMatrix.h>

// Initalizing of Pinout / Variables
const int matrixvcc = 8;
const int motionsense = 2;
const int DIN = 7;  
const int CLK = 6; 
const int CS = 5;
const int maxInUse = 2;
const int statled = 13;
const int toparm = 10;
const int lowerarm = 11;
const int midblock = 12;
int baud = 9600;
int testp = 500;

//------------Define Matrix Clock Pins for Library------------
MaxMatrix m(DIN, CS, CLK, maxInUse); 

//----------------------Matrix Sprites------------------------

char cb1[] = {8, 8,
B00000110,
B00001011,
B00011010,
B00111010,
B00100010,
B00100010,
B00010011,
B00001110
                     };

char testpattern[] = {8, 8,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111
  }; 

char serialwake[] = {8, 8,
B11111111,
B11000001,
B10100001,
B10010001,
B10001001,
B10000101,
B10000011,
B11111111
  };

//-----------------Arduino Serial Startup--------------------

void serialstart() {
  Serial.begin(baud);
  Serial.println("Arduino, Interactive System -- Software V.01_dbg");
  delay(1000);
  Serial.println("System Startup..");
  Serial.println("Initalizing Parts..");
  delay(1000);
  Serial.println("---------------------------------------------");
  devinit();
  delay(500);
  Serial.println("---------------------------------------------");
  Serial.println("-- DONE --");
  Serial.println("-- Serial Debug --");
  }

//----------------Testsetup & Parts initalization----------------
void devinit() {
  digitalWrite(statled, HIGH);
  Serial.println("StatusLED on");
  digitalWrite(toparm, HIGH);
  Serial.println("Left Top/ Right Top: on");
  delay(testp);
  digitalWrite(toparm, LOW);
  digitalWrite(lowerarm, HIGH);
  Serial.println("Lower Left, Lower Right: on");
  Serial.println("Top Left / Right: off");
  delay(testp);
  digitalWrite(lowerarm, LOW);
  digitalWrite(midblock, HIGH);
  Serial.println("Middle Block: on");
  Serial.println("Lower Left / Right: off");
  delay(testp);
  digitalWrite(midblock, LOW);
  Serial.println("Mid Block: off");
  /*
   * Initalization of Sensors
   * like Distance Tracking or 
   * LLS Trigger goes here
   * and should be send to the
   * serial prompt for debug
   */
   matrix_tpstartup();
  }

void matrix_tpstartup() {
  digitalWrite(matrixvcc, HIGH);
  Serial.println("MatrixVCC powerup. Waiting 1 sec");
  delay(1000);
  m.writeSprite(0, 0, testpattern);
  Serial.println("Send Testpattern to Matrix");
  delay(1500);
  digitalWrite(matrixvcc, LOW);
  Serial.println("MatrixVCC powerdown");
  }

    void setup() {
      serialstart();
      m.init();
      m.setIntensity(15);
    }

//-------------System Loop for Arduino Code--------------------
    void loop() {
    if(digitalRead(2 == HIGH)) {
      Serial.println("Motion Detected && Matrix Startup");
      matrix_startup();
      displayMatrix();
      delay(500);
      }  
      else {
        matrix_powerdown();
        Serial.println("Matrix Powerdown");
        }
      while(digitalRead(matrixvcc) == LOW) {
        if (Serial.read() == DEC, "dev_wake") {
          Serial.println("Recieved Wakecommand: dev_startup");
          matrix_startup();
          m.writeSprite(0, 0, serialwake);
          delay(1000);
          m.clear();
          Serial.println("Matrix cleared");
          }
        }
    }

//--------------Define Startup Sequence for MAX----------------
void matrix_startup() {
  digitalWrite(matrixvcc, HIGH);
  }

//-------------Define Shutdown Sequence for MAX----------------
void matrix_powerdown() {
  digitalWrite(matrixvcc, LOW);
  }
  
/*--------------------Matrix Display Code ---------------------
------------------For printing out Sequences-----------------*/
void displayMatrix() {
  

      m.writeSprite(0, 0, cb1);
      delay(0);
      Serial.println("Wrote Sprite: cb1");
      

      for (int i=0; i<16; i++){
        m.shiftLeft(true, true);
        delay(250);
      }
      m.clear();
      Serial.println("Matrix Cleared");
  }


