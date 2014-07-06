#include "OpcUaStackCore/Base/Utility.h"
#include <sstream>
#include <iomanip>
#include <assert.h>

namespace OpcUaStackCore
{

	char byteToHex(uint8_t c)
	{
		assert(c < 16);

		if (c < 10) return c + '0';
		else return c - 10 + 'A';
	}

	uint8_t hexToByte(char c)
	{
		assert((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
		
		if (c >= '0' && c <= '9') {
			return c - '0';
		}
		else if (c >= 'a' && c <= 'f'){
			return c - 'a' + 10;
		}
		else {
			return c - 'A' + 10;
		}
	}

	void duplicate(std::iostream& ios1, std::iostream& ios2)
	{
		std::stringstream ss1;
		std::stringstream ss2;

		char c;
		while (ios1.get(c)) {
			ss1 << c;
			ss2 << c;
		}

		ios1.clear();
		ios2.clear();
		ios1 << ss1.rdbuf();
		ios2 << ss2.rdbuf();
	}

	uint32_t count(std::iostream& ios)
	{
		std::stringstream ss;
		duplicate(ios, ss);

		char c;
		uint32_t count = 0;
		while (ss.get(c)) {
			count++;
		}

		return count;
	}

	uint32_t count(boost::asio::streambuf& sb)
	{
		uint32_t size = 0;
		boost::asio::streambuf::const_buffers_type data = sb.data();
		boost::asio::streambuf::const_buffers_type::const_iterator it;
		for (it=data.begin(); it!=data.end(); it++) {
			size += boost::asio::buffer_size(*it);
		}
		return size;
	}

	void dumpHex(std::streambuf& sb, std::ostream& os)
	{
		std::iostream ios(&sb);
		dumpHex(ios, os);
	}


	void dumpHex(std::iostream& ios, std::ostream& os)
	{
		std::stringstream ss;
		duplicate(ios, ss);
		unsigned int long address = 0;

		os << std::hex << std::setfill('0');
		while (ios.good()) {
	        int nread;
		    char buf[16];

		    for( nread = 0; nread < 16 && ss.get(buf[nread]); nread++ );
            if( nread == 0 ) break;

			os << std::setw(8) << address;

			for (int i=0; i<16; i++) {
				if (i % 8 == 0) os << ' ';
				if (i < nread) {
					os << ' ' << std::setw(2) << (unsigned)(buf[i] & 0xFF);
				}
				else {
					os << "   ";
				}
			}

			os << "  ";
			for (int i=0; i<nread; i++) {
				if (buf[i] < 32) os << ".";
				else os << buf[i];
			}

			os << std::endl;
			address += 16;
		}
	}

	void dumpHex(const char* bufDat, const uint32_t bufLen, std::ostream& os)
	{
		unsigned int long address = 0;

		os << std::hex << std::setfill('0');
		while (address < bufLen) {
	        int nread;

			const char* buf = &bufDat[address];
			if (address + 16 <= bufLen) {
				nread = 16;
			}
			else {
				nread = bufLen - address;
			}

			os << std::setw(8) << address;

			for (int i=0; i<16; i++) {
				if (i % 8 == 0) os << ' ';
				if (i < nread) {
					os << ' ' << std::setw(2) << (buf[i] & 0xFF);
				}
				else {
					os << "   ";
				}
			}

			os << "  ";
			for (int i=0; i<nread; i++) {
				if (buf[i] < 32) os << ".";
				else os << buf[i];
			}

			os << std::endl;
			address += 16;
		}
	}

	void hexStringToByteSequence(const std::string& hexString, uint8_t* byteSequence)
	{
		uint32_t pos = 0;
		uint32_t hexStringLength = hexString.length();

		for (uint32_t idx=0; idx<hexStringLength; idx+=2) {
			uint8_t n1 = hexToByte(hexString[idx]);
			uint8_t n2 = 0;
			if (idx + 1 < hexStringLength) {
				n2 = hexToByte(hexString[idx+1]);
			}

			byteSequence[pos] = (n1<<4)+n2;
			pos++;
		}
	}

	void byteSequenceToHexString(const uint8_t* byteSequence, uint32_t byteSequenceLength, std::string& hexString)
	{
		hexString = "";
		for (uint32_t idx=0; idx<byteSequenceLength; idx++) {
			char c[2];
			c[0] = byteToHex((byteSequence[idx] & 0xFF) >> 4);
			c[1] = byteToHex(byteSequence[idx] & 0x0F);
			hexString.append(1, c[0]).append(1, c[1]);
		}
	}

}