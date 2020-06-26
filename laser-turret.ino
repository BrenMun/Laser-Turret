#include<Servo.h>
Servo servoX;                         //X and Y axis servos
Servo servoY;

String serialData;

void setup() 
{
  servoX.attach(12);   //assign servo x to pin 12
  servoY.attach(13);   //assign servo y to pin 13
  Serial.begin(9600);
  Serial.setTimeout(10);  //set serial timeout to 10ms (default is 1000ms between each command)
}

/*Position Data is sent to the arduino via serial as a string with the format "X ... Y ..." - where "X" and "Y" indicate the coordinate and "..." being the 
  values corresponding to the x and y coordinates. The data needs to be parsed so that only the relevant values are written onto the X and Y servos*/


//parsing for the X servo involves removing all the subsequent Y data as well as the X index beforehand, leaving only the X coordinate values. 
int parseDataX (String data)            
{            
  data.remove(data.indexOf("Y"));       //removes all subsequent data starting from the Y index 
  data.remove(data.indexOf("X"), 1);    //removes the index of X, only removing 1 character 
  return data.toInt();                  //converts parsed data to an integer
}

//parsing for the Y servo involves removing all the data before the Y coordinate values
int parseDataY (String data)
{
  data.remove(0, data.indexOf("Y") + 1); //removes data starting from "X" up to the Y index (the count is Y_index + 1, since the first index is 0 not 1)

  return data.toInt();
}
void serialEvent() 

{                   
  serialData = Serial.readString(); //used to read out the current the serial string being sent to the arduino

  servoX.write(parseDataX(serialData));  //the serial data is parsed to fit X and written onto the servo
  servoY.write(parseDataY(serialData));  //the serial data is parsed to fit Y and written onto the servo
  
}

void loop() {}
