/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf modbusTCPMaster://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)

 */

#ifndef __OpUaStackCore_SecureChannelServerConfig_h__
#define __OpUaStackCore_SecureChannelServerConfig_h__

#include "OpcUaStackCore/SecureChannel/SecureChannelConfig.h"

namespace OpcUaStackCore
{

	class SecureChannelServerConfig
	: public SecureChannelConfig
	{
	  public:
		typedef boost::shared_ptr<SecureChannelServerConfig> SPtr;

		SecureChannelServerConfig(void);
		~SecureChannelServerConfig(void);

		void endpointUrl(const std::string& endpointUrl);
		std::string& endpointUrl(void);
		void securityMode(SecurityMode securityMode);
		SecurityMode securityMode(void);
		void securityPolicy(SecurityPolicy securityPolicy);
		SecurityPolicy securityPolicy(void);

	  private:
		std::string endpointUrl_;
		SecurityMode securityMode_;
		SecurityPolicy securityPolicy_;
	};

}

#endif
