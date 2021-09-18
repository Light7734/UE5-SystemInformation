#pragma once

#include <vector>
#include <string>
#include "motherboardinfo.h"
#include "systemcommand.h"

class MotherboardInfoDelegate
{
public:
	MotherboardInfoDelegate();
	std::vector<MotherboardInfo> motherboardInfoVector() const;
	int numberOfMotherboardInfoItems() const;

private:
	std::vector<MotherboardInfo> _motherboardInfoVector;
	int _numberOfMotherboardInfoItems;

	void determineNumberOfMotherboardInfoItems(const std::vector<std::string> &data);
};

