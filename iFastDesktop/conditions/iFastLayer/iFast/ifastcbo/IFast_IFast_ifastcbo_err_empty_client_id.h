#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_empty_client_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_empty_client_id() { }
		~CIFast_IFast_ifastcbo_err_empty_client_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EMPTY_CLIENT_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to retrieve Client Identification.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kunden-Identifizierung nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible recuperar la identificación del cliente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de récupérer l'identification du client.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Klantidentificatie kon niet worden opgehaald")); }

        // Actions
	};
}



