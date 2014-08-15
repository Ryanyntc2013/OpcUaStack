#include "unittest.h"
#include "OpcUaStackCore/ServiceSet/WriteValue.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDataValue.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"
#include "OpcUaStackCore/Base/Utility.h"
#include <boost/iostreams/stream.hpp>

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(WriteValue_)

BOOST_AUTO_TEST_CASE(WriteValue_)
{
	std::cout << "WriteValue_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(WriteValue_encode_decode)
{
	std::stringstream ss;
	
	OpcUaDataValue dataValue;
	OpcUaVariant::SPtr variantSPtr;
	WriteValue value1, value2;

	// Variant
	variantSPtr = OpcUaVariant::construct();
	variantSPtr->variant((OpcUaInt16)123);

	// Data Value
	dataValue.variant(variantSPtr);

	// WriteValue
	value1.nodeId((OpcUaInt16) 2, (OpcUaInt32) 9);
	value1.attributeId((OpcUaInt32) 13);
	value1.indexRange("TestString");
	value1.dataValue(dataValue);
	
	// Test
	value1.opcUaBinaryEncode(ss);
	value2.opcUaBinaryDecode(ss);
	
	BOOST_REQUIRE(value2.nodeId()->namespaceIndex() == 2);
	BOOST_REQUIRE(value2.nodeId()->nodeId<OpcUaUInt32>() == 9);
	BOOST_REQUIRE(value2.attributeId() == 13);
	BOOST_REQUIRE(value2.indexRange() == "TestString");
	
	variantSPtr = OpcUaVariant::construct();
	variantSPtr = value2.dataValue().variant();

	BOOST_REQUIRE(variantSPtr->variantType() == OpcUaBuildInType_OpcUaInt16);
	BOOST_REQUIRE(variantSPtr->variant<OpcUaInt16>() == 123);
}

BOOST_AUTO_TEST_SUITE_END()