#ifndef __OpcUaStackCore_ReadProcessedDetails_h__
#define __OpcUaStackCore_ReadProcessedDetails_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/AggregateConfiguration.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameterBase.h"

namespace OpcUaStackCore
{

	class DLLEXPORT ReadProcessedDetails : public  ObjectPool<ReadProcessedDetails>, public ExtensibleParameterBase
	{
	  public:
		ReadProcessedDetails(void);
		virtual ~ReadProcessedDetails(void);

		void startTime(const UtcTime& startTime);
		void startTime(const boost::posix_time::ptime& startTime);
		UtcTime& startTime(void);
		void endTime(const UtcTime& endTime);
		void endTime(const boost::posix_time::ptime& endTime);
		UtcTime& endTime(void);
		void resampleInterval(const OpcUaDouble& resampleInterval);
		OpcUaDouble resampleInterval(void);
		void aggregateType(const OpcUaNodeIdArray::SPtr aggregateType);
		OpcUaNodeIdArray::SPtr aggregateType(void) const;
		void aggregateConfiguration(const AggregateConfiguration& aggregateConfiguration);
		AggregateConfiguration& aggregateConfiguration(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

		//- ExtensibleParameterBase -------------------------------------------
		virtual ExtensibleParameterBase::BSPtr factory(void);
		//- ExtensibleParameterBase -------------------------------------------

	  private:
		UtcTime startTime_;
		UtcTime endTime_;
		OpcUaDouble resampleInterval_;
		OpcUaNodeIdArray::SPtr aggregateTypeArraySPtr_;
		AggregateConfiguration aggregateConfiguration_;
	};

}

#endif