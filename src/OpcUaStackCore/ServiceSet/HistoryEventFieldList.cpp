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

#include "OpcUaStackCore/ServiceSet/HistoryEventFieldList.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa HistoryEventFieldList
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	HistoryEventFieldList::HistoryEventFieldList(void)
	: ObjectPool<HistoryEventFieldList>()
	, eventFieldArraySPtr_(constructSPtr<OpcUaVariantArray>())
	{
	}

	HistoryEventFieldList::~HistoryEventFieldList(void)
	{
	}

	void 
	HistoryEventFieldList::eventFields(const OpcUaVariantArray::SPtr eventFields)
	{
		eventFieldArraySPtr_ = eventFields;
	}
	
	OpcUaVariantArray::SPtr 
	HistoryEventFieldList::eventFields(void) const
	{
		return eventFieldArraySPtr_;
	}

	void 
	HistoryEventFieldList::opcUaBinaryEncode(std::ostream& os) const
	{
		eventFieldArraySPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	HistoryEventFieldList::opcUaBinaryDecode(std::istream& is)
	{
		eventFieldArraySPtr_->opcUaBinaryDecode(is);
	}
}
