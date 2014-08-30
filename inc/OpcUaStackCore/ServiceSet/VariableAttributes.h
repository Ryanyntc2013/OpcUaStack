#ifndef __OpcUaStackCore_VariableAttributes_h__
#define __OpcUaStackCore_VariableAttributes_h__

#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameter.h"
#include "OpcUaStackCore/ServiceSet/AttributesDescription.h"


namespace OpcUaStackCore
{

	class DLLEXPORT VariableAttributes : public  ObjectPool<VariableAttributes>, public ExtensibleParameterBase
	{
	  public:
		VariableAttributes(void);
		virtual ~VariableAttributes(void);

		//- ExtensibleParameterBase -------------------------------------------
		virtual ExtensibleParameterBase::BSPtr factory(void);
		virtual void opcUaBinaryEncode(std::ostream& os) const;
		virtual void opcUaBinaryDecode(std::istream& is);
		//- ExtensibleParameterBase -------------------------------------------


        OpcUaUInt32 specifiedAttributes(void) const;
        void displayName(const OpcUaLocalizedText::SPtr displayNameSPtr);
        OpcUaLocalizedText::SPtr displayName(void) const;
        void description(const OpcUaLocalizedText::SPtr descriptionSPtr);
        OpcUaLocalizedText::SPtr description(void) const;
        void value(const OpcUaDataValue::SPtr valueSPtr);
        OpcUaDataValue::SPtr value(void) const;
        void dataType(const OpcUaNodeId::SPtr dataTypeSPtr);
        OpcUaNodeId::SPtr dataType(void) const;
        void valueRank(const OpcUaInt32 valueRank);
        OpcUaInt32 valueRank(void) const;
        void arrayDimensions(const OpcUaUInt32Array::SPtr arrayDimensionsSPtr);
        OpcUaUInt32Array::SPtr arrayDimensions(void) const;
        void accessLevel(const OpcUaByte accessLevel);
        OpcUaByte accessLevel(void) const;
        void userAccessLevel(const OpcUaByte userAccessLevel);
        OpcUaByte userAccessLevel(void) const;
        void minimumSamplingInterval(const Duration minimumSamplingInterval);
        Duration minimumSamplingInterval(void) const;
        void historizing(const OpcUaBoolean historizing);
        OpcUaBoolean historizing(void) const;
        void writeMask(const WriteableAttribute writeMask);
        OpcUaUInt32 writeMask(void) const;
        void userWriteMask(const WriteableAttribute userWriteMask);
        OpcUaUInt32 userWriteMask(void) const;
		
	  private:
		OpcUaUInt32 specifiedAttributes_;
		OpcUaLocalizedText::SPtr displayName_;
		OpcUaLocalizedText::SPtr description_;
		OpcUaDataValue::SPtr value_;
		OpcUaNodeId::SPtr dataType_;
		OpcUaInt32 valueRank_;
        OpcUaUInt32Array::SPtr arrayDimensions_; 
        OpcUaByte accessLevel_;
        OpcUaByte userAccessLevel_;
        Duration minimumSamplingInterval_;
        OpcUaBoolean historizing_;
        OpcUaUInt32 writeMask_;
		OpcUaUInt32 userWriteMask_;        
	};

}

#endif