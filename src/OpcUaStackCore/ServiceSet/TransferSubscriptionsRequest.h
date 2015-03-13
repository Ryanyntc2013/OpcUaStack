#ifndef __OpcUaStackCore_TransferSubscriptionsRequest_h__
#define __OpcUaStackCore_TransferSubscriptionsRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"

namespace OpcUaStackCore
{

	class DLLEXPORT TransferSubscriptionsRequest : public  ObjectPool<TransferSubscriptionsRequest>
	{
	  public:
		typedef boost::shared_ptr<TransferSubscriptionsRequest> SPtr;

		TransferSubscriptionsRequest(void);
		virtual ~TransferSubscriptionsRequest(void);

		void subscriptionIds(const OpcUaUInt32Array::SPtr subscriptionIds);
		OpcUaUInt32Array::SPtr subscriptionIds(void) const;
		void sendInitialValues(const OpcUaBoolean& sendInitialValues);
		OpcUaBoolean sendInitialValues(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaUInt32Array::SPtr subscriptionIdArraySPtr_;
		OpcUaBoolean sendInitialValues_;
	};

}

#endif