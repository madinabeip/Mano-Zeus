/*###########################################
## Author's github:    madport             ##
#############################################
*/

#include "ServoM.h"

enum
{
  PINSERVO1 = 7,
  PINSERVO2 = 8,
  PINSERVO3 = 9,
  PINSERVO4 = 10,
  PINSERVO5 = 11,
  PINSERVO6 = 12,

  NUMINVALUES = 6,
  DIGITSPERVAL = 1,
};
int acel = 200;
ServoM servo1 = ServoM(acel, -180, 180);
ServoM servo2 = ServoM(acel, -180, 180);
ServoM servo3 = ServoM(acel, -180, 180);
ServoM servo4 = ServoM(acel, -180, 180);
ServoM servo5 = ServoM(acel, -180, 180);
ServoM servo6 = ServoM(acel*2, -180, 180);

int valsIn[NUMINVALUES];
int stringLenght = NUMINVALUES * DIGITSPERVAL + 1;
int counter = 0;
bool counterStart = false;
String recivedString;


void setup() 
{
  Serial.begin(9600);
  
  servo1.attach(PINSERVO1);
  servo2.attach(PINSERVO2);
  servo3.attach(PINSERVO3);
  servo4.attach(PINSERVO4);
  servo5.attach(PINSERVO5);
  servo6.attach(PINSERVO6);
}


void receiveData()
{
  while(Serial.available())
  {
     char c = Serial.read();

     if (c=='$') {counterStart = true; }
     
     if (counterStart)
     {
      if (counter < stringLenght)
      {
        recivedString = String(recivedString+c);
        counter++;
      }
      if (counter >= stringLenght){
        for (int i = 0; i < NUMINVALUES ; i++){
          int num = (i*DIGITSPERVAL) + 1;
          valsIn[i] = recivedString.substring(num,num + DIGITSPERVAL).toInt();
        }
        recivedString = "";
        counter = 0;
        counterStart = false;
        
      }
     }
  }
}

void loop() 
{
  receiveData();
  if (valsIn[0] == 1){servo1.goTo(180); }
  else {servo1.goTo(0); }
  
  if (valsIn[1] == 1){servo2.goTo(180); }
  else {servo2.goTo(0); }
  
  if (valsIn[2] == 1){servo3.goTo(180); }
  else {servo3.goTo(0); }
  
  if (valsIn[3] == 1){servo4.goTo(180); }
  else {servo4.goTo(0); }
  
  if (valsIn[4] == 1){servo5.goTo(180); }
  else {servo5.goTo(0); }

  if (valsIn[5] == 1){servo6.goTo(180); }
  else {servo6.goTo(0); }
  }
