#ifndef __OpcUaStackCore_OpcUaString_h__
#define __OpcUaStackCore_OpcUaString_h__

#include "OpcUaStackCore/Base/ObjectPool.h"
#include <string>
#include <stdint.h>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaArray.h"

namespace OpcUaStackCore
{

	class DLLEXPORT OpcUaString : public ObjectPool<OpcUaString>
	{
	  public:
	    OpcUaString(void);
		~OpcUaString(void);

		std::string value(void) const;
		void value(const std::string& value);
		uint32_t size(void) const;
		void reset(void);
		bool exist(void) const;

		OpcUaString& operator=(const std::string& string); 
		operator std::string const (void); 

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		bool exist_;
		std::string value_; 
	};

	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaString& value);
	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaString::SPtr& valueSPtr);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaString& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaString::SPtr& valueSPtr);


	class OpcUaStringArray : public OpcUaArray<OpcUaString::SPtr>, public ObjectPool<OpcUaStringArray> {};

	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaStringArray& value);
	DLLEXPORT void opcUaBinaryEncode(std::ostream& os, const OpcUaStringArray::SPtr& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaStringArray& value);
	DLLEXPORT void opcUaBinaryDecode(std::istream& is, OpcUaStringArray::SPtr& value);

}

#endif