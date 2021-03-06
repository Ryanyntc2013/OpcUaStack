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

#ifndef __OpcUaStackCore_PkiCertificateInfo_h__
#define __OpcUaStackCore_PkiCertificateInfo_h__

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <vector>
#include <stdint.h>
#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackCore
{

	class DLLEXPORT PkiCertificateInfo
	{
	  public:
		PkiCertificateInfo(void);
		~PkiCertificateInfo(void);

		void URI(const std::string& URI);
		std::string& URI(void);
		void ipAddresses(const std::vector<std::string>& ipAddresses);
		std::vector<std::string>& ipAddresses(void);
		void dnsNames(const std::vector<std::string>& dnsNames);
		std::vector<std::string>& dnsNames(void);
		void email(const std::vector<std::string>& email);
		std::vector<std::string>& email(void);
		void validTimeNotAfter(const boost::posix_time::ptime& validTimeNotAfter);
		boost::posix_time::ptime& validTimeNotAfter(void);
		void validTimeNotBefore(const boost::posix_time::ptime& validTimeNotBefore);
		boost::posix_time::ptime& validTimeNotBefore(void);

	  private:
	    std::string URI_;
	    std::vector<std::string> ipAddresses_;
	    std::vector<std::string> dnsNames_;
	    std::vector<std::string> emails_;
	    boost::posix_time::ptime validTimeNotAfter_;
	    boost::posix_time::ptime validTimeNotBefore_;
	};

}

#endif
