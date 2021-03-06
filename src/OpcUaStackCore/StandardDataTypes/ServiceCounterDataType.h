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

   Autor: Samuel Huebl (samuel.huebl@asneg.de)
 */

#ifndef __OpcUaStackCore_ServiceCounterDataType_h__
#define __OpcUaStackCore_ServiceCounterDataType_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaExtensionObjectBase.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNumber.h"

namespace OpcUaStackCore
{

	class DLLEXPORT ServiceCounterDataType
	: public ObjectPool<ServiceCounterDataType>
	, public ExtensionObjectBase
	{
	  public:
		typedef boost::shared_ptr<ServiceCounterDataType> SPtr;

		ServiceCounterDataType(void);
		virtual ~ServiceCounterDataType(void);

		OpcUaUInt32& totalCount(void);
		void totalCount(OpcUaUInt32 totalCount);
		OpcUaUInt32& errorCount(void);
		void errorCount(OpcUaUInt32 errorCount);

		void copyTo(ServiceCounterDataType& serviceCounterDataType);
		bool operator==(const ServiceCounterDataType& serviceCounterDataType) const;

		//- ExtensionObjectBase -----------------------------------------------
		ExtensionObjectBase::BSPtr factory(void);
		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);
		void copyTo(ExtensionObjectBase& extensionObjectBase);
		bool equal(ExtensionObjectBase& extensionObjectBase) const;
		void out(std::ostream& os);
		//- ExtensionObjectBase -----------------------------------------------

	  private:
		OpcUaUInt32 totalCount_;
		OpcUaUInt32 errorCount_;
	};

}

#endif



