/*
 * This project is for wireless communication between two XBee modules. 
 * This is the code for the Transmitter XBee module. 
 * 
 * Authors William, Elvin och Hamoud
 */

#include <Printers.h>
#include <XBee.h>


XBee xbee = XBee();
uint8_t payload[2] ;
int Up = 0;
int Stop = 0;

void setup()
{
  Serial.begin(9600);
  xbee.setSerial(Serial);

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

}

void loop()
{
  Stop = digitalRead(6);
  Up = digitalRead(7);


  payload[0] = {NULL};

  if (Stop == LOW) {         //Körs då stop inte är tryckt
    
    if (Up == HIGH)
    {                          //Hissas upp
     digitalWrite(2, HIGH);
     digitalWrite(3, LOW);
      payload[0] = {'A'};
    }
    if (Up == LOW) {           //Hissas ner
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      payload[0] = {'B'};

    }
    digitalWrite(4, LOW);
  }                          // STOP if-sats
  if (Stop == HIGH) {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
  }
  Tx16Request tx16 = Tx16Request(0xFFFF, payload, sizeof(payload));

  xbee.send( tx16 );
  delay(200);

}
