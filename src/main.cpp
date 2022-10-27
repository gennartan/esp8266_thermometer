#include <Arduino.h>

#include <Communication_Manager.hpp>
#include <Thermometer_Sensor.hpp>
#include <ESP8266WiFi.h>

#define WLANSSID "WiFi-2.4-8876"
#define WLANPWD "wwcd92ppr6n4m"

#define THERMOMETER_PIN 0
#define UPDATE_INTERVAL 30000

Communication_Manager *mm;
Thermometer_Sensor *thermo;

void setup()
{
	Serial.begin(115200);
	thermo = new Thermometer_Sensor(THERMOMETER_PIN);
	mm = new Communication_Manager(WLANSSID, WLANPWD, "192.168.1.35", 1883, thermo->get_name());
}

void loop()
{
	float temp = thermo->measure_temperature_smoothed();
	mm->publish("temperature/" + thermo->get_name(), std::to_string(temp));

	mm->check_wifi_connection();
	mm->check_mqtt_connection();

	delay(UPDATE_INTERVAL);
}
