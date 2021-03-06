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

#ifndef __OpcUaStackCore_QueryNextResponse_h__
#define __OpcUaStackCore_QueryNextResponse_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/ResponseHeader.h"
#include "OpcUaStackCore/ServiceSet/QueryDataSet.h"

namespace OpcUaStackCore
{

	class DLLEXPORT QueryNextResponse : public  ObjectPool<QueryNextResponse>
	{
	  public:
		typedef boost::shared_ptr<QueryNextResponse> SPtr;

		QueryNextResponse(void);
		virtual ~QueryNextResponse(void);

		void queryDataSets(const QueryDataSetArray::SPtr queryDataSets);
		QueryDataSetArray::SPtr queryDataSets(void) const;
		void revisedContinuationPoint(const OpcUaByteString& revisedContinuationPoint);
		OpcUaByteString& revisedContinuationPoint(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		QueryDataSetArray::SPtr queryDataSetArraySPtr_;
		OpcUaByteString revisedContinuationPoint_;
	};

}

#endif
