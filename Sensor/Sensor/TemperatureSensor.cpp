#include "stdafx.h"
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int i)
{
	pinNumber = i;
}

float TemperatureSensor::ParsedValue()
{
	return ReadValue() * 1.5;
}