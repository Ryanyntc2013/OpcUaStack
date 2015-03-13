#include "OpcUaStackClient/SecureChannel/SecureChannelTransaction.h"

namespace OpcUaStackClient
{

	SecureChannelTransaction::SecureChannelTransaction(void)
	: is_()
	, os_()
	{
	}

	SecureChannelTransaction::~SecureChannelTransaction(void)
	{
	}

	void
	SecureChannelTransaction::isAppend(boost::asio::streambuf& sb)
	{
		std::iostream ios(&is_);
		boost::asio::const_buffer buffer(sb.data());
		std::size_t bufferSize = boost::asio::buffer_size(buffer);
		const char* bufferPtr = boost::asio::buffer_cast<const char*>(buffer);
		ios.write(bufferPtr,bufferSize);
		sb.consume(bufferSize);
	}

	void
	SecureChannelTransaction::osAppend(boost::asio::streambuf& sb)
	{
		std::iostream ios(&os_);
		boost::asio::const_buffer buffer(sb.data());
		std::size_t bufferSize = boost::asio::buffer_size(buffer);
		const char* bufferPtr = boost::asio::buffer_cast<const char*>(buffer);
		ios.write(bufferPtr,bufferSize);
		sb.consume(bufferSize);
	}

}