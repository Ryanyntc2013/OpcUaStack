#ifndef __OpcUaStackCore_ConfigXml_h__
#define __OpcUaStackCore_ConfigXml_h__

#include "OpcUaStackCore/Base/os.h"
#include <string>

namespace OpcUaStackCore
{

	class DLLEXPORT ConfigXml
	{
	  public:
		ConfigXml(void);
		~ConfigXml(void);

		bool parse(const std::string& configFileName, bool writeToConfig = false);
		std::string errorMessage(void);
		boost::property_tree::ptree& ptree(void);
		void writeToConfig(void);

	  private:
		std::string configFileName_;
		boost::property_tree::ptree ptree_;
		std::string errorMessage_;
	};

}

#endif