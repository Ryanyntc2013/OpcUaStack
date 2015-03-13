#ifndef __OpcUaStackCore_DataChangeFilter_h__
#define __OpcUaStackCore_DataChangeFilter_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameterBase.h"

namespace OpcUaStackCore
{

	class DLLEXPORT DataChangeFilter : public  ObjectPool<DataChangeFilter>, public ExtensibleParameterBase
	{
	  public:
		typedef boost::shared_ptr<DataChangeFilter> SPtr;

		DataChangeFilter(void);
		virtual ~DataChangeFilter(void);

		void trigger(const DataChangeTrigger trigger);
		DataChangeTrigger trigger(void);
		void deadbandType(const OpcUaUInt32& deadBandType);
		OpcUaUInt32 deadbandType(void);
		void deadbandValue(const OpcUaDouble& deadbandValue);
		OpcUaDouble deadbandValue(void);
		
		//- ExtensibleParameterBase -------------------------------------------
		virtual ExtensibleParameterBase::BSPtr factory(void);
		//- ExtensibleParameterBase -------------------------------------------

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		DataChangeTrigger trigger_;
		OpcUaUInt32 deadbandType_;
		OpcUaDouble deadbandValue_;
	};

}

#endif