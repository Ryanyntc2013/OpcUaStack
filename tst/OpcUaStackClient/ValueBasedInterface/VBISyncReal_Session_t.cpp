#include "unittest.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClientHandlerTest.h"

using namespace OpcUaStackClient;

#ifdef REAL_SERVER

BOOST_AUTO_TEST_SUITE(VBISyncReal_Session_)

BOOST_AUTO_TEST_CASE(VBISyncReal_Session_)
{
	std::cout << "VBISyncReal_Session_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(VBISyncReal_Session_session_connect_disconnect)
{
#if 0
	OpcUaStatusCode statusCode;
	VBIClient client;

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	BOOST_REQUIRE(client.syncConnect(connectContext) == Success);

	// disconnect session
	BOOST_REQUIRE(client.syncDisconnect() == Success);
#endif
}

BOOST_AUTO_TEST_CASE(VBISyncReal_Session_session_connect_disconnect_two_times)
{
#if 0
	OpcUaStatusCode statusCode;
	VBIClient client;

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	BOOST_REQUIRE(client.syncConnect(connectContext) == Success);

	// disconnect session
	BOOST_REQUIRE(client.syncDisconnect() == Success);

	// connect session
	BOOST_REQUIRE(client.syncConnect(connectContext) == Success);

	// disconnect session
	BOOST_REQUIRE(client.syncDisconnect() == Success);
#endif
}


BOOST_AUTO_TEST_SUITE_END()

#endif
