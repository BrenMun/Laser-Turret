#include<Servo.h>
Servo servx;                         // X and Y axis servos
Servo servy;

String serialData;

void setup() {
  servx.attach(12);
  servy.attach(13);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {}


void serialEvent(){                   
  serialData = Serial.readString();

  servx.write(parseDataX(serialData));
  servy.write(parseDataY(serialData));
  
}

int parseDataX (String data){            
  data.remove(data.indexOf("Y"));       //remove index of Y from the end of the string
  data.remove(data.indexOf("X"), 1);    //remove index of X, only remove 1 character
  return data.toInt();
}
int parseDataY (String data){
  data.remove(0, data.indexOf("Y") + 1); //remove index of Y, only read the number representing the y coordinate

  return data.toInt();
}
