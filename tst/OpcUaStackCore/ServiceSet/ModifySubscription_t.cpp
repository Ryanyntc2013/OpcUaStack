#include "unittest.h"
#include "boost/asio.hpp"
#include "OpcUaStackCore/ServiceSet/ModifySubscriptionRequest.h"
#include "OpcUaStackCore/ServiceSet/ModifySubscriptionResponse.h"
#include "OpcUaStackCore/SecureChannel/MessageHeader.h"
#include "OpcUaStackCore/SecureChannel/SequenceHeader.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"

#include <streambuf>
#include <iostream>

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(ModifySubscription_)

BOOST_AUTO_TEST_CASE(ModifySubscription_Title)
{
	std::cout << "ModifySubscription_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(ModifySubscription_Request)
{
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaGuid::SPtr opcUaGuidSPtr;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	ModifySubscriptionRequest::SPtr modifySubscriptionRequestSPtr;
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
	sequenceHeaderSPtr->sequenceNumber(54);
	sequenceHeaderSPtr->requestId(4);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_ModifySubscriptionRequest_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build CreateSubscriptionRequest
	modifySubscriptionRequestSPtr = ModifySubscriptionRequest::construct();

	// build RequestHeader
	opcUaGuidSPtr = OpcUaGuid::construct();
	*opcUaGuidSPtr = "0D4455B2-8D2F-B74F-864F-0AF5945DD833";
	
	modifySubscriptionRequestSPtr->requestHeader()->sessionAuthenticationToken().namespaceIndex(1);
	modifySubscriptionRequestSPtr->requestHeader()->sessionAuthenticationToken().nodeId(opcUaGuidSPtr);
	modifySubscriptionRequestSPtr->requestHeader()->time(ptime);
	modifySubscriptionRequestSPtr->requestHeader()->requestHandle(0);
	modifySubscriptionRequestSPtr->requestHeader()->returnDisagnostics(0);
	modifySubscriptionRequestSPtr->requestHeader()->timeoutHint(300000);
	
	// build Parameter
	modifySubscriptionRequestSPtr->subscriptionId(153451225);
	modifySubscriptionRequestSPtr->requestedPublishingInterval(500);
	modifySubscriptionRequestSPtr->requestedLifetimeCount(2400);
	modifySubscriptionRequestSPtr->requestedMaxKeepAliveCount(10);
	modifySubscriptionRequestSPtr->maxNotificationsPerPublish(4294967295);
	modifySubscriptionRequestSPtr->priority(0);

	// encode CreateSubscriptionRequest
	modifySubscriptionRequestSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);
	
	std::stringstream ss;
	ss << "4d 53 47 46 63 00 00 00  d9 7a 25 09 01 00 00 00"
	   << "36 00 00 00 04 00 00 00  01 00 19 03 04 01 00 0d"
	   << "44 55 b2 8d 2f b7 4f 86  4f 0a f5 94 5d d8 33 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 ff"	
	   << "ff ff ff e0 93 04 00 00  00 00 d9 7a 25 09 00 00"
	   << "00 00 00 40 7f 40 60 09  00 00 0a 00 00 00 ff ff"
	   << "ff ff 00";

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
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 54);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 4);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_ModifySubscriptionRequest_Encoding_DefaultBinary);

	// decode ReadRequest
	modifySubscriptionRequestSPtr = ModifySubscriptionRequest::construct();
	modifySubscriptionRequestSPtr->opcUaBinaryDecode(ios);

	std::string str;
	str = *modifySubscriptionRequestSPtr->requestHeader()->sessionAuthenticationToken().nodeId<OpcUaGuid::SPtr>();
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestHeader()->sessionAuthenticationToken().namespaceIndex() == 1);
	BOOST_REQUIRE(str == "0D4455B2-8D2F-B74F-864F-0AF5945DD833");
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestHeader()->time().dateTime() == ptime);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestHeader()->requestHandle() == 0);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestHeader()->returnDisagnostics() == 0);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestHeader()->timeoutHint() == 300000);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->subscriptionId() == 153451225);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestedPublishingInterval() == 500);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestedLifetimeCount() == 2400);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->requestedMaxKeepAliveCount() == 10);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->maxNotificationsPerPublish() == 4294967295);
	BOOST_REQUIRE(modifySubscriptionRequestSPtr->priority() == 0);
}


BOOST_AUTO_TEST_CASE(CreateSubscription_Response)
{
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaStatusCode statusCode;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	ModifySubscriptionResponse::SPtr modifySubscriptionResponseSPtr;
	OpcUaDateTime sourceTimestamp, serverTimestamp;
	OpcUaDataValue::SPtr dataValueSPtr;
	OpcUaVariant::SPtr variantSPtr;
	boost::posix_time::ptime ptime;
	
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
	sequenceHeaderSPtr->sequenceNumber(54);
	sequenceHeaderSPtr->requestId(4);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_ModifySubscriptionResponse_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build ModifySubscriptionResponse
	modifySubscriptionResponseSPtr = ModifySubscriptionResponse::construct();

	// build ResponseHeader
	statusCode = Success;
	modifySubscriptionResponseSPtr->responseHeader()->time(ptime);
	modifySubscriptionResponseSPtr->responseHeader()->requestHandle(0);
	modifySubscriptionResponseSPtr->responseHeader()->serviceResult(statusCode);
	
	// build Parameter
	modifySubscriptionResponseSPtr->revisedPublishingInterval(500);
	modifySubscriptionResponseSPtr->revisedLifetimeCount(2400);
	modifySubscriptionResponseSPtr->revisedMaxKeepAliveCount(10);

	// encode ModifySubscription
	modifySubscriptionResponseSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = MessageHeader::construct();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);

	std::stringstream ss;
	ss << "4d 53 47 46 44 00 00 00  d9 7a 25 09 01 00 00 00"
	   << "36 00 00 00 04 00 00 00  01 00 1c 03 00 00 00 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00"
	   << "00 00 00 00 00 00 00 00  00 40 7f 40 60 09 00 00"
	   << "0a 00 00 00";

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
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 54);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 4);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_ModifySubscriptionResponse_Encoding_DefaultBinary);

	// decode ReadResponse
	modifySubscriptionResponseSPtr = ModifySubscriptionResponse::construct();
	modifySubscriptionResponseSPtr->opcUaBinaryDecode(ios);

	BOOST_REQUIRE(modifySubscriptionResponseSPtr->responseHeader()->time().dateTime() == ptime);
	BOOST_REQUIRE(modifySubscriptionResponseSPtr->responseHeader()->requestHandle() == 0);
	BOOST_REQUIRE(modifySubscriptionResponseSPtr->responseHeader()->serviceResult() == Success);
	BOOST_REQUIRE(modifySubscriptionResponseSPtr->revisedPublishingInterval() == 500);
	BOOST_REQUIRE(modifySubscriptionResponseSPtr->revisedLifetimeCount() == 2400);
	BOOST_REQUIRE(modifySubscriptionResponseSPtr->revisedMaxKeepAliveCount() == 10);
}

BOOST_AUTO_TEST_SUITE_END()