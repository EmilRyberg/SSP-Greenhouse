#pragma once

#include <vector>

class Sensor {
public:
	float ReadValue();
	virtual float ParsedValue() = 0;
protected:
	int pinNumber;
	float lastMeasurement;
	std::vector<float> buffer;
};