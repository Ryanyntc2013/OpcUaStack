#ifndef __OpcUaStackCore_ReadRawModifiedDetails_h__
#define __OpcUaStackCore_ReadRawModifiedDetails_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameterBase.h"

namespace OpcUaStackCore
{

	class DLLEXPORT ReadRawModifiedDetails : public  ObjectPool<ReadRawModifiedDetails>, public ExtensibleParameterBase
	{
	  public:
		ReadRawModifiedDetails(void);
		virtual ~ReadRawModifiedDetails(void);

		void isReadModified(const OpcUaBoolean& isReadModified);
		OpcUaBoolean isReadModified(void);
		void startTime(const UtcTime& startTime);
		void startTime(const boost::posix_time::ptime& startTime);
		UtcTime& startTime(void);
		void endTime(const UtcTime& endTime);
		void endTime(const boost::posix_time::ptime& endTime);
		UtcTime& endTime(void);
		void numValuesPerNode(const OpcUaUInt32& numValuesPerNode);
		OpcUaUInt32 numValuesPerNode(void) const;
		void returnBoolean(const OpcUaBoolean& returnBoolean);
		OpcUaBoolean returnBoolean(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

		//- ExtensibleParameterBase -------------------------------------------
		virtual ExtensibleParameterBase::BSPtr factory(void);
		//- ExtensibleParameterBase -------------------------------------------

	  private:
		OpcUaBoolean isReadModified_;
		UtcTime startTime_;
		UtcTime endTime_;
		OpcUaUInt32 numValuesPerNode_;
		OpcUaBoolean returnBoolean_;
	};

}

#endif