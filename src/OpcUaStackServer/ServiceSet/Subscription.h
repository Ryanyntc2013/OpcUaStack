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

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackServer_Subscription_h__
#define __OpcUaStackServer_Subscription_h__

#include <boost/thread/mutex.hpp>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"
#include "OpcUaStackCore/Utility/SlotTimer.h"
#include "OpcUaStackCore/ServiceSet/SubscriptionServiceTransaction.h"
#include "OpcUaStackCore/ServiceSet/MonitoredItemServiceTransaction.h"
#include "OpcUaStackServer/ServiceSet/MonitorManager.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"
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
		SendPublishKeepalive,
		SubscriptionTimeout,
	} PublishResult;

	class DLLEXPORT Subscription : public ObjectPool<Subscription>
	{
	  public:
		typedef boost::shared_ptr<Subscription> SPtr;

		Subscription(void);
		~Subscription(void);

		uint32_t subscriptionId(void);
		void publishingInterval(double publishingInterval);	
		void lifetimeCount(uint32_t lifetimeCount);
		void maxKeepAliveCount(uint32_t maxKeepAliveCount);
		void ioService(IOService* ioService);
		void informationModel(InformationModel::SPtr informationModel);

		void retransmissionQueue(SubscriptionAcknowledgement::SPtr subscriptionAcknowledgement);
		void retransmissionQueue(PublishResponse::SPtr publishResponse);

		PublishResult publish(ServiceTransactionPublish::SPtr trx);
		uint32_t publishPre(void);

		// monitored item
		OpcUaStatusCode receive(ServiceTransactionCreateMonitoredItems::SPtr trx);
		OpcUaStatusCode receive(ServiceTransactionDeleteMonitoredItems::SPtr trx);
		OpcUaStatusCode receive(ServiceTransactionModifyMonitoredItems::SPtr trx);
		OpcUaStatusCode receive(ServiceTransactionSetMonitoringMode::SPtr trx);
		OpcUaStatusCode receive(ServiceTransactionSetTriggering::SPtr trx);

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

		IOService* ioService_;
		MonitorManager monitorManager_;
	};

	typedef std::map<uint32_t, Subscription::SPtr> SubscriptionMap;
}

#endif
