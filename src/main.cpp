#include <Arduino.h>

#include <Communication_Manager.hpp>
#include <Thermometer_Sensor.hpp>
#include <ESP8266WiFi.h>

#define WLANSSID "WiFi-2.4-8876"
#define WLANPWD "wwcd92ppr6n4m"


Communication_Manager *mm;
Thermometer_Sensor *thermo;

void setup()
{
	Serial.begin(115200);
	mm = new Communication_Manager(WLANSSID, WLANPWD, "192.168.1.35", 1883, "superClient");
	thermo = new Thermometer_Sensor(0);
}


void loop()
{
	Serial.println("Hello");
	yield();

	mm->publish("test/topic", "hello world I am here " + std::to_string(5));

	float temp = thermo->measure_temperature_smoothed();
	mm->publish("test/temperature",  std::to_string(temp));
	delay(2000);


	mm->check_wifi_connection();
	mm->check_mqtt_connection();
}
