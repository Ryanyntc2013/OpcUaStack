#ifndef __OpcUaStackCore_QueryNextResponse_h__
#define __OpcUaStackCore_QueryNextResponse_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/ResponseHeader.h"
#include "OpcUaStackCore/ServiceSet/QueryDataSet.h"

namespace OpcUaStackCore
{

	class DLLEXPORT QueryNextResponse : public  ObjectPool<QueryNextResponse>
	{
	  public:
		QueryNextResponse(void);
		virtual ~QueryNextResponse(void);

		void responseHeader(const ResponseHeader::SPtr responseHeader);
		ResponseHeader::SPtr responseHeader(void) const;
		void queryDataSets(const QueryDataSetArray::SPtr queryDataSets);
		QueryDataSetArray::SPtr queryDataSets(void) const;
		void revisedContinuationPoint(const OpcUaByteString& revisedContinuationPoint);
		OpcUaByteString& revisedContinuationPoint(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		ResponseHeader::SPtr responseHeaderSPtr_;
		QueryDataSetArray::SPtr queryDataSetArraySPtr_;
		OpcUaByteString revisedContinuationPoint_;
	};

}

#endif