#ifndef __OpcUaStackServer_ServiceManager_h__
#define __OpcUaStackServer_ServiceManager_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackServer/ServiceSet/SessionManager.h"
#include "OpcUaStackServer/ServiceSet/AttributeService.h"
#include "OpcUaStackServer/ServiceSet/MethodService.h"
#include "OpcUaStackServer/ServiceSet/NodeManagementService.h"
#include "OpcUaStackServer/ServiceSet/MonitoredItemService.h"
#include "OpcUaStackServer/ServiceSet/QueryService.h"
#include "OpcUaStackServer/ServiceSet/SubscriptionService.h"
#include "OpcUaStackServer/ServiceSet/ViewService.h"

namespace OpcUaStackServer
{

	class DLLEXPORT ServiceManager
	{
	  public:
		ServiceManager(void);
		~ServiceManager(void);

		bool init(SessionManager& sessionManager);

	  private:
		TransactionManager::SPtr transactionManager_;
		AttributeService::SPtr attributeService_;
		MethodService::SPtr methodService_;
		MonitoredItemService::SPtr monitoredItemService_;
		NodeManagementService::SPtr nodeManagementService_;
		QueryService::SPtr queryService_;
		SubscriptionService::SPtr subscriptionService_;
		ViewService::SPtr viewService_;
	};

}

#endif