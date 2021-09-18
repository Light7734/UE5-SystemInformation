#include "osinfodelegate.h"

#define OS_INFO_QUERY_STRING "wmic os get /format:list"
#define OS_INSTANCE_QUERY_STRING "PortableOperatingSystem="
#define OS_INFO_END_IDENTIFIER_STRING "WindowsDirectory="

OSInfoDelegate::OSInfoDelegate() :
    _numberOfOSInfoItems{0}
{
    FSystemCommand systemCommand(OS_INFO_QUERY_STRING);
    
	std::vector<std::string> tempVector = systemCommand.GetResult();
	if (!systemCommand.HasFailed()) {
		std::vector<std::string> raw = { systemCommand.GetResult() };
		determineNumberOfOSInfoItems(raw);
		std::vector<std::string> singleOSInfoItem;
		std::vector<std::string>::const_iterator iter = raw.begin();
		int osNumber = 0;
		while (osNumber < this->_numberOfOSInfoItems) {
			while (iter->find(OS_INFO_END_IDENTIFIER_STRING) == std::string::npos) {
				if ((*iter != "") && (*iter != "\r")) {
					singleOSInfoItem.push_back(*iter);
				}
				iter++;
			}
            singleOSInfoItem.push_back(*iter);
			this->_osInfoVector.emplace_back(singleOSInfoItem, osNumber);
			singleOSInfoItem.clear();
			iter++;
			osNumber++;
		}
    }
}

void OSInfoDelegate::determineNumberOfOSInfoItems(const std::vector<std::string> &data)
{
    for (auto iter = data.begin(); iter != data.end(); iter++) {
        if (iter->find(OS_INSTANCE_QUERY_STRING) != std::string::npos) {
            this->_numberOfOSInfoItems++;
        }
    }
}

int OSInfoDelegate::numberOfOSInfoItems() const
{
	return this->_numberOfOSInfoItems;
}

std::vector<OSInfo> OSInfoDelegate::osInfoVector() const
{
	return this->_osInfoVector;
}