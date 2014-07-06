#include "OpcUaStackCore/ServiceSet/CloseSessionRequest.h"

namespace OpcUaStackCore
{

	CloseSessionRequest::CloseSessionRequest(void)
	: requestHeaderSPtr_()
	, deleteSubscriptions_()
	{
	}

	CloseSessionRequest::~CloseSessionRequest(void)
	{
	}

	void 
	CloseSessionRequest::requestHeader(const RequestHeader::SPtr requestHeaderSPtr)
	{
		requestHeaderSPtr_ = requestHeaderSPtr;
	}

	void 
	CloseSessionRequest::deleteSubscriptions(const OpcUaBoolean& deleteSubscriptions)
	{
		deleteSubscriptions_ = deleteSubscriptions;
	}

	OpcUaBoolean 
	CloseSessionRequest::deleteSubscriptions(void) const
	{
		return deleteSubscriptions_;
	}

	void 
	CloseSessionRequest::opcUaBinaryEncode(std::ostream& os) const
	{
		requestHeaderSPtr_->opcUaBinaryEncode(os);
		OpcUaStackCore::opcUaBinaryEncode(os, deleteSubscriptions_);
	}

	void 
	CloseSessionRequest::opcUaBinaryDecode(std::istream& is)
	{
		requestHeaderSPtr_->opcUaBinaryDecode(is);
		OpcUaStackCore::opcUaBinaryDecode(is, deleteSubscriptions_);
	}

}