#include "OpcUaStackCore/ServiceSet/ReadProcessedDetails.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa ReadProcessedDetails
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	ReadProcessedDetails::ReadProcessedDetails(void)
	: ObjectPool<ReadProcessedDetails>()
	, startTime_()
	, endTime_()
	, resampleInterval_()
	, aggregateTypeArraySPtr_(OpcUaNodeIdArray::construct())
	, aggregateConfiguration_()
	{
	}

	ReadProcessedDetails::~ReadProcessedDetails(void)
	{
	}
	
	void 
	ReadProcessedDetails::startTime(const UtcTime& startTime)
	{
		startTime_ = startTime;
	}
	
	void 
	ReadProcessedDetails::startTime(const boost::posix_time::ptime& startTime)
	{
		startTime_.dateTime(startTime);
	}
	
	UtcTime& 
	ReadProcessedDetails::startTime(void)
	{
		return startTime_;
	}
	
	void 
	ReadProcessedDetails::endTime(const UtcTime& endTime)
	{
		endTime_ = endTime;
	}

	void 
	ReadProcessedDetails::endTime(const boost::posix_time::ptime& endTime)
	{
		endTime_.dateTime(endTime);
	}
	
	UtcTime& 
	ReadProcessedDetails::endTime(void)
	{
		return endTime_;
	}

	void 
	ReadProcessedDetails::resampleInterval(const OpcUaDouble& resampleInterval)
	{
		resampleInterval_ = resampleInterval;
	}
	
	OpcUaDouble 
	ReadProcessedDetails::resampleInterval(void)
	{
		return resampleInterval_;
	}
	
	void 
	ReadProcessedDetails::aggregateType(const OpcUaNodeIdArray::SPtr aggregateType)
	{
		aggregateTypeArraySPtr_ = aggregateType;
	}
	
	OpcUaNodeIdArray::SPtr 
	ReadProcessedDetails::aggregateType(void) const
	{
		return aggregateTypeArraySPtr_;
	}
	
	void 
	ReadProcessedDetails::aggregateConfiguration(const AggregateConfiguration& aggregateConfiguration)
	{
		aggregateConfiguration_ = aggregateConfiguration;
	}
	
	AggregateConfiguration& 
	ReadProcessedDetails::aggregateConfiguration(void)
	{
		return aggregateConfiguration_;
	}

	ExtensibleParameterBase::BSPtr 
	ReadProcessedDetails::factory(void)
	{
		return ReadProcessedDetails::construct();
	}

	void 
	ReadProcessedDetails::opcUaBinaryEncode(std::ostream& os) const
	{
		startTime_.opcUaBinaryEncode(os);
		endTime_.opcUaBinaryEncode(os);
		OpcUaNumber::opcUaBinaryEncode(os, resampleInterval_);
		aggregateTypeArraySPtr_->opcUaBinaryEncode(os);
		aggregateConfiguration_.opcUaBinaryEncode(os);
	}
	
	void 
	ReadProcessedDetails::opcUaBinaryDecode(std::istream& is)
	{
		startTime_.opcUaBinaryDecode(is);
		endTime_.opcUaBinaryDecode(is);
		OpcUaNumber::opcUaBinaryDecode(is, resampleInterval_);
		aggregateTypeArraySPtr_->opcUaBinaryDecode(is);
		aggregateConfiguration_.opcUaBinaryDecode(is);
	}
}