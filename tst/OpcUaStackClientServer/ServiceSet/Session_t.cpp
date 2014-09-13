#include "unittest.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/IOService.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/ServiceSet/AnonymousIdentityToken.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameter.h"

#include "OpcUaStackClient/ServiceSet/SessionManager.h"
#include "OpcUaStackClient/ServiceSet/SessionTestHandler.h"
#include "OpcUaStackClient/ServiceSet/AttributeService.h"

#include "OpcUaStackServer/ServiceSet/SessionManager.h"
#include "OpcUaStackServer/ServiceSet/AttributeService.h"

#include <boost/asio/error.hpp>


#define TEST_HOST		"127.0.0.1"
#define TEST_PORT		"4841"


using namespace OpcUaStackCore;
using namespace OpcUaStackClient;
using namespace OpcUaStackServer;

BOOST_AUTO_TEST_SUITE(Session_)

BOOST_AUTO_TEST_CASE(Session_)
{
	std::cout << "Session_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(Session_open)
{
	bool rc;
	SessionTestHandler sessionTestHandler;

	ExtensibleParameter ep;
	ep.registerFactoryElement<AnonymousIdentityToken>(OpcUaId_AnonymousIdentityToken_Encoding_DefaultBinary);

	OpcUaStackClient::SessionManager sessionManagerClient;
	OpcUaStackServer::SessionManager sessionManagerServer;

	OpcUaStackClient::AttributeService attributeServiceClient;
	OpcUaStackServer::AttributeService attributeServiceServer;
	
	TransactionManager::SPtr transactionManager = TransactionManager::construct();
	ServiceTransactionRead::SPtr serviceTransactionReadSPtr = ServiceTransactionRead::construct();
	serviceTransactionReadSPtr->serviceTransactionIfService(&attributeServiceServer);
	transactionManager->registerTransaction(serviceTransactionReadSPtr);
	sessionManagerServer.transactionManager(transactionManager);
	
	sessionManagerClient.start();
	sessionManagerServer.start();

	Config clientConfig;
	Config serverConfig;

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// client configuration : session
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	clientConfig.setValue("TestConfig.EndpointUrl", "opc.tcp://" + std::string(TEST_HOST) + ":" + std::string(TEST_PORT));
	clientConfig.setValue("TestConfig.SessionName", "urn:" + std::string(TEST_HOST) + ":Company:MyAppl");
	clientConfig.setValue("TestConfig.ApplicationDescription.ApplicationUri", "urn:" + std::string(TEST_HOST) + ":Company:MyAppl");
	clientConfig.setValue("TestConfig.ApplicationDescription.ProductUri", "urn:Company:MyAppl");
	clientConfig.setValue("TestConfig.ApplicationDescription.ApplicationName.Locale", "en");
	clientConfig.setValue("TestConfig.ApplicationDescription.ApplicationName.Text", "MyAppl");

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// client configuration : secure channel
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	clientConfig.setValue("TestConfig.EndpointUrl", "opc.tcp://" + std::string(TEST_HOST) + ":" + std::string(TEST_PORT));
	clientConfig.setValue("TestConfig.SecurityPolicyUri", "http://opcfoundation.org/UA/SecurityPolicy#None");

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// server configuration : session
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	Config endpoint;
	Config userTokenPolicy;

	endpoint.clear();
	endpoint.setValue("EndpointUrl", "opc.tcp://" + std::string(TEST_HOST) + ":" + std::string(TEST_PORT) + "/0.0.0.0");
	endpoint.setValue("ApplicationUri", "urn:localhost:compyny:Unittest");
	endpoint.setValue("ProductUri", "urn:company:Unittest");
	endpoint.setValue("ApplicationName", "company Unittest");
	endpoint.addValue("DiscoveryUrl", "opt.tcp://localhost:4841/0.0.0.0");
	endpoint.setValue("SecurityPolicyUri", "http://opcfoundation.org/UA/SecurityPolicy#None");

	userTokenPolicy.clear();
	userTokenPolicy.setValue("PolicyId", "OpcUaStack");
	userTokenPolicy.setValue("TokenType", "Anonymous");
	endpoint.setChild("UserTokenPolicy", userTokenPolicy);

	endpoint.setValue("TransportProfileUri", "http://opcfoundation.org/UA-Profile/Transport/uatcp-uasc-uabinary");
	endpoint.setValue("SecurityLevel", "0");
	serverConfig.addChild("TestConfig.EndpointDescription", endpoint);


	endpoint.clear();
	endpoint.setValue("EndpointUrl", "opc.tcp://" + std::string(TEST_HOST) + ":" + std::string(TEST_PORT) + "/0.0.0.0");
	endpoint.setValue("ApplicationUri", "urn:localhost:compyny:Unittest");
	endpoint.setValue("ProductUri", "urn:company:Unittest");
	endpoint.setValue("ApplicationName", "company Unittest");
	endpoint.addValue("DiscoveryUrl", "opt.tcp://localhost:4841/0.0.0.0");
	endpoint.setValue("SecurityPolicyUri", "http://opcfoundation.org/UA/SecurityPolicy#None");

	userTokenPolicy.clear();
	userTokenPolicy.setValue("PolicyId", "OpcUaStack");
	userTokenPolicy.setValue("TokenType", "Anonymous");
	endpoint.setChild("UserTokenPolicy", userTokenPolicy);

	endpoint.setValue("TransportProfileUri", "http://opcfoundation.org/UA-Profile/Transport/uatcp-uasc-uabinary");
	endpoint.setValue("SecurityLevel", "1");
	serverConfig.addChild("TestConfig.EndpointDescription", endpoint);


	endpoint.clear();
	endpoint.setValue("EndpointUrl", "opc.tcp://" + std::string(TEST_HOST) + ":" + std::string(TEST_PORT) + "/0.0.0.0");
	endpoint.setValue("ApplicationUri", "urn:localhost:compyny:Unittest");
	endpoint.setValue("ProductUri", "urn:company:Unittest");
	endpoint.setValue("ApplicationName", "company Unittest");
	endpoint.addValue("DiscoveryUrl", "opt.tcp://localhost:4841/0.0.0.0");
	endpoint.setValue("SecurityPolicyUri", "http://opcfoundation.org/UA/SecurityPolicy#None");

	userTokenPolicy.clear();
	userTokenPolicy.setValue("PolicyId", "OpcUaStack");
	userTokenPolicy.setValue("TokenType", "Anonymous");
	endpoint.setChild("UserTokenPolicy", userTokenPolicy);

	endpoint.setValue("TransportProfileUri", "http://opcfoundation.org/UA-Profile/Transport/uatcp-uasc-uabinary");
	endpoint.setValue("SecurityLevel", "3");
	serverConfig.addChild("TestConfig.EndpointDescription", endpoint);

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// server configuration : secure channel
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	serverConfig.setValue("TestConfig.EndpointUrl", "opc.tcp://" + std::string(TEST_HOST) + ":" + std::string(TEST_PORT));

	rc = sessionManagerServer.openServerSocket(
		"TestConfig", serverConfig,
		"TestConfig", serverConfig
	);
	BOOST_REQUIRE(rc == true);

	OpcUaStackClient::Session::SPtr session = sessionManagerClient.getNewSession(
		"TestConfig", clientConfig,
		"TestConfig", clientConfig,
		&sessionTestHandler
	);
	attributeServiceClient.session(session);

	// client createSession
	sessionTestHandler.createSessionCompleteCondition_.condition(1, 0);
	session->createSession();
	BOOST_REQUIRE(sessionTestHandler.createSessionCompleteCondition_.waitForCondition(1000) == true);

	// client activateSession
	sessionTestHandler.activateSessionCompleteCondition_.condition(1, 0);
	session->activateSession();
	BOOST_REQUIRE(sessionTestHandler.activateSessionCompleteCondition_.waitForCondition(1000) == true);

	// client send read request to server
	boost::shared_ptr<ServiceTransactionRead> readTrx = ServiceTransactionRead::construct();
	ReadRequest::SPtr req = readTrx->request();
	req->maxAge(0);
	req->timestampsToReturn(2);

	ReadValueId::SPtr readValueIdSPtr = ReadValueId::construct();
	readValueIdSPtr->nodeId((OpcUaInt16) 2, (OpcUaInt32) 9);
	readValueIdSPtr->attributeId((OpcUaInt32) 13);
	readValueIdSPtr->dataEncoding().namespaceIndex((OpcUaInt16) 0);

	req->readValueIdArray()->set(readValueIdSPtr);

	attributeServiceClient.send(readTrx);

	IOService::secSleep(1000);

	sessionManagerServer.stop();
	sessionManagerClient.stop();
}

BOOST_AUTO_TEST_SUITE_END()