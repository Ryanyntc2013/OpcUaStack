#ifndef __OpcUaStackCore_RegisterNodesRequest_h__
#define __OpcUaStackCore_RegisterNodesRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"

namespace OpcUaStackCore
{

	class DLLEXPORT RegisterNodesRequest : public  ObjectPool<RegisterNodesRequest>
	{
	  public:
		RegisterNodesRequest(void);
		virtual ~RegisterNodesRequest(void);

		void requestHeader(const RequestHeader::SPtr requestHeader);
		RequestHeader::SPtr requestHeader(void) const;
		void nodesToRegister(const OpcUaNodeIdArray::SPtr nodesToRegister);
		OpcUaNodeIdArray::SPtr nodesToRegister(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		RequestHeader::SPtr requestHeaderSPtr_;
		OpcUaNodeIdArray::SPtr nodesToRegisterArraySPtr_;
	};

}

#endif