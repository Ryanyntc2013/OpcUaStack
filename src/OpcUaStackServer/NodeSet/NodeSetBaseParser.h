#ifndef __OpcUaStackServer_NodeSetBaseParser_h__
#define __OpcUaStackServer_NodeSetBaseParser_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/MethodNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/ObjectNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/ObjectTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/ReferenceTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/VariableNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/VariableTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/ViewNodeClass.h"
#include <vector>

namespace OpcUaStackServer
{

	typedef std::vector<DataTypeNodeClass::SPtr> DataTypeNodeClassVec;
	typedef std::vector<MethodNodeClass::SPtr> MethodNodeClassVec;
	typedef std::vector<ObjectNodeClass::SPtr> ObjectNodeClassVec;
	typedef std::vector<ObjectTypeNodeClass::SPtr> ObjectTypeNodeClassVec;
	typedef std::vector<ReferenceTypeNodeClass::SPtr> ReferenceTypeNodeClassVec;
	typedef std::vector<VariableNodeClass::SPtr> VariableNodeClassVec;
	typedef std::vector<VariableTypeNodeClass::SPtr> VariableTypeNodeClassVec;
	typedef std::vector<ViewNodeClass::SPtr> ViewNodeClassVec;

	class DLLEXPORT NodeSetBaseParser
	{
	  public:
		NodeSetBaseParser(void);
		~NodeSetBaseParser(void);

		void clear();

		DataTypeNodeClassVec& dataTypeNodeClassVec(void);
		MethodNodeClassVec& methodNodeClassVec(void);
		ObjectNodeClassVec& objectNodeClassVec(void);
		ObjectTypeNodeClassVec& objectTypeNodeClassVec(void);
		ReferenceTypeNodeClassVec& referenceTypeNodeClassVec(void);
		VariableNodeClassVec& variableNodeClassVec(void);
		VariableTypeNodeClassVec& variableTypeNodeClassVec(void);
		ViewNodeClassVec& viewNodeClassVec(void);

		void dataTypeNodeClassVec(DataTypeNodeClassVec& dataTypeNodeClassVec);
		void methodNodeClassVec(MethodNodeClassVec& methodNodeClassVec);
		void objectNodeClassVec(ObjectNodeClassVec& objectNodeClassVec);
		void objectTypeNodeClassVec(ObjectTypeNodeClassVec& objectTypeNodeClassVec);
		void referenceTypeNodeClassVec(ReferenceTypeNodeClassVec& referenceTypeNodeClassVec);
		void variableNodeClassVec(VariableNodeClassVec& variableNodeClassVec);
		void variableTypeNodeClassVec(VariableTypeNodeClassVec& variableTypeNodeClassVec);
		void viewNodeClassVec(ViewNodeClassVec& viewNodeClassVec);

	  private:
		DataTypeNodeClassVec dataTypeNodeClassVec_;
		MethodNodeClassVec methodNodeClassVec_;
		ObjectNodeClassVec objectNodeClassVec_;
		ObjectTypeNodeClassVec objectTypeNodeClassVec_;
		ReferenceTypeNodeClassVec referenceTypeNodeClassVec_;
		VariableNodeClassVec variableNodeClassVec_;
		VariableTypeNodeClassVec variableTypeNodeClassVec_;
		ViewNodeClassVec viewNodeClassVec_;
	};

}

#endif