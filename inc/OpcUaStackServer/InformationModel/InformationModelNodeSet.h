#ifndef __OpcUaStackServer_InformationModelNodeSet_h__
#define __OpcUaStackServer_InformationModelNodeSet_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackServer/NodeSet/NodeSetBaseParser.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"

namespace OpcUaStackServer
{

	class DLLEXPORT InformationModelNodeSet
	{
	  public:
		InformationModelNodeSet(void);
		~InformationModelNodeSet(void);

		static bool initial(InformationModel::SPtr informationModelSPtr, NodeSetBaseParser& nodeSetBaseParser);
	};

}

#endif