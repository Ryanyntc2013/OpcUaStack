#include "OpcUaStackCore/ServiceSet/GetEndpointsRequest.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa GetEndpointsRequest
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	GetEndpointsRequest::GetEndpointsRequest(void)
	: ObjectPool<GetEndpointsRequest>()
	, requestHeaderSPtr_(RequestHeader::construct())
	, endpointUrl_()
	, localeIdArraySPtr_(OpcUaStringArray::construct())
	, profileUriArraySPtr_(OpcUaStringArray::construct())
	{
	}

	GetEndpointsRequest::~GetEndpointsRequest(void)
	{
	}

	void 
	GetEndpointsRequest::requestHeader(const RequestHeader::SPtr requestHeaderSPtr)
	{
		requestHeaderSPtr_ = requestHeaderSPtr;
	}

	RequestHeader::SPtr 
	GetEndpointsRequest::requestHeader(void) const
	{
		return requestHeaderSPtr_;
	}

	void 
	GetEndpointsRequest::endpointUrl(const OpcUaString& endpointUrl)
	{
		endpointUrl_ = endpointUrl;
	}

	void 
	GetEndpointsRequest::endpointUrl(const std::string& endpointUrl)
	{
		endpointUrl_.value(endpointUrl);
	}
	
	OpcUaString& 
	GetEndpointsRequest::endpointUrl(void)
	{
		return endpointUrl_;
	}
	
	void 
	GetEndpointsRequest::localeIds(const OpcUaStringArray::SPtr localeIds)
	{
		localeIdArraySPtr_ = localeIds;
	}
	
	OpcUaStringArray::SPtr 
	GetEndpointsRequest::localeIds(void) const
	{
		return localeIdArraySPtr_;
	}
	
	void 
	GetEndpointsRequest::profileUris(const OpcUaStringArray::SPtr profileUris)
	{
		profileUriArraySPtr_ = profileUris;
	}
	
	OpcUaStringArray::SPtr 
	GetEndpointsRequest::profileUris(void) const
	{
		return profileUriArraySPtr_;
	}

	void 
	GetEndpointsRequest::opcUaBinaryEncode(std::ostream& os) const
	{
		requestHeaderSPtr_->opcUaBinaryEncode(os);
		endpointUrl_.opcUaBinaryEncode(os);
		localeIdArraySPtr_->opcUaBinaryEncode(os);
		profileUriArraySPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	GetEndpointsRequest::opcUaBinaryDecode(std::istream& is)
	{
		requestHeaderSPtr_->opcUaBinaryDecode(is);
		endpointUrl_.opcUaBinaryDecode(is);
		localeIdArraySPtr_->opcUaBinaryDecode(is);
		profileUriArraySPtr_->opcUaBinaryDecode(is);
	}

}