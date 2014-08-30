#ifndef __OpcUaStackCore_EventFieldList_h__
#define __OpcUaStackCore_EventFieldList_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaArray.h"
#include "OpcUaStackCore/ServiceSet/EventField.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameterBase.h"

namespace OpcUaStackCore
{

	class DLLEXPORT EventFieldList : public  ObjectPool<EventFieldList>
	{
	  public:
		EventFieldList(void);
		virtual ~EventFieldList(void);

		void clientHandle(const OpcUaUInt32& clientHandle);
		OpcUaUInt32 clientHandle(void) const;
		void eventFields(const EventFieldArray::SPtr eventFieldList);
		EventFieldArray::SPtr eventFields(void) const;
		
		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaUInt32 clientHandle_;
		EventFieldArray::SPtr eventFieldsSPtr_;
	};

	class EventFieldListArray : public OpcUaArray<EventFieldList::SPtr, SPtrTypeCoder<EventFieldList> >, public ObjectPool<EventFieldListArray> {};

}

#endif