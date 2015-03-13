#ifndef __OpcUaStackCore_OpcUaXmlElement_h__
#define __OpcUaStackCore_OpcUaXmlElement_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaNumber.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackCore
{

	class DLLEXPORT OpcUaXmlElement : public ObjectPool<OpcUaXmlElement>
	{
	  public:
		typedef boost::shared_ptr<OpcUaXmlElement> SPtr;

	    OpcUaXmlElement(void);
		~OpcUaXmlElement(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		
	};

	class OpcUaXmlElementArray : public OpcUaArray<OpcUaXmlElement::SPtr, SPtrTypeCoder<OpcUaXmlElement> >, public ObjectPool<OpcUaXmlElementArray> 
	{
	  public:
		typedef boost::shared_ptr<OpcUaXmlElementArray> SPtr;
	};

}

#endif