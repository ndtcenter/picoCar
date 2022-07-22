#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 6
UART pc0(16, 17, -1, -1); //-1等价于NC
UART pc1(4, 5, NC, NC);  //NC=Not Connected
UART &pc = pc0;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;



// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) pc.print("0");
    pc.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  pc.print("Temp C: ");
  pc.print(tempC);
  pc.print(" Temp F: ");
  pc.print(DallasTemperature::toFahrenheit(tempC));
}

void printAlarms(uint8_t deviceAddress[])
{
  char temp;
  temp = sensors.getHighAlarmTemp(deviceAddress);
  pc.print("High Alarm: ");
  pc.print(temp, DEC);
  pc.print("C/");
  pc.print(DallasTemperature::toFahrenheit(temp));
  pc.print("F | Low Alarm: ");
  temp = sensors.getLowAlarmTemp(deviceAddress);
  pc.print(temp, DEC);
  pc.print("C/");
  pc.print(DallasTemperature::toFahrenheit(temp));
  pc.print("F");
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  pc.print("Device Address: ");
  printAddress(deviceAddress);
  pc.print(" ");
  printTemperature(deviceAddress);
  pc.println();
}

void checkAlarm(DeviceAddress deviceAddress)
{
  if (sensors.hasAlarm(deviceAddress))
  {
    pc.print("ALARM: ");
    printData(deviceAddress);
  }
}

void setup(void)
{
  // start pc port
  pc.begin(115200);
  pc.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  
  // locate devices on the bus
  pc.print("Found ");
  pc.print(sensors.getDeviceCount(), DEC);
  pc.println(" devices.");

  // search for devices on the bus and assign based on an index.
  if (!sensors.getAddress(insideThermometer, 0)) pc.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(outsideThermometer, 1)) pc.println("Unable to find address for Device 1"); 

  // show the addresses we found on the bus
  pc.print("Device 0 Address: ");
  printAddress(insideThermometer);
  pc.println();

  pc.print("Device 0 Alarms: ");
  printAlarms(insideThermometer);
  pc.println();
  
  pc.print("Device 1 Address: ");
  printAddress(outsideThermometer);
  pc.println();

  pc.print("Device 1 Alarms: ");
  printAlarms(outsideThermometer);
  pc.println();
  
  pc.println("Setting alarm temps...");

  // alarm when temp is higher than 30C
  sensors.setHighAlarmTemp(insideThermometer, 30);
  
  // alarm when temp is lower than -10C
  sensors.setLowAlarmTemp(insideThermometer, -10);
  
  // alarm when temp is higher than 31C
  sensors.setHighAlarmTemp(outsideThermometer, 31);
  
  // alarn when temp is lower than 27C
  sensors.setLowAlarmTemp(outsideThermometer, 27);
  
  pc.print("New Device 0 Alarms: ");
  printAlarms(insideThermometer);
  pc.println();
  
  pc.print("New Device 1 Alarms: ");
  printAlarms(outsideThermometer);
  pc.println();
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  pc.print("Requesting temperatures...");
  sensors.requestTemperatures();
  pc.println("DONE");

  // Method 1:
  // check each address individually for an alarm condition
  checkAlarm(insideThermometer);
  checkAlarm(outsideThermometer);
/*
  // Alternate method:
  // Search the bus and iterate through addresses of devices with alarms
  
  // space for the alarm device's address
  DeviceAddress alarmAddr;

  pc.println("Searching for alarms...");
  
  // resetAlarmSearch() must be called before calling alarmSearch()
  sensors.resetAlarmSearch();
  
  // alarmSearch() returns 0 when there are no devices with alarms
  while (sensors.alarmSearch(alarmAddr))
  {
    pc.print("ALARM: ");
    printData(alarmAddr);
  }
*/

}