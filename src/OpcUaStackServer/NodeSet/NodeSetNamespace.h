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

#ifndef __OpcUaStackServer_NodeSetNamespace_h__
#define __OpcUaStackServer_NodeSetNamespace_h__

#include <boost/property_tree/ptree.hpp>
#include "OpcUaStackCore/Base/os.h"
#include <map>
#include <vector>
#include <stdint.h>

namespace OpcUaStackServer
{

	typedef std::vector<std::string> NamespaceVec;
	typedef std::vector<uint16_t> NamespaceIndexVec;
	typedef std::map<uint16_t,uint16_t> NamespaceIndexMap;
	typedef std::map<std::string, uint16_t> NamespaceMap;

	class DLLEXPORT NodeSetNamespace
	{
	  public:
		NodeSetNamespace(void);
		~NodeSetNamespace(void);
		void clear(void);
		void clearGlobal(void);

		void decodeNamespaceUris(boost::property_tree::ptree& ptree);
		void decodeNamespaceUris(std::vector<std::string>& namespaceUriVec);
		void encodeNamespaceUris(boost::property_tree::ptree& ptree);
		uint32_t addNewGlobalNamespace(const std::string& namespaceUri);
	
		NamespaceVec& localNamespaceVec(void);
		NamespaceVec& globalNamespaceVec(void);
		uint16_t mapToLocalNamespaceIndex(uint16_t globalNamespaceIndex);
		uint16_t mapToGlobalNamespaceIndex(const std::string& namespaceUri);
		uint16_t mapToGlobalNamespaceIndex(uint16_t localNamespaceIndex);

	  private:
		static bool startup_;
		static void startup(void);
		static uint16_t addGlobalNamespace(const std::string& namespaceUri);
		static std::string getGlobalNamespaceUri(uint16_t globalNamespaceIndex);

		// list off all existing global namespace uris
		static NamespaceVec globalNamespaceVec_;
		// map from global namespace name to global namespace index
		static NamespaceMap globalNamespaceMap_;
		
		//
		// common
		//
		// namespace names in nodeset file
		NamespaceVec localNamespaceVec_;

		// 
		// read nodeset files
		//

		// mapping vector
		// The position defines the input namespace index in the nodeset file
		// The value defines the global namespace index in the information model
		NamespaceIndexVec inputNamespaceIndexVec_;


		//
		// write nodeset files
		//
		// maps the global namespace index to the namespace index in the nodeset file 
		NamespaceIndexMap outputNamespaceIndexMap_;
	};

}

#endif
