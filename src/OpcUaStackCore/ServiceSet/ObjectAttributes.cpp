#include "OpcUaStackCore/ServiceSet/ObjectAttributes.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ObjectAttributes
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	ObjectAttributes::ObjectAttributes(void)
		: ExtensibleParameterBase(),
		specifiedAttributes_(),
		displayName_(OpcUaLocalizedText::construct()),
		description_(OpcUaLocalizedText::construct()),
		eventNotifier_(),
		writeMask_(),
		userWriteMask_()
	{
		specifiedAttributes_ |= SpecifiedAttributes_Description;
		specifiedAttributes_ |= SpecifiedAttributes_DisplayName;
		specifiedAttributes_ |= SpecifiedAttributes_EventNotifier;
		specifiedAttributes_ |= SpecifiedAttributes_WriteMask;
		specifiedAttributes_ |= SpecifiedAttributes_UserWriteMask;
	}

	ObjectAttributes::~ObjectAttributes(void)
	{
	}

	 OpcUaUInt32
     ObjectAttributes::specifiedAttributes(void) const
	 {
		 return specifiedAttributes_;
	 }

	void
	ObjectAttributes::displayName(
		const OpcUaLocalizedText::SPtr displayNameSPtr)
	{
		displayName_ = displayNameSPtr;		
	}

    OpcUaLocalizedText::SPtr
	ObjectAttributes::displayName(void) const
	{
		return displayName_;
	}

	void
	ObjectAttributes::description(
		const OpcUaLocalizedText::SPtr descriptionSPtr)
	{
		description_ = descriptionSPtr;
	}

    OpcUaLocalizedText::SPtr
	ObjectAttributes::description(void) const
	{
		return description_;
	}

	void ObjectAttributes::eventNotifier(
		const EventNotifierAttribute eventNotifier)
	{
		eventNotifier_ |= eventNotifier;
	}

    OpcUaByte
	ObjectAttributes::eventNotifier(void) const
	{
		return eventNotifier_;
	}

	void ObjectAttributes::writeMask(
		const WriteableAttribute writeMask)
	{
		writeMask_ |= writeMask;
	}

    OpcUaUInt32
	ObjectAttributes::writeMask(void) const
	{
		return writeMask_;
	}

	
	void ObjectAttributes::userWriteMask(
		const WriteableAttribute userWriteMask)
	{
		userWriteMask_ |= userWriteMask;
	}

    OpcUaUInt32
	ObjectAttributes::userWriteMask(void) const
	{
		return userWriteMask_;
	}

	ExtensibleParameterBase::BSPtr 
	ObjectAttributes::factory(void)
	{
		return ObjectAttributes::construct();
	}
			
	void 
	ObjectAttributes::opcUaBinaryEncode(
		std::ostream& os) const
	{
		OpcUaNumber::opcUaBinaryEncode(os, specifiedAttributes_);
		displayName_->opcUaBinaryEncode(os);
		description_->opcUaBinaryEncode(os);
		OpcUaNumber::opcUaBinaryEncode(os, eventNotifier_);
		OpcUaNumber::opcUaBinaryEncode(os, writeMask_);
		OpcUaNumber::opcUaBinaryEncode(os, userWriteMask_);
	}
	
	void 
	ObjectAttributes::opcUaBinaryDecode(
		std::istream& is)
	{
		OpcUaNumber::opcUaBinaryDecode(is, specifiedAttributes_);
		displayName_->opcUaBinaryDecode(is);
		description_->opcUaBinaryDecode(is);
		OpcUaNumber::opcUaBinaryDecode(is, eventNotifier_);
		OpcUaNumber::opcUaBinaryDecode(is, writeMask_);
		OpcUaNumber::opcUaBinaryDecode(is, userWriteMask_);
	}

}