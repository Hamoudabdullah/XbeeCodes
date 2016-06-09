/*
   This project is for wireless communication between two XBee modules.
   This is the code for the receiving XBee module.

   Authors William, Elvin och Hamoud
*/

#include <Printers.h>
#include <XBee.h>


XBee xbee1 = XBee();


XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();

int data = 0;
int i = 0;
int k = 0;

void setup()
{
  Serial.begin(9600);
  xbee1.setSerial(Serial);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);

  //DIRECTION
  pinMode(3, OUTPUT);             //IN_1
  pinMode(11, OUTPUT);            //IN_2
  //SLEEP MODE
  pinMode(12, OUTPUT);            //INH_1
  pinMode(13, OUTPUT);            //INH_2

  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);


}

void loop()
{

  xbee1.readPacket(100);

  //-------------------------------------------------------------------------------------------------------------------------------------
  if (xbee1.getResponse().isAvailable())                                    //Xbee 1
  {

    if (xbee1.getResponse().getApiId() == RX_16_RESPONSE)
    {
      xbee1.getResponse().getRx16Response(rx16);
      data = rx16.getData(0);

      Serial.print(" XBee1: ");
      Serial.print( data );
      Serial.print("\n");
      delay(1);
    }

  }
  if (data == 66) {               // Hissas upp
                                  //Hissas sakta upp
    digitalWrite(2, HIGH);
    analogWrite(3, i);
    delay(100);
    if (i != 255) {
      i = i + 1;
    }
  }

  else if (data == 65) {          // Hissas ner
    //Hissas sakta upp
    digitalWrite(2, LOW);
    analogWrite(11, k);
    delay(100);
    if (k != 255) {
      k = k + 1;
    }
  } 
  

 
  

  if (data == 0) {
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);
    analogWrite(3, 0);
    analogWrite(11, 0);
    k=0;
    i=0;
  }
  if (data != 0) {
    digitalWrite(4, LOW);
  }
}

