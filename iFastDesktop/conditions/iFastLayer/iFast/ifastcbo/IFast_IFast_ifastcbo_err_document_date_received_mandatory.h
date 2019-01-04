#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_document_date_received_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_document_date_received_mandatory() { }
		~CIFast_IFast_ifastcbo_err_document_date_received_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DOCUMENT_DATE_RECEIVED_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date Received is mandatory when status is Received.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il faut indiquer la date reçue lorsque l'état est reçu.")); }

        // Actions
	};
}



