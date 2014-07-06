#include "unittest.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackCore/Base/Utility.h"
#include <boost/iostreams/stream.hpp>

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(OpcUaNodeId_)

BOOST_AUTO_TEST_CASE(OpcUaNodeId_)
{
	std::cout << "OpcUaNodeId_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_two_byte_representation)
{
	std::stringstream ss;
	OpcUaNodeId value1, value2;

	value1.nodeId((OpcUaInt32)11);
	
	opcUaBinaryEncode(ss, value1);
	BOOST_REQUIRE(count(ss) == 2);
	opcUaBinaryDecode(ss, value2);

	BOOST_REQUIRE(value2.namespaceIndex() == 0);
	BOOST_REQUIRE(value2.nodeId<OpcUaUInt32>() == 11);
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_four_byte_representation)
{
	std::stringstream ss;
	OpcUaNodeId value1, value2;

	value1.namespaceIndex(123);
	value1.nodeId((OpcUaInt32)11);
	
	opcUaBinaryEncode(ss, value1);
	BOOST_REQUIRE(count(ss) == 4);
	opcUaBinaryDecode(ss, value2);

	BOOST_REQUIRE(value2.namespaceIndex() == 123);
	BOOST_REQUIRE(value2.nodeId<OpcUaUInt32>() == 11);
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_other1_byte_representation)
{
	std::stringstream ss;
	OpcUaNodeId value1, value2;

	value1.namespaceIndex(130);
	value1.nodeId((OpcUaUInt32)11);
	
	opcUaBinaryEncode(ss, value1);
	BOOST_REQUIRE(count(ss) == 4);
	opcUaBinaryDecode(ss, value2);

	BOOST_REQUIRE(value2.namespaceIndex() == 130);
	BOOST_REQUIRE(value2.nodeId<OpcUaUInt32>() == 11);
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_other2_byte_representation)
{
	std::stringstream ss;
	OpcUaNodeId value1, value2;

	value1.namespaceIndex(123);
	value1.nodeId((OpcUaUInt32)0x10000);
	
	opcUaBinaryEncode(ss, value1);
	BOOST_REQUIRE(count(ss) > 4);
	opcUaBinaryDecode(ss, value2);

	BOOST_REQUIRE(value2.namespaceIndex() == 123);
	BOOST_REQUIRE(value2.nodeId<OpcUaUInt32>() == 0x10000);
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_type_OpcUaUInt32)
{
	std::stringstream ss;
	OpcUaNodeId value1, value2;

	value1.namespaceIndex(123);
	value1.nodeId((OpcUaInt32)0x10000);
	
	opcUaBinaryEncode(ss, value1);
	opcUaBinaryDecode(ss, value2);
	
	BOOST_REQUIRE(value2.nodeIdType() == OpcUaBuildInType_OpcUaUInt32);
	BOOST_REQUIRE(value2.namespaceIndex() == 123);
	BOOST_REQUIRE(value2.nodeId<OpcUaUInt32>() == 0x10000);
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_type_OpcUaString_SPtr)
{
	std::string str;
	std::stringstream ss;
	OpcUaNodeId value1, value2;
	
	OpcUaString::SPtr opcUaStringSPtr = OpcUaString::construct();
	opcUaStringSPtr->value("Dies ist ein String");

	value1.namespaceIndex(123);
	value1.nodeId(opcUaStringSPtr);
	
	opcUaBinaryEncode(ss, value1);
	opcUaBinaryDecode(ss, value2);

	BOOST_REQUIRE(value2.nodeIdType() == OpcUaBuildInType_OpcUaString);
	BOOST_REQUIRE(value2.namespaceIndex() == 123);
	BOOST_REQUIRE(value2.nodeId<OpcUaString::SPtr>()->value() == "Dies ist ein String");
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_type_OpcUaGuid_SPtr)
{
	std::string str;
	std::stringstream ss;
	OpcUaNodeId value1, value2;
	
	OpcUaGuid::SPtr opcUaGuidSPtr = OpcUaGuid::construct();
	*opcUaGuidSPtr = "12345678-9ABC-DEF0-1234-56789ABCDEF0";

	value1.namespaceIndex(123);
	value1.nodeId(opcUaGuidSPtr);
	
	opcUaBinaryEncode(ss, value1);
	opcUaBinaryDecode(ss, value2);

	str = *value2.nodeId<OpcUaGuid::SPtr>();
	BOOST_REQUIRE(value2.nodeIdType() == OpcUaBuildInType_OpcUaGuid);
	BOOST_REQUIRE(value2.namespaceIndex() == 123);
	BOOST_REQUIRE(str == "12345678-9ABC-DEF0-1234-56789ABCDEF0");
}

BOOST_AUTO_TEST_CASE(OpcUaNodeId_type_OpcUaByteString_SPtr)
{
	std::stringstream ss;
	OpcUaNodeId value1, value2;
	
	OpcUaByteString::SPtr opcUaByteStringSPtr = OpcUaByteString::construct();
	opcUaByteStringSPtr->value("0123456789", 10);

	value1.namespaceIndex(123);
	value1.nodeId(opcUaByteStringSPtr);
	
	opcUaBinaryEncode(ss, value1);
	opcUaBinaryDecode(ss, value2);

	char *buf;
	OpcUaInt32 bufLen;
	value2.nodeId<OpcUaByteString::SPtr>()->value(&buf, &bufLen);
	BOOST_REQUIRE(value2.nodeIdType() == OpcUaBuildInType_OpcUaByteString);
	BOOST_REQUIRE(value2.namespaceIndex() == 123);
	BOOST_REQUIRE(bufLen == 10);
	BOOST_REQUIRE(memcmp(buf, "0123456789", 10) == 0);
}

BOOST_AUTO_TEST_SUITE_END()