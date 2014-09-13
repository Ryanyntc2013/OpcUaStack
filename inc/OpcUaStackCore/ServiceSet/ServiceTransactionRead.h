#ifndef __OpcUaStackCore_ServiceTransactionRead_h__
#define __OpcUaStackCore_ServiceTransactionRead_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/ServiceSet/ReadRequest.h"
#include "OpcUaStackCore/ServiceSet/ReadResponse.h"
#include "OpcUaStackCore/ServiceSet/ServiceTransaction.h"
#include "OpcUaStackCore/ServiceSet/ServiceTransactionIf.h"

using namespace OpcUaStackCore;

namespace OpcUaStackCore
{

	class DLLEXPORT ServiceTransactionRead : public ObjectPool<ServiceTransactionRead>, public ServiceTransaction
	{
	  public:
		typedef boost::shared_ptr<ServiceTransactionRead> SPtr;

		ServiceTransactionRead(void);
		~ServiceTransactionRead(void);

		ServiceTransaction::SPtr constructTransaction(void);

		ReadRequest::SPtr request(void);
		ReadResponse::SPtr response(void);

		void opcUaBinaryEncodeRequest(std::ostream& os) const;
		void opcUaBinaryEncodeResponse(std::ostream& os) const;
		void opcUaBinaryDecodeRequest(std::istream& is);
		void opcUaBinaryDecodeResponse(std::istream& is);

	  private:
		ReadRequest::SPtr readRequest_;
		ReadResponse::SPtr readResponse_;
	};

}

#endif