#pragma once

#include "Sensor.h"

class TemperatureSensor : protected Sensor {
public:
	TemperatureSensor(int i);
	virtual float ParsedValue();
};