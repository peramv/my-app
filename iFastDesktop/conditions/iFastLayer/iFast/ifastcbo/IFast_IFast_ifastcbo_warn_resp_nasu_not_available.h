#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_nasu_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_nasu_not_available() { }
		~CIFast_IFast_ifastcbo_warn_resp_nasu_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_NASU_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP NASU not available on desktop")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage d'un nouveau compte REEE n'est pas disponible sur le bureau.")); }

        // Actions
	};
}



