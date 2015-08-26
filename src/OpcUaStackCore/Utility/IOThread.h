#ifndef __OpcUaStackCore_IOThread_h__
#define __OpcUaStackCore_IOThread_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaStackCore/Base/IOService.h"
#include "OpcUaStackCore/Utility/SlotTimer.h"

namespace OpcUaStackCore
{

	class IOThread
	{
	  public:
		IOThread(void);
		~IOThread(void);

		void ioService(const IOService::SPtr& ioService);
		IOService::SPtr& ioService(void);
		void slotTimer(const SlotTimer::SPtr& slotTimer);
		SlotTimer::SPtr& slotTimer(void);
		void numberThreads(uint32_t numberThreads);

		bool startup(void);
		bool shutdown(void);

	  private:
		void createIOService(void);
		void deleteIOService(void);
		void createSlotTimer(void);
		void deleteSlotTimer(void);

		uint32_t numberThreads_;
		IOService::SPtr ioService_;
		SlotTimer::SPtr slotTimer_;
		bool ioServiceCreateFlag_;
		bool slotTimerCreateFlag_;
	};

}

#endif