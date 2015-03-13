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
		typedef boost::shared_ptr<OpcUaLocalizedText> SPtr;

	    OpcUaLocalizedText(void);
		~OpcUaLocalizedText(void);

		void set(const std::string& locale, const std::string& text);
		void get(std::string& locale, std::string& text);

		void locale(const OpcUaString& locale);
		void locale(const std::string& locale);
		OpcUaString& locale(void);
		void text(const OpcUaString& text);
		void text(const std::string& text);
		OpcUaString& text(void);

		void copyTo(OpcUaLocalizedText& localizedText);

		void out(std::ostream& os) const;
		friend std::ostream& operator<<(std::ostream& os, const OpcUaLocalizedText& value) {
			value.out(os);
			return os;
		}
		bool operator!=(const OpcUaLocalizedText& opcUaLocalizedText) const;
		bool operator==(const OpcUaLocalizedText& opcUaLocalizedText) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaString locale_;
		OpcUaString text_;
	};


	class OpcUaLocalizedTextArray : public OpcUaArray<OpcUaLocalizedText::SPtr, SPtrTypeCoder<OpcUaLocalizedText> >, public ObjectPool<OpcUaLocalizedTextArray> 
	{
	  public:
		typedef boost::shared_ptr<OpcUaLocalizedTextArray> SPtr;
	};

}

#endif