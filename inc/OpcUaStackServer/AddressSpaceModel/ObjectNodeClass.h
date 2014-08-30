#ifndef __OpcUaStackServer_ObjectNodeClass_h__
#define __OpcUaStackServer_ObjectNodeClass_h__

#include "OpcUaStackServer/AddressSpaceModel/BaseNodeClass.h"

namespace OpcUaStackServer
{

	class ObjectNodeClass : public BaseNodeClass
	{
	  public:
		ObjectNodeClass(void);
		~ObjectNodeClass(void);

		EventNotifierAttribute& eventNotifier(void);

	  private:
		// attributes mandatory
		EventNotifierAttribute eventNotifier_;

		// references
		OpcUaNodeIdList hasComponent_;
		OpcUaNodeIdList hasProperty_;
		OpcUaNodeIdList hasModellingRule_;
		OpcUaNodeIdList hasTypeDefinition_;
		OpcUaNodeIdList hasModelParent_;
		OpcUaNodeIdList hasEventSource_;
		OpcUaNodeIdList hasNotifier_;
		OpcUaNodeIdList organizes_;
		OpcUaNodeIdList hasDescription_;

		// standard properties
		OpcUaString::SPtr nodeVersion_;  // optional
		// FIXME: Image icon_;	// optional
		// FIXME: NamingRuleType nameingRule_;	// optional 
	};

}

#endif