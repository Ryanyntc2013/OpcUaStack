#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaServer/Server/Server.h"
#include "OpcUaStackCore/Utility/Environment.h"
#include <iostream>

using namespace OpcUaStackCore;

namespace OpcUaServer
{

	Server::Server(void)
	: configurationFile_("")
	, config_(nullptr)
	, server_()
	{
	}

	Server::~Server(void)
	{
	}

	bool
	Server::initial(const std::string& configurationFile)
	{
		configurationFile_ = Environment::getAbsolutePath(configurationFile);

		// read configuration file
		if (!readConfigurationFile()) {
			Log(Error, "shutdown server, because read configuration error");
			return false;
		}

		// intial logging
		if (!initLogging()) {
			Log(Error, "shutdown server, because init log error");
			return false;
		}

		// initial opc ua server
		if (!server_.init()) {
			Log(Error, "shutdown server, because init server error");
			return false;
		}

		return true;
	}

	bool
	Server::start(void)
	{
		server_.start();
		return true;
	}

	void
	Server::stop(void)
	{

	}

	void 
	Server::cleanup(void)
	{
	}

	bool 
	Server::readConfigurationFile(void)
	{
		config_ = Config::instance();
		ConfigXml configXml;
		if (!configXml.parse(configurationFile_, true)) {
			std::string errorMessage = configXml.errorMessage();
			Log(Error, "read configuration error")
				.parameter("ErrorMessage", errorMessage);
			return false;
		}

		server_.config(*config_);
		return true;
	}

	bool
	Server::initLogging(void)
	{
		return true;
	}

}