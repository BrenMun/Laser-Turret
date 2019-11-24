#include<Servo.h>
Servo servoX;                         // X and Y axis servos
Servo servoY;

String serialData;

void setup() 
{
  servoX.attach(12);
  servoY.attach(13);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {}


void serialEvent()
{                   
  serialData = Serial.readString();

  servoX.write(parseDataX(serialData));  //write data onto servo x
  servoY.write(parseDataY(serialData));
  
}

//The format for the positioning data is X A Y B, where "A" and "B" are the values corresponding to the x and y position of the mouse.
//The data needs to be parsed so that only relevant data is written onto the servo


//parsing for the X servo involves removing Y and the X index, leaving only the number representing the X coordinate
int parseDataX (String data)            
{            
  data.remove(data.indexOf("Y"));       //remove index of Y to the end of the string
  data.remove(data.indexOf("X"), 1);    //remove index of X, only remove 1 character
  return data.toInt();                  //converts parsed data to an integer
}

//parsing for the Y servo involves the opposite
int parseDataY (String data)
{
  data.remove(0, data.indexOf("Y") + 1); //remove all of X and remove the index of Y, only read the number representing the y coordinate

  return data.toInt();
}
