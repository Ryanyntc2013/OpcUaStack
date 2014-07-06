#ifndef __OpcUaStackCore_OpcUaLocalizedText_h__
#define __OpcUaStackCore_OpcUaLocalizedText_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaString.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackCore
{

	class DLLEXPORT OpcUaLocalizedText : public ObjectPool<OpcUaLocalizedText>
	{
	  public:
	    OpcUaLocalizedText(void);
		~OpcUaLocalizedText(void);

		void locale(const OpcUaString& locale);
		void locale(const std::string& locale);
		OpcUaString& locale(void);
		void text(const OpcUaString& text);
		void text(const std::string& text);
		OpcUaString& text(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaString locale_;
		OpcUaString text_;
	};

	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaLocalizedText& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaLocalizedText& value);


	class OpcUaLocalizedTextArray : public OpcUaArray<OpcUaLocalizedText::SPtr>, public ObjectPool<OpcUaLocalizedTextArray> {};

	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaLocalizedTextArray& value);
	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaLocalizedTextArray::SPtr& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaLocalizedTextArray& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaLocalizedTextArray::SPtr& value);

}

#endif