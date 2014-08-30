#include "OpcUaStackCore/ServiceSet/DataTypeAttributes.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// DataTypeAttributes
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	DataTypeAttributes::DataTypeAttributes(void)
		: ExtensibleParameterBase()
		, specifiedAttributes_(),
		displayName_(OpcUaLocalizedText::construct()),
		description_(OpcUaLocalizedText::construct()),
		isAbstract_(false),
		writeMask_(),
		userWriteMask_()
	{
		specifiedAttributes_ |= SpecifiedAttributes_Description;
		specifiedAttributes_ |= SpecifiedAttributes_DisplayName;
		specifiedAttributes_ |= SpecifiedAttributes_IsAbstract;
		specifiedAttributes_ |= SpecifiedAttributes_WriteMask;
		specifiedAttributes_ |= SpecifiedAttributes_UserWriteMask;
	}

	DataTypeAttributes::~DataTypeAttributes(void)
	{
	}

	 OpcUaUInt32
     DataTypeAttributes::specifiedAttributes(void) const
	 {
		 return specifiedAttributes_;
	 }

	void
	DataTypeAttributes::displayName(
		const OpcUaLocalizedText::SPtr displayNameSPtr)
	{
		displayName_ = displayNameSPtr;		
	}

    OpcUaLocalizedText::SPtr
	DataTypeAttributes::displayName(void) const
	{
		return displayName_;
	}

	void
	DataTypeAttributes::description(
		const OpcUaLocalizedText::SPtr descriptionSPtr)
	{
		description_ = descriptionSPtr;
	}

    OpcUaLocalizedText::SPtr
	DataTypeAttributes::description(void) const
	{
		return description_;
	}

	void DataTypeAttributes::isAbstract(
		const OpcUaBoolean isAbstract)
	{
		isAbstract_ = isAbstract;
	}

    OpcUaBoolean
	DataTypeAttributes::isAbstract(void) const
	{
		return isAbstract_;
	}

	void DataTypeAttributes::writeMask(
		const WriteableAttribute writeMask)
	{
		writeMask_ |= writeMask;
	}

    OpcUaUInt32
	DataTypeAttributes::writeMask(void) const
	{
		return writeMask_;
	}

	
	void DataTypeAttributes::userWriteMask(
		const WriteableAttribute userWriteMask)
	{
		userWriteMask_ |= userWriteMask;
	}

    OpcUaUInt32
	DataTypeAttributes::userWriteMask(void) const
	{
		return userWriteMask_;
	}

	ExtensibleParameterBase::BSPtr 
	DataTypeAttributes::factory(void)
	{
		return DataTypeAttributes::construct();
	}
			
	void 
	DataTypeAttributes::opcUaBinaryEncode(
		std::ostream& os) const
	{
		OpcUaNumber::opcUaBinaryEncode(os, specifiedAttributes_);
		displayName_->opcUaBinaryEncode(os);
		description_->opcUaBinaryEncode(os);
		OpcUaNumber::opcUaBinaryEncode(os, isAbstract_);
		OpcUaNumber::opcUaBinaryEncode(os, writeMask_);
		OpcUaNumber::opcUaBinaryEncode(os, userWriteMask_);
	}
	
	void 
	DataTypeAttributes::opcUaBinaryDecode(
		std::istream& is)
	{
		OpcUaNumber::opcUaBinaryDecode(is, specifiedAttributes_);
		displayName_->opcUaBinaryDecode(is);
		description_->opcUaBinaryDecode(is);
		OpcUaNumber::opcUaBinaryDecode(is, isAbstract_);
		OpcUaNumber::opcUaBinaryDecode(is, writeMask_);
		OpcUaNumber::opcUaBinaryDecode(is, userWriteMask_);
	}

}