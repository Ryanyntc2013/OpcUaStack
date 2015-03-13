#ifndef __OpcUaStackCore_ModifyMonitoredItemsRequest_h__
#define __OpcUaStackCore_ModifyMonitoredItemsRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"
#include "OpcUaStackCore/ServiceSet/MonitoredItemModifyRequest.h"
#include "OpcUaStackCore/ServiceSet/TimestampsToReturn.h"

namespace OpcUaStackCore
{

	class DLLEXPORT ModifyMonitoredItemsRequest : public  ObjectPool<ModifyMonitoredItemsRequest>
	{
	  public:
		typedef boost::shared_ptr<ModifyMonitoredItemsRequest> SPtr;

		ModifyMonitoredItemsRequest(void);
		virtual ~ModifyMonitoredItemsRequest(void);

		void subscriptionId(const OpcUaUInt32& subscriptionId);
		OpcUaUInt32 subscriptionId(void) const;
		void timestampsToReturn(const TimestampsToReturn timestampsToReturn);
		TimestampsToReturn timestampsToReturn(void);
		void itemsToModify(const MonitoredItemModifyRequestArray::SPtr itemsToModify);
		MonitoredItemModifyRequestArray::SPtr itemsToModify(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaUInt32 subscriptionId_;
		TimestampsToReturn timestampsToReturn_;
		MonitoredItemModifyRequestArray::SPtr itemsToModifyArraySPtr_;
	};

}

#endif