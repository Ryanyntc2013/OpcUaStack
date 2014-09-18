#include "OpcUaStackCore/ServiceSet/AddReferencesItem.h"
#include "OpcUaStackCore/Base/Utility.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// AddReferencesItem
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	AddReferencesItem::AddReferencesItem(void)
		: sourceNodeIdSPtr_(OpcUaNodeId::construct()),
		referenceTypeIdSPtr_(OpcUaNodeId::construct()),
		isForward_(false),
		targetServerUriSPtr_(OpcUaString::construct()),
		targetNodeIdSPtr_(OpcUaExpandedNodeId::construct()),
		targetNodeClassSPtr_(NodeClass::construct())
	{
	}

	AddReferencesItem::~AddReferencesItem(void)
	{
	}


	void
	AddReferencesItem::sourceNodeId(
		const OpcUaNodeId::SPtr sourceNodeIdSPtr)
	{
		sourceNodeIdSPtr_ = sourceNodeIdSPtr;
	}

	OpcUaNodeId::SPtr
	AddReferencesItem::sourceNodeId(void) const
	{
		return sourceNodeIdSPtr_;
	}

	void
	AddReferencesItem::referenceTypeId(
		const OpcUaNodeId::SPtr referenceTypeIdSPtr)
	{
		referenceTypeIdSPtr_ = referenceTypeIdSPtr;
	}

	OpcUaNodeId::SPtr
	AddReferencesItem::referenceTypeId(void) const
	{
		return referenceTypeIdSPtr_;
	}

	void
	AddReferencesItem::isForward(
		const OpcUaBoolean isForward)
	{
		isForward_ = isForward;
	}

    OpcUaBoolean
	AddReferencesItem::isForward(void) const
	{
		return isForward_;
	}

	void
	AddReferencesItem::targetServerUri(
		const OpcUaString::SPtr targetServerUriSPtr)
	{
		targetServerUriSPtr_ = targetServerUriSPtr;
	}

	
	OpcUaString::SPtr
	AddReferencesItem::targetServerUri(void) const
	{
		return targetServerUriSPtr_;
	}

	void
	AddReferencesItem::targetNodeId(
		const OpcUaExpandedNodeId::SPtr targetNodeIdSPtr)
	{
		targetNodeIdSPtr_ = targetNodeIdSPtr;
	}

	OpcUaExpandedNodeId::SPtr
	AddReferencesItem::targetNodeId(void) const
	{
		return targetNodeIdSPtr_;
	}

	void
	AddReferencesItem::targetNodeClass(
		const NodeClass::SPtr targetNodeClassSPtr)
	{
		targetNodeClassSPtr_ = targetNodeClassSPtr;
	}
	
	NodeClass::SPtr
	AddReferencesItem::targetNodeClass(void) const
	{
		return targetNodeClassSPtr_;
	}

		

	void 
	AddReferencesItem::opcUaBinaryEncode(
		std::ostream& os) const
	{
		sourceNodeIdSPtr_->opcUaBinaryEncode(os);
		referenceTypeIdSPtr_->opcUaBinaryEncode(os);
		OpcUaNumber::opcUaBinaryEncode(os, isForward_);
		targetServerUriSPtr_->opcUaBinaryEncode(os);
		targetNodeIdSPtr_->opcUaBinaryEncode(os);
		targetNodeClassSPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	AddReferencesItem::opcUaBinaryDecode(
		std::istream& is)
	{
		sourceNodeIdSPtr_->opcUaBinaryDecode(is);
		referenceTypeIdSPtr_->opcUaBinaryDecode(is);
		OpcUaNumber::opcUaBinaryDecode(is, isForward_);
		targetServerUriSPtr_->opcUaBinaryDecode(is);
		targetNodeIdSPtr_->opcUaBinaryDecode(is);
		targetNodeClassSPtr_->opcUaBinaryDecode(is);
	}

}