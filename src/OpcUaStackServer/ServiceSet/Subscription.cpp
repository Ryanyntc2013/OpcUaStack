#include "OpcUaStackServer/ServiceSet/Subscription.h"

namespace OpcUaStackServer
{

	uint32_t Subscription::uniqueSubscriptionId_ = 0;
	uint32_t Subscription::sequenceNumber_;
	boost::mutex Subscription::mutex_;

	uint32_t 
	Subscription::uniqueSubscriptionId(void) 
	{ 
		boost::mutex::scoped_lock g(mutex_);
		uniqueSubscriptionId_++;
		return uniqueSubscriptionId_;
	}

	uint32_t 
	Subscription::sequenceNumber(void)
	{
		boost::mutex::scoped_lock g(mutex_);
		sequenceNumber_++;
		if (sequenceNumber_ == 0) sequenceNumber_;
		return sequenceNumber_;
	}

	Subscription::Subscription(void)
	: subscriptionId_(uniqueSubscriptionId())
	, slotTimerElement_(SlotTimerElement::construct())
	, retransmissionQueue_()
	{
	}

	Subscription::~Subscription(void)
	{
		retransmissionQueue_.clear();
	}

	uint32_t 
	Subscription::subscriptionId(void)
	{
		return subscriptionId_;
	}

	void 
	Subscription::publishingInterval(double publishingInterval)
	{
		publishingInterval_ = publishingInterval;
	}
		
	SlotTimerElement::SPtr 
	Subscription::slotTimerElement(void)
	{
		return slotTimerElement_;
	}

	void 
	Subscription::lifetimeCount(uint32_t lifetimeCount)
	{
		lifetimeCount_ = lifetimeCount;
		actLifetimeCount_ = lifetimeCount;
	}

	void 
	Subscription::maxKeepAliveCount(uint32_t maxKeepAliveCount)
	{
		maxKeepAliveCount_ = maxKeepAliveCount;
		actMaxKeepAliveCount_  = maxKeepAliveCount;
	}
		
	uint32_t 
	Subscription::publishPre(void)
	{
		return 0;
	}

	PublishResult 
	Subscription::publish(ServiceTransactionPublish::SPtr trx)
	{
		if (trx.get() == NULL) {
			actLifetimeCount_--;
			if (actLifetimeCount_ == 0) return SubscriptionTimeout;

			if (actMaxKeepAliveCount_ == 0) return NothingTodo;

			// calculate keepalive count
			actMaxKeepAliveCount_--;
			if (actMaxKeepAliveCount_ == 0) return NeedAttention;

			return NothingTodo;
		}

		// FIXME: todo

		// check lifetime counter
		actLifetimeCount_ = lifetimeCount_;

		// check keepalive counter
		actMaxKeepAliveCount_--;
		if (actMaxKeepAliveCount_ == 0) {
			actMaxKeepAliveCount_  = maxKeepAliveCount_;

			createKeepalive(trx);
			return SendPublish;
		}

		return NothingTodo;
	}

	void 
	Subscription::createKeepalive(ServiceTransactionPublish::SPtr trx)
	{
		PublishRequest::SPtr publishRequest = trx->request();
		PublishResponse::SPtr publishResponse = trx->response();
		ServiceTransaction::SPtr serviceTransaction = trx;

		publishResponse->notificationMessage()->publishTime().dateTime(boost::posix_time::microsec_clock::local_time());
		publishResponse->notificationMessage()->sequenceNumber(sequenceNumber());
		publishResponse->subscriptionId(subscriptionId_);
		publishResponse->moreNotifications(false);
	}

	void 
	Subscription::retransmissionQueue(SubscriptionAcknowledgement::SPtr subscriptionAcknowledgement)
	{
		retransmissionQueue_.erase(subscriptionAcknowledgement->sequenceNumber());
	}
		
	void 
	Subscription::retransmissionQueue(PublishResponse::SPtr publishResponse)
	{
		publishResponse->availableSequenceNumbers()->resize(retransmissionQueue_.size());

		uint32_t idx = 0;
		RetransmissionQueue::iterator it;
		for (it=retransmissionQueue_.begin(); it!=retransmissionQueue_.end(); it++) {
			publishResponse->availableSequenceNumbers()->set(idx, it->first);
			idx++;
		}

		retransmissionQueue_.insert(std::make_pair(publishResponse->notificationMessage()->sequenceNumber(), publishResponse));
	}

}