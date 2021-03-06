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

#include "OpcUaStackCore/ServiceSet/QueryFirstRequest.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa QueryFirstRequest
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	QueryFirstRequest::QueryFirstRequest(void)
	: ObjectPool<QueryFirstRequest>()
	, view_()
	, nodeTypeArraySPtr_(NodeTypeDescriptionArray::construct())
	, filter_()
	, maxDataSetsToReturn_()
	, maxReferencesToReturn_()
	{
	}


	QueryFirstRequest::~QueryFirstRequest(void)
	{
	}

	void 
	QueryFirstRequest::view(const ViewDescription& view)
	{
		view_ = view;
	}
	
	ViewDescription& 
	QueryFirstRequest::view(void)
	{
		return view_;
	}
	
	void 
	QueryFirstRequest::nodeTypes(const NodeTypeDescriptionArray::SPtr nodeTypes)
	{
		nodeTypeArraySPtr_ = nodeTypes;
	}
	
	NodeTypeDescriptionArray::SPtr 
	QueryFirstRequest::nodeTypes(void) const
	{
		return nodeTypeArraySPtr_;
	}
	
	void 
	QueryFirstRequest::filter(const ContentFilter& filter)
	{
		filter_ = filter;
	}
	
	ContentFilter& 
	QueryFirstRequest::filter(void)
	{
		return filter_;
	}
	
	void 
	QueryFirstRequest::maxDataSetsToReturn(const OpcUaUInt32& maxDataSetsToReturn)
	{
		maxDataSetsToReturn_ = maxDataSetsToReturn;
	}
	
	OpcUaUInt32 
	QueryFirstRequest::maxDataSetsToReturn(void)
	{
		return maxDataSetsToReturn_;
	}
	
	void 
	QueryFirstRequest::maxReferencesToReturn(const OpcUaUInt32& maxReferencesToReturn)
	{
		maxReferencesToReturn_ = maxReferencesToReturn;
	}
	
	OpcUaUInt32 
	QueryFirstRequest::maxReferencesToReturn(void)
	{
		return maxReferencesToReturn_;
	}

	void 
	QueryFirstRequest::opcUaBinaryEncode(std::ostream& os) const
	{
		view_.opcUaBinaryEncode(os);
		nodeTypeArraySPtr_->opcUaBinaryEncode(os);
		filter_.opcUaBinaryEncode(os);
		OpcUaNumber::opcUaBinaryEncode(os, maxDataSetsToReturn_);
		OpcUaNumber::opcUaBinaryEncode(os, maxReferencesToReturn_);
	}
	
	void 
	QueryFirstRequest::opcUaBinaryDecode(std::istream& is)
	{
		view_.opcUaBinaryDecode(is);
		nodeTypeArraySPtr_->opcUaBinaryDecode(is);
		filter_.opcUaBinaryDecode(is);
		OpcUaNumber::opcUaBinaryDecode(is, maxDataSetsToReturn_);
		OpcUaNumber::opcUaBinaryDecode(is, maxReferencesToReturn_);
	}
}
