#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/ServerArray.h"

namespace OpcUaStackServer
{

	ServerArray::ServerArray(void)
	: informationModel_()
	{
	}
	
	ServerArray::~ServerArray(void)
	{
	}

	void 
	ServerArray::informationModel(InformationModel::SPtr informationModel)
	{
		informationModel_ = informationModel;
	}

	void 
	ServerArray::serverArray(std::vector<std::string>& serverArray)
	{
		OpcUaVariant variant;
		informationModel_->getValue(OpcUaId_Server_ServerArray, AttributeId_Value, variant);
		for (int32_t idx=0; idx<variant.arrayLength(); idx++) {
			OpcUaString::SPtr stringValue = variant.variantSPtr<OpcUaString>((uint32_t)idx);
			serverArray.push_back(stringValue->value());
		}
	}

	bool 
	ServerArray::addServerName(const std::string& serverName)
	{
		OpcUaString::SPtr stringValue = OpcUaString::construct();
		*stringValue = serverName;

		OpcUaVariant variant;
		informationModel_->getValue(OpcUaId_Server_ServerArray, AttributeId_Value, variant);
		variant.pushBack(stringValue);
		informationModel_->setValue(OpcUaId_Server_ServerArray, AttributeId_Value, variant);
		return true;
	}

	int32_t 
	ServerArray::getServerIndex(const std::string& serverName)
	{
		std::vector<std::string>::iterator it;
		std::vector<std::string> serverArray;
		this->serverArray(serverArray);

		uint32_t serverIndex = 0;
		for (it = serverArray.begin(); it != serverArray.end(); it++) {
			if (*it == serverName) return serverIndex;
			serverIndex++;
		}

		return -1;
	}

	std::string 
	ServerArray::getServerName(uint32_t serverIndex)
	{
		std::vector<std::string> serverArray;
		this->serverArray(serverArray);

		if (serverIndex >= serverArray.size()) return "";
		return serverArray[serverIndex];
	}

	bool 
	ServerArray::existServerIndex(uint32_t serverIndex)
	{
		std::vector<std::string>::iterator it;
		std::vector<std::string> serverArray;
		this->serverArray(serverArray);

		if (serverArray.size() >= serverIndex) return false;
		return true;
	}
		
	bool 
	ServerArray::existServerName(const std::string& serverName)
	{
		return (getServerIndex(serverName) != -1);
	}
}