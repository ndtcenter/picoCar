#include <Arduino.h>

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 6
const int DQ = 6;

const int led = LED_BUILTIN; //25
UART pc1(4, 5, NC, NC);      //deault to WiFi
UART pc0(16, 17, NC, NC);    //default to USB or 485
UART &pc = pc0;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  pc.begin(115200);
  pc.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  sensors.setWaitForConversion(false);
}

/*
 * Main function, get and show the temperature
 */
unsigned long tNextStart = 0;
unsigned long tNextRead = 800;
unsigned long tPrint =50;
void loop(void)
{
  if (millis() > tNextStart)
  {
    tNextStart += 1000; //下一次1000ms之后执行
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    pc.print("Requesting temperatures...");
    sensors.requestTemperatures(); // 设为不需要等待之后，这个函数启动转换之后立即返回
  }

  if (millis() > tNextRead)
  {
    tNextRead += 1000;
    pc.println("DONE");
    // After we got the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    float tempC = sensors.getTempCByIndex(0);

    // Check if reading was successful
    if (tempC != DEVICE_DISCONNECTED_C)
    {
      pc.print("Temperature for the device 1 (index 0) is: ");
      pc.println(tempC);
    }
    else
    {
      pc.println("Error: Could not read temperature data");
    }
  }

  //这里构造了另一个任务，每隔50ms打印当前时间
  if (millis() > tPrint){
    pc.print("cur t:");
    pc.println(millis());
    tPrint+=200;
  }

}
