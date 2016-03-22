#include "unittest.h"
#include <boost/asio/ip/host_name.hpp>
#include "OpcUaStackCore/Certificate/PkiCertificate.h"
#include "OpcUaStackCore/Certificate/PkiRsaKey.h"

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(PkiCertificate_t)

BOOST_AUTO_TEST_CASE(PkiCertificate_)
{
	std::cout << "PkiCertificate_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(PkiCertificate_create)
{
	std::string hostname = boost::asio::ip::host_name();

	PkiIdentity identity;
	identity.commonName()		= "ASNeG-Demo@" + hostname;
	identity.organization()		= "ASNeG";
	identity.organizationUnit()	= "Unit";
	identity.locality()			= "LocationName";
	identity.state()			= "State";
	identity.country()			= "DE";
	identity.domainComponent()	= hostname;

	PkiCertificateInfo info;
	info.URI()					= "urn:" + hostname + ":ASNeG::ASNeG-Demo";
	info.dnsNames().push_back(hostname);
	info.validTime(3600*24*365*5);

	PkiRsaKey rsaKey;
	BOOST_REQUIRE(rsaKey.createKey(1024) == true);

	PkiPrivateKey issuerPrivateKey;
	BOOST_REQUIRE(rsaKey.getPrivateKey(issuerPrivateKey) == true);

	PkiPublicKey subjectPublicKey;
	BOOST_REQUIRE(rsaKey.getPublicKey(subjectPublicKey) == true);

	PkiCertificate certificate;
	BOOST_REQUIRE(certificate.createNewCertificate(info, identity, subjectPublicKey, identity, issuerPrivateKey) == true);
}

BOOST_AUTO_TEST_CASE(PkiCertificate_write_key)
{
	std::string hostname = boost::asio::ip::host_name();

	PkiIdentity identity;
	identity.commonName()		= "ASNeG-Demo@" + hostname;
	identity.organization()		= "ASNeG";
	identity.organizationUnit()	= "Unit";
	identity.locality()			= "LocationName";
	identity.state()			= "State";
	identity.country()			= "DE";
	identity.domainComponent()	= hostname;

	PkiCertificateInfo info;
	info.URI()					= "urn:" + hostname + ":ASNeG::ASNeG-Demo";
	info.dnsNames().push_back(hostname);
	info.validTime(3600*24*365*5);

	PkiRsaKey rsaKey;
	BOOST_REQUIRE(rsaKey.createKey(1024) == true);

	PkiPrivateKey issuerPrivateKey;
	BOOST_REQUIRE(rsaKey.getPrivateKey(issuerPrivateKey) == true);

	PkiPublicKey subjectPublicKey;
	BOOST_REQUIRE(rsaKey.getPublicKey(subjectPublicKey) == true);

	PkiCertificate certificate;
	BOOST_REQUIRE(
		certificate.createNewCertificate(
			info, identity, subjectPublicKey, identity, issuerPrivateKey
		) == true);

	//
	// store certificate
	//
	BOOST_REQUIRE(certificate.toDERFile("../tst/data/ASNeG-Test.der") == true);

	//
	// store private key
	//
	BOOST_REQUIRE(rsaKey.writePEMFile("../tst/data/ASNeG-Test.PEM", "") == true);
}

BOOST_AUTO_TEST_CASE(PkiCertificate_write_read_key)
{
	std::string hostname = boost::asio::ip::host_name();

	{ // write certificate to file

		PkiIdentity identity;
		identity.commonName()		= "ASNeG-Demo@" + hostname;
		identity.organization()		= "ASNeG";
		identity.organizationUnit()	= "Unit";
		identity.locality()			= "LocationName";
		identity.state()			= "State";
		identity.country()			= "DE";
		identity.domainComponent()	= hostname;

		PkiCertificateInfo info;
		info.URI()					= "urn:" + hostname + ":ASNeG::ASNeG-Demo";
		info.dnsNames().push_back(hostname);
		info.validTime(3600*24*365*5);

		PkiRsaKey rsaKey;
		BOOST_REQUIRE(rsaKey.createKey(1024) == true);

		PkiPrivateKey issuerPrivateKey;
		BOOST_REQUIRE(rsaKey.getPrivateKey(issuerPrivateKey) == true);

		PkiPublicKey subjectPublicKey;
		BOOST_REQUIRE(rsaKey.getPublicKey(subjectPublicKey) == true);

		PkiCertificate certificate;
		BOOST_REQUIRE(
			certificate.createNewCertificate(
				info, identity, subjectPublicKey, identity, issuerPrivateKey
			) == true
		);

		//
		// store certificate
		//
		BOOST_REQUIRE(certificate.toDERFile("../tst/data/ASNeG-Test.der") == true);

		//
		// store private key
		//
		BOOST_REQUIRE(rsaKey.writePEMFile("../tst/data/ASNeG-Test.PEM", "") == true);
	}

	{ // read certificate from file
		PkiCertificate certificate;

		PkiCertificateInfo pkiCertificateInfo;
		PkiIdentity subjectPkiIdentity;
		PkiPublicKey subjectPkiPublicKey;
		PkiIdentity issuerPkiIdentity;
		PkiPrivateKey issuerPrivateKey;

		BOOST_REQUIRE(certificate.fromDERFile("../tst/data/ASNeG-Test.der") == true);
		BOOST_REQUIRE(
			certificate.getCertificate(
				pkiCertificateInfo,
				subjectPkiIdentity,
				subjectPkiPublicKey,
				issuerPkiIdentity,
				issuerPrivateKey
			) == true
		);

		BOOST_REQUIRE(subjectPkiIdentity.commonName()	== "ASNeG-Demo@" + hostname);
		BOOST_REQUIRE(subjectPkiIdentity.organization() == "ASNeG");
		BOOST_REQUIRE(subjectPkiIdentity.organizationUnit() == "Unit");
		BOOST_REQUIRE(subjectPkiIdentity.locality() == "LocationName");
		BOOST_REQUIRE(subjectPkiIdentity.state() == "State");
		BOOST_REQUIRE(subjectPkiIdentity.country() == "DE");
		BOOST_REQUIRE(subjectPkiIdentity.domainComponent() == hostname);

		BOOST_REQUIRE(issuerPkiIdentity.commonName()	== "ASNeG-Demo@" + hostname);
		BOOST_REQUIRE(issuerPkiIdentity.organization() == "ASNeG");
		BOOST_REQUIRE(issuerPkiIdentity.organizationUnit() == "Unit");
		BOOST_REQUIRE(issuerPkiIdentity.locality() == "LocationName");
		BOOST_REQUIRE(issuerPkiIdentity.state() == "State");
		BOOST_REQUIRE(issuerPkiIdentity.country() == "DE");
		BOOST_REQUIRE(issuerPkiIdentity.domainComponent() == hostname);

	}
}

BOOST_AUTO_TEST_SUITE_END()


