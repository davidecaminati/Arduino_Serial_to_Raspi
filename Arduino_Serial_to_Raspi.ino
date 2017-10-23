#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(2, 3); // RX, TX


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 7

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

void setup(void)
{
  // start serial port
  Serial.begin(4800);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  //mySerial.println("Hello, world?");
  
  sensors.begin();

  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  
  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 12);
 

}


void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  
  // It responds almost immediately. Let's print out the data
  //printTemperature(insideThermometer); // Use a simple function to print out the data
float tempC = sensors.getTempC(insideThermometer);
Serial.println(tempC);


if (mySerial.available()>0 )
	{
		if ((char)mySerial.read() == 't')
			{
			//mySerial.flush();
			mySerial.println(tempC);
			}

	}
delay(10);
}

/*  
--- RASPBERRY CODE ---
#!/usr/bin/env python

import serial

rot13 = string.maketrans( 
    "ABCDEFGHIJKLMabcdefghijklmNOPQRSTUVWXYZnopqrstuvwxyz", 
    "NOPQRSTUVWXYZnopqrstuvwxyzABCDEFGHIJKLMabcdefghijklm")

test=serial.Serial("/dev/ttyAMA0",4800)
test.open()

try:
    while True:
                line = test.readline()
                print(line)
                
except KeyboardInterrupt:
    pass # do cleanup here

test.close()
*/
