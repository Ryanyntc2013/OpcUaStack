#include "OpcUaStackServer/AddressSpaceModel/ReferenceItemMap.h"

namespace OpcUaStackServer
{

	ReferenceItemMap::ReferenceItemMap(void)
	{
	}

	ReferenceItemMap::~ReferenceItemMap(void)
	{
	}

	bool 
	ReferenceItemMap::add(ReferenceType referenceType, ReferenceItem::SPtr referenceItem)
	{
		OpcUaNodeId::SPtr nodeId = ReferenceTypeMap::typeNodeId(referenceType);
		return add(*nodeId, referenceItem);
	}

	bool 
	ReferenceItemMap::add(OpcUaNodeId& referenceTypeNodeId, ReferenceItem::SPtr referenceItem)
	{
		if (referenceItem.get() == nullptr) return false;

		std::pair<ReferenceItemMultiMap::iterator,ReferenceItemMultiMap::iterator> it1;
		ReferenceItemMultiMap::iterator it2;
		it1 = referenceItemMultiMap_.equal_range(referenceTypeNodeId);
		for (it2 = it1.first; it2 != it1.second; it2++) {
			if (*it2->second == *referenceItem) return false;
		}

		referenceItemMultiMap_.insert(std::make_pair(referenceTypeNodeId, referenceItem));
		return true;
	}
		
	ReferenceItemMultiMap& 
	ReferenceItemMap::referenceItemMultiMap(void)
	{
		return referenceItemMultiMap_;
	}

}