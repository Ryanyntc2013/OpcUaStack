/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#include "OpcUaStackCore/SecureChannel/SecureChannelClientConfig.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// SecureChannelClientData
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	SecureChannelClientConfig::SecureChannelClientConfig(void)
	: SecureChannelConfig()
	, endpointUrl_("")
	, securityMode_(SM_None)
	, securityPolicy_(SP_None)
	, connectTimeout_(0)
	{
	}

	SecureChannelClientConfig::~SecureChannelClientConfig(void)
	{
	}

	void
	SecureChannelClientConfig::endpointUrl(const std::string& endpointUrl)
	{
		endpointUrl_ = endpointUrl;
	}

	std::string&
	SecureChannelClientConfig::endpointUrl(void)
	{
		return endpointUrl_;
	}

	void
	SecureChannelClientConfig::securityMode(SecurityMode securityMode)
	{
		securityMode_ = securityMode;
	}

	SecurityMode
	SecureChannelClientConfig::securityMode(void)
	{
		return securityMode_;
	}

	void
	SecureChannelClientConfig::securityPolicy(SecurityPolicy securityPolicy)
	{
		securityPolicy_ = securityPolicy;
	}

	SecurityPolicy
	SecureChannelClientConfig::securityPolicy(void)
	{
		return securityPolicy_;
	}

	void
	SecureChannelClientConfig::connectTimeout(uint32_t connectTimeout)
	{
		connectTimeout_ = connectTimeout;
	}

	uint32_t
	SecureChannelClientConfig::connectTimeout(void)
	{
		return connectTimeout_;
	}

}
