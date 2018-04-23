#include "stdafx.h"
#include <iostream>
#include "TemperatureSensor.h"

int main(int argc, char** args)
{
	TemperatureSensor sensor(12);
	std::cout << sensor.ParsedValue() << std::endl;
	std::cout << "Test" << std::endl;
	char temp;
	std::cin >> temp;
}