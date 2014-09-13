#include "OpcUaStackCore/ServiceSet/ServiceTransactionRead.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"

namespace OpcUaStackCore
{

	ServiceTransactionRead::ServiceTransactionRead(void)
	: ServiceTransaction(OpcUaId_ReadRequest_Encoding_DefaultBinary, OpcUaId_ReadResponse_Encoding_DefaultBinary)
	, readRequest_(ReadRequest::construct())
	, readResponse_(ReadResponse::construct())
	{
	}

	ServiceTransactionRead::~ServiceTransactionRead(void)
	{
	}

	ServiceTransaction::SPtr 
	ServiceTransactionRead::constructTransaction(void) 
	{
		return ServiceTransactionRead::construct();
	}

	ReadRequest::SPtr 
	ServiceTransactionRead::request(void)
	{
		return readRequest_;
	}
		
	ReadResponse::SPtr 
	ServiceTransactionRead::response(void)
	{
		return readResponse_;
	}

	void 
	ServiceTransactionRead::opcUaBinaryEncodeRequest(std::ostream& os) const
	{
		readRequest_->opcUaBinaryEncode(os);
	}

	void 
	ServiceTransactionRead::opcUaBinaryEncodeResponse(std::ostream& os) const
	{
		readResponse_->opcUaBinaryEncode(os);
	}

	void 
	ServiceTransactionRead::opcUaBinaryDecodeRequest(std::istream& is)
	{
		readRequest_->opcUaBinaryDecode(is);
	}

	void 
	ServiceTransactionRead::opcUaBinaryDecodeResponse(std::istream& is)
	{
		readResponse_->opcUaBinaryDecode(is);
	}

}