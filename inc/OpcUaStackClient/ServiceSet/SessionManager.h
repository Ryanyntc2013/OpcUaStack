#ifndef __OpcUaStackClient_SessionManager_h__
#define __OpcUaStackClient_SessionManager_h__

#include <boost/thread/mutex.hpp>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackClient/SecureChannel/SecureChannelClientConfig.h"
#include "OPcUaStackClient/ServiceSet/SessionConfig.h"

namespace OpcUaStackClient
{

	class DLLEXPORT SessionManager : public SessionSecureChannelIf, public SecureChannelIf
	{
	  public:
		static SessionManager* instance_;
		static SessionManager* instance(void);

		SessionManager(void);
		~SessionManager(void);

		void start(void);
		void stop(void);

		Session::SPtr getNewSession(
			const std::string& prefixSessionConfig, Config& sessionConfig, 
			const std::string& prefixSecureChannelConfig, Config& secureChannelConfig, 
			SessionIf* sessionIf,
			bool newSecureChannel = false
		);
		void deleteSession(void);

		//- SessionSecureChannelIf --------------------------------------------
		void connectToSecureChannel(void); 
	    void createSessionRequest(boost::asio::streambuf& sb);
		void activateSessionRequest(boost::asio::streambuf& sb);
		//- SessionSecurechannelIf --------------------------------------------

		//- SecureChannelIf ---------------------------------------------------
		void connect(void);
		void disconnect(void);
		void receive(OpcUaNodeId& nodeId, boost::asio::streambuf& is);
		//- SecureChannelIf ---------------------------------------------------

	  private:
		IOService ioService_;

		SecureChannelClient::SPtr secureChannel_;
		Session::SPtr session_;
	};

}

#endif