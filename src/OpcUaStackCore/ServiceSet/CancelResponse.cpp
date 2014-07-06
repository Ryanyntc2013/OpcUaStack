#include "OpcUaStackCore/ServiceSet/CancelResponse.h"

namespace OpcUaStackCore
{

	CancelResponse::CancelResponse(void)
	: responseHeader_()
	{
	}

	CancelResponse::~CancelResponse(void)
	{
	}

	void 
	CancelResponse::responseHeader(const ResponseHeader::SPtr requestHeader)
	{
		responseHeader_ = requestHeader;
	}

	ResponseHeader::SPtr 
	CancelResponse::responseHeader(void) const
	{
		return responseHeader_;
	}

	void
	CancelResponse::cancelCount(const OpcUaInt32& cancelCount)
	{
		cancelCount_ = cancelCount;
	}

	OpcUaInt32 
	CancelResponse::cancelCount(void) const
	{
		return cancelCount_;
	}

	void 
	CancelResponse::opcUaBinaryEncode(std::ostream& os) const
	{
		responseHeader_->opcUaBinaryEncode(os);
		OpcUaStackCore::opcUaBinaryEncode(os, cancelCount_);
	}

	void 
	CancelResponse::opcUaBinaryDecode(std::istream& is)
	{
		responseHeader_->opcUaBinaryDecode(is);
		OpcUaStackCore::opcUaBinaryDecode(is, cancelCount_);
	}

}