#ifndef __OpcUaStackServer_Server_h__
#define __OpcUaStackServer_Server_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/IOService.h"
#include "OpcUaStackCore/Core/Core.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"
#include "OpcUaStackServer/ServiceSet/SessionManager.h"
#include "OpcUaStackServer/ServiceManager/ServiceManager.h"

namespace OpcUaStackServer
{

	class DLLEXPORT Server : public OpcUaStackCore::Core
	{
	  public:
	    Server(void);
	    ~Server(void);

		bool init(void);
		void cleanup(void);
		bool start(void);
		void stop(void);

	  private:
		bool initInformationModel(void);
		bool setInformationModel(void);
		bool initService(void);
		bool initSession(void);

		IOService ioService_;
		InformationModel::SPtr informationModel_;
		SessionManager sessionManager_;
		ServiceManager serviceManager_;
	};

}

#endif