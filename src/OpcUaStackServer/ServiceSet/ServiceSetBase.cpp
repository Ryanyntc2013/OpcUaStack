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

#include "OpcUaStackServer/ServiceSet/ServiceSetBase.h"

namespace OpcUaStackServer
{

	ServiceSetBase::ServiceSetBase(void)
	: Component()
	, informationModel_()
	, namespaceArray_(NamespaceArray::construct())
	, serverArray_(ServerArray::construct())
	{
	}

	ServiceSetBase::~ServiceSetBase(void)
	{
	}

	void 
	ServiceSetBase::informationModel(InformationModel::SPtr informationModel)
	{
		informationModel_ = informationModel;
		namespaceArray_->informationModel(informationModel);
		serverArray_->informationModel(informationModel);
	}

	InformationModel::SPtr 
	ServiceSetBase::informationModel(void)
	{
		return informationModel_;
	}

	NamespaceArray::SPtr 
	ServiceSetBase::namespaceArray(void)
	{
		return namespaceArray_;
	}

	ServerArray::SPtr
	ServiceSetBase::serverArray(void)
	{
		return serverArray_;
	}

}
