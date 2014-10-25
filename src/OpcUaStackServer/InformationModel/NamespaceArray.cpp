#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/NamespaceArray.h"

namespace OpcUaStackServer
{

	NamespaceArray::NamespaceArray(void)
	: informationModel_()
	{
	}
	
	NamespaceArray::~NamespaceArray(void)
	{
	}

	void 
	NamespaceArray::informationModel(InformationModel::SPtr informationModel)
	{
		informationModel_ = informationModel;
	}

	void 
	NamespaceArray::namespaceArray(std::vector<std::string>& namespaceArray)
	{
		OpcUaVariant variant;
		informationModel_->getValue(OpcUaId_Server_NamespaceArray, AttributeId_Value, variant);
		for (int32_t idx=0; idx<variant.arrayLength(); idx++) {
			OpcUaString::SPtr stringValue = variant.variantSPtr<OpcUaString>((uint32_t)idx);
			namespaceArray.push_back(stringValue->value());
		}
	}

	bool 
	NamespaceArray::addNamespaceName(const std::string& namespaceName)
	{
		OpcUaString::SPtr stringValue = OpcUaString::construct();
		*stringValue = namespaceName;

		OpcUaVariant variant;
		informationModel_->getValue(OpcUaId_Server_NamespaceArray, AttributeId_Value, variant);
		variant.pushBack(stringValue);
		informationModel_->setValue(OpcUaId_Server_NamespaceArray, AttributeId_Value, variant);
		return true;
	}

	int32_t 
	NamespaceArray::getNamespaceIndex(const std::string& namespaceName)
	{
		std::vector<std::string>::iterator it;
		std::vector<std::string> namespaceArray;
		this->namespaceArray(namespaceArray);

		uint32_t namespaceIndex = 0;
		for (it = namespaceArray.begin(); it != namespaceArray.end(); it++) {
			if (*it == namespaceName) return namespaceIndex;
			namespaceIndex++;
		}

		return -1;
	}

	std::string 
	NamespaceArray::getNamespaceName(uint32_t namespaceIndex)
	{
		std::vector<std::string> namespaceArray;
		this->namespaceArray(namespaceArray);

		if (namespaceIndex >= namespaceArray.size()) return "";
		return namespaceArray[namespaceIndex];
	}

	bool 
	NamespaceArray::expandedNodeIdToNodeId(OpcUaExpandedNodeId& expandedNodeId, OpcUaNodeId& nodeId)
	{
		// set namespace index
		int32_t namespaceIndex = getNamespaceIndex(expandedNodeId.namespaceUri().value());
		if (namespaceIndex < 0) return false;
		nodeId.namespaceIndex((uint16_t)namespaceIndex);
	
		// set node identifier
		nodeId.nodeIdValue(expandedNodeId.nodeIdValue());

		return true;
	}

	bool 
	NamespaceArray::existNamespaceIndex(uint32_t namespaceIndex)
	{
		std::vector<std::string>::iterator it;
		std::vector<std::string> namespaceArray;
		this->namespaceArray(namespaceArray);

		if (namespaceArray.size() >= namespaceIndex) return false;
		return true;
	}
		
	bool 
	NamespaceArray::existNamespaceName(const std::string& namespaceName)
	{
		return (getNamespaceIndex(namespaceName) != -1);
	}
}