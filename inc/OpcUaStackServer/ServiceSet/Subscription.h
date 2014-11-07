#ifndef __OpcUaStackServer_Subscription_h__
#define __OpcUaStackServer_Subscription_h__

#include <boost/thread/mutex.hpp>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"
#include "OpcUaStackCore/Utility/SlotTimer.h"
#include "OpcUaStackCore/ServiceSet/SubscriptionServiceTransaction.h"
#include <map>

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	typedef std::map<uint32_t, PublishResponse::SPtr> RetransmissionQueue; 
	typedef enum
	{
		NothingTodo,
		NeedAttention,
		SendPublish,
		SubscriptionTimeout,
	} PublishResult;

	class DLLEXPORT Subscription : public ObjectPool<Subscription>
	{
	  public:
		Subscription(void);
		~Subscription(void);

		uint32_t subscriptionId(void);
		void publishingInterval(double publishingInterval);	
		void lifetimeCount(uint32_t lifetimeCount);
		void maxKeepAliveCount(uint32_t maxKeepAliveCount);

		void retransmissionQueue(SubscriptionAcknowledgement::SPtr subscriptionAcknowledgement);
		void retransmissionQueue(PublishResponse::SPtr publishResponse);

		PublishResult publish(ServiceTransactionPublish::SPtr trx);
		uint32_t publishPre(void);

		SlotTimerElement::SPtr slotTimerElement(void);

	  private:
		void createKeepalive(ServiceTransactionPublish::SPtr trx);

		static uint32_t uniqueSubscriptionId(void);
		static uint32_t sequenceNumber(void);
		static boost::mutex mutex_;
		static uint32_t uniqueSubscriptionId_;
		static uint32_t sequenceNumber_;

		uint32_t subscriptionId_;
		double publishingInterval_;
		uint32_t lifetimeCount_;
		uint32_t actLifetimeCount_;
		uint32_t maxKeepAliveCount_;
		uint32_t actMaxKeepAliveCount_;
		SlotTimerElement::SPtr slotTimerElement_;
		RetransmissionQueue retransmissionQueue_;
	};

	typedef std::map<uint32_t, Subscription::SPtr> SubscriptionMap;
}

#endif