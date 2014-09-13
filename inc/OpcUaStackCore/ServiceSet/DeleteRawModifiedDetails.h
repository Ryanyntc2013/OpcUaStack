#ifndef __OpcUaStackCore_DeleteRawModifiedDetails_h__
#define __OpcUaStackCore_DeleteRawModifiedDetails_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameterBase.h"

namespace OpcUaStackCore
{

	class DLLEXPORT DeleteRawModifiedDetails : public  ObjectPool<DeleteRawModifiedDetails>, public ExtensibleParameterBase
	{
	  public:
		DeleteRawModifiedDetails(void);
		virtual ~DeleteRawModifiedDetails(void);

		void nodeId(const OpcUaNodeId& nodeId);
		OpcUaNodeId& nodeId(void);
		void isDeleteModified(const OpcUaBoolean& isDeleteModified);
		OpcUaBoolean isDeleteModified(void);
		void startTime(const UtcTime& startTime);
		void startTime(const boost::posix_time::ptime& startTime);
		UtcTime& startTime(void);
		void endTime(const UtcTime& endTime);
		void endTime(const boost::posix_time::ptime& endTime);
		UtcTime& endTime(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

		//- ExtensibleParameterBase -------------------------------------------
		virtual ExtensibleParameterBase::BSPtr factory(void);
		//- ExtensibleParameterBase -------------------------------------------

	  private:
		OpcUaNodeId nodeId_;
		OpcUaBoolean isDeleteModified_;
		UtcTime startTime_;
		UtcTime endTime_;
	};

}

#endif