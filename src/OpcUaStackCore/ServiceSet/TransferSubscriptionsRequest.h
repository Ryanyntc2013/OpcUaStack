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

#ifndef __OpcUaStackCore_TransferSubscriptionsRequest_h__
#define __OpcUaStackCore_TransferSubscriptionsRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"

namespace OpcUaStackCore
{

	class DLLEXPORT TransferSubscriptionsRequest : public  ObjectPool<TransferSubscriptionsRequest>
	{
	  public:
		typedef boost::shared_ptr<TransferSubscriptionsRequest> SPtr;

		TransferSubscriptionsRequest(void);
		virtual ~TransferSubscriptionsRequest(void);

		void subscriptionIds(const OpcUaUInt32Array::SPtr subscriptionIds);
		OpcUaUInt32Array::SPtr subscriptionIds(void) const;
		void sendInitialValues(const OpcUaBoolean& sendInitialValues);
		OpcUaBoolean sendInitialValues(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaUInt32Array::SPtr subscriptionIdArraySPtr_;
		OpcUaBoolean sendInitialValues_;
	};

}

#endif
