#include "unittest.h"
#include "boost/asio.hpp"
#include "OpcUaStackCore/ServiceSet/WriteRequest.h"
#include "OpcUaStackCore/ServiceSet/WriteResponse.h"
#include "OpcUaStackCore/SecureChannel/MessageHeader.h"
#include "OpcUaStackCore/SecureChannel/SequenceHeader.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"

#include <streambuf>
#include <iostream>

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(Write_)

BOOST_AUTO_TEST_CASE(Write_)
{
	std::cout << "Write_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(Write_Request)
{
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaGuid::SPtr opcUaGuidSPtr;
	WriteValue::SPtr writeValueSPtr;
	WriteRequest::SPtr writeRequestSPtr;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	boost::posix_time::ptime ptime = boost::posix_time::from_iso_string("16010101T120000.000000000");
	
	// stream
	boost::asio::streambuf sb1;
	std::iostream ios1(&sb1);
	boost::asio::streambuf sb2;
	std::iostream ios2(&sb2);
	boost::asio::streambuf sb;
	std::iostream ios(&sb);

	// encode security header
	OpcUaInt32 secureChannelId;
	OpcUaInt32 secureTokenId;

	secureChannelId = 153451225;
	secureTokenId = 1;

	OpcUaNumber::opcUaBinaryEncode(ios1, secureChannelId);
	OpcUaNumber::opcUaBinaryEncode(ios1, secureTokenId);

	// encode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->sequenceNumber(55);
	sequenceHeaderSPtr->requestId(5);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_WriteRequest_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build ReadRequest
	writeRequestSPtr = WriteRequest::construct();

	// build RequestHeader
	opcUaGuidSPtr = OpcUaGuid::construct();
	*opcUaGuidSPtr = "0D4455B2-8D2F-B74F-864F-0AF5945DD833";

	writeRequestSPtr->requestHeader()->sessionAuthenticationToken().namespaceIndex(1);
	writeRequestSPtr->requestHeader()->sessionAuthenticationToken().nodeId(opcUaGuidSPtr);
	writeRequestSPtr->requestHeader()->time(ptime);
	writeRequestSPtr->requestHeader()->requestHandle(0);
	writeRequestSPtr->requestHeader()->returnDisagnostics(0);
	writeRequestSPtr->requestHeader()->timeoutHint(300000);

	// build NodesToWrite
	// Variant
	OpcUaVariant::SPtr variantSPtr;
	variantSPtr = OpcUaVariant::construct();
	variantSPtr->variant((OpcUaFloat)321);

	// Data Value
	OpcUaDataValue dataValue;
	dataValue.variant(variantSPtr);

	// WriteValue
	writeValueSPtr = WriteValue::construct();
	writeValueSPtr->nodeId((OpcUaInt16) 2, (OpcUaInt32) 9);
	writeValueSPtr->attributeId((OpcUaInt32) 13);
	writeValueSPtr->dataValue(dataValue);

	// WriteValueArray
	writeRequestSPtr->writeValueArray()->set(writeValueSPtr);

	// encode WriteRequest
	writeRequestSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);

	std::stringstream ss;
	ss << "4d 53 47 46 60 00 00 00  d9 7a 25 09 01 00 00 00"
	   << "37 00 00 00 05 00 00 00  01 00 a1 02 04 01 00 0d"
	   << "44 55 b2 8d 2f b7 4f 86  4f 0a f5 94 5d d8 33 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 ff"
	   << "ff ff ff e0 93 04 00 00  00 00 01 00 00 00 01 02"
	   << "09 00 0d 00 00 00 ff ff  ff ff 01 0a 00 80 a0 43";

	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos) == true);

	// decode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(messageHeaderSPtr->messageType() == MessageType_Message);

	// decode security header
	OpcUaNumber::opcUaBinaryDecode(ios, secureChannelId);
	BOOST_REQUIRE(secureChannelId == 153451225);
	OpcUaNumber::opcUaBinaryDecode(ios, secureTokenId);
	BOOST_REQUIRE(secureTokenId == 1);

	// decode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 55);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 5);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_WriteRequest_Encoding_DefaultBinary);

	// decode WriteRequest
	writeRequestSPtr = WriteRequest::construct();
	writeRequestSPtr->opcUaBinaryDecode(ios);

	std::string str;
	str = *writeRequestSPtr->requestHeader()->sessionAuthenticationToken().nodeId<OpcUaGuid::SPtr>();
	BOOST_REQUIRE(writeRequestSPtr->requestHeader()->sessionAuthenticationToken().namespaceIndex() == 1);
	BOOST_REQUIRE(str == "0D4455B2-8D2F-B74F-864F-0AF5945DD833");
	BOOST_REQUIRE(writeRequestSPtr->requestHeader()->time().dateTime() == ptime);
	BOOST_REQUIRE(writeRequestSPtr->requestHeader()->requestHandle() == 0);
	BOOST_REQUIRE(writeRequestSPtr->requestHeader()->returnDisagnostics() == 0);
	BOOST_REQUIRE(writeRequestSPtr->requestHeader()->timeoutHint() == 300000);

	BOOST_REQUIRE(writeRequestSPtr->writeValueArray()->size() == 1);

	writeValueSPtr = WriteValue::construct();
	writeRequestSPtr->writeValueArray()->get(writeValueSPtr);
	BOOST_REQUIRE(writeValueSPtr->nodeId()->namespaceIndex() == 2);
	BOOST_REQUIRE(writeValueSPtr->nodeId()->nodeId<OpcUaUInt32>() == 9);
	BOOST_REQUIRE(writeValueSPtr->attributeId() == 13);
	BOOST_REQUIRE(writeValueSPtr->dataValue().variant()->variantType() == OpcUaBuildInType_OpcUaFloat);
	BOOST_REQUIRE(writeValueSPtr->dataValue().variant()->variant<OpcUaFloat>() == 321);
}


BOOST_AUTO_TEST_CASE(Write_Response)
{
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaStatusCode statusCode;
	WriteResponse::SPtr writeResponseSPtr;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	OpcUaDateTime sourceTimestamp, serverTimestamp;
	OpcUaDataValue::SPtr dataValueSPtr;
	OpcUaVariant::SPtr variantSPtr;
	boost::posix_time::ptime ptime, ptime1, ptime2;
	
	// test-time
	ptime = boost::posix_time::from_iso_string("16010101T120000.000000000");

	// stream
	boost::asio::streambuf sb1;
	std::iostream ios1(&sb1);
	boost::asio::streambuf sb2;
	std::iostream ios2(&sb2);
	boost::asio::streambuf sb;
	std::iostream ios(&sb);

	// encode security header
	OpcUaInt32 secureChannelId;
	OpcUaInt32 secureTokenId;

	secureChannelId = 153451225;
	secureTokenId = 1;

	OpcUaNumber::opcUaBinaryEncode(ios1, secureChannelId);
	OpcUaNumber::opcUaBinaryEncode(ios1, secureTokenId);

	// encode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->sequenceNumber(55);
	sequenceHeaderSPtr->requestId(5);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_WriteResponse_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build WriteResponse
	writeResponseSPtr = WriteResponse::construct();

	// build ResponseHeader
	statusCode = Success;
	writeResponseSPtr->responseHeader()->time(ptime);
	writeResponseSPtr->responseHeader()->requestHandle(0);
	writeResponseSPtr->responseHeader()->serviceResult(statusCode);
	
	// build Results
	statusCode = Success;
	writeResponseSPtr->results()->set(statusCode);

	// encode WriteResponse
	writeResponseSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);

	std::stringstream ss;
	ss << "4d 53 47 46 40 00 00 00  d9 7a 25 09 01 00 00 00"
       << "37 00 00 00 05 00 00 00  01 00 a4 02 00 00 00 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00"
	   << "00 00 00 00 01 00 00 00  00 00 00 00 00 00 00 00";

	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos) == true);

	// decode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(messageHeaderSPtr->messageType() == MessageType_Message);

	// decode security header
	OpcUaNumber::opcUaBinaryDecode(ios, secureChannelId);
	BOOST_REQUIRE(secureChannelId == 153451225);
	OpcUaNumber::opcUaBinaryDecode(ios, secureTokenId);
	BOOST_REQUIRE(secureTokenId == 1);

	// decode sequence header
	sequenceHeaderSPtr = SequenceHeader::construct();
	sequenceHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 55);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 5);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_WriteResponse_Encoding_DefaultBinary);

	// decode WriteResponse
	writeResponseSPtr = WriteResponse::construct();
	writeResponseSPtr->opcUaBinaryDecode(ios);

	BOOST_REQUIRE(writeResponseSPtr->responseHeader()->time().dateTime() == ptime);
	BOOST_REQUIRE(writeResponseSPtr->responseHeader()->requestHandle() == 0);
	BOOST_REQUIRE(writeResponseSPtr->responseHeader()->serviceResult() == Success);

	BOOST_REQUIRE(writeResponseSPtr->results()->size() == 1);

	writeResponseSPtr->results()->get(statusCode);
	BOOST_REQUIRE(statusCode == Success);
}

BOOST_AUTO_TEST_SUITE_END()