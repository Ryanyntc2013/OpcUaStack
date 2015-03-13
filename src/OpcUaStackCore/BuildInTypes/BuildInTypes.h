#ifndef __OpcUaStackCore_BuildInTypes_h__
#define __OpcUaStackCore_BuildInTypes_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaNumber.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaString.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDateTime.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaGuid.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaByteString.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaXmlElement.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaExpandedNodeId.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaQualifiedName.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaLocalizedText.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaExtensionObject.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDataValue.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaArray.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDiagnosticInfo.h"


namespace OpcUaStackCore
{

	typedef OpcUaDateTime UtcTime;
	typedef OpcUaDateTimeArray UtcTimeArray;
	typedef OpcUaUInt32 IntegerId;
	typedef OpcUaDouble Duration;
	typedef OpcUaStringArray LocaleIdArray;

};

#endif