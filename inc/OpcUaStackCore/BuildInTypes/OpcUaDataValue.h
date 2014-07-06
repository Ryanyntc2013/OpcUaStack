#ifndef __OpcUaStackCore_OpcUaDataValue_h__
#define __OpcUaStackCore_OpcUaDataValue_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaNumber.h"
#include "OpcUaStackCOre/BuildInTypes/OpcUaVariant.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDateTime.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackCore
{

	class DLLEXPORT OpcUaDataValue : public ObjectPool<OpcUaDataValue>
	{
	  public:
	    OpcUaDataValue(void);
		~OpcUaDataValue(void);

		void variant(const OpcUaVariant::SPtr& opcUaVariantSPtr);
		OpcUaVariant::SPtr variant(void);
		void statusCode(const OpcUaStatusCode& opcUaStatusCode);
		OpcUaStatusCode statusCode(void);
		void sourceTimestamp(const OpcUaDateTime& sourceTimestamp);
		OpcUaDateTime sourceTimestamp(void);
		void sourcePicoseconds(const OpcUaUInt16& sourcePicoseconds);
		OpcUaInt16 sourcePicoseconds(void);
		void serverTimestamp(const OpcUaDateTime& serverTimestamp);
		OpcUaDateTime serverTimestamp(void);
		void serverPicoseconds(const OpcUaUInt16& serverPicoseconds);
		OpcUaInt16 serverPicoseconds(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaVariant::SPtr opcUaVariantSPtr_;
		OpcUaStatusCode opcUaStatusCode_;
		OpcUaDateTime sourceTimestamp_;
		OpcUaInt16 sourcePicoseconds_;
		OpcUaDateTime serverTimestamp_;
		OpcUaInt16 serverPicoseconds_;
	};

	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaDataValue& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaDataValue& value);


	class OpcUaDataValueArray : public OpcUaArray<OpcUaDataValue::SPtr>, public ObjectPool<OpcUaDataValueArray> {};

	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaDataValueArray& value);
	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaDataValueArray::SPtr& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaDataValueArray& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaDataValueArray::SPtr& value);

}

#endif