#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_resp_trinfo_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_resp_trinfo_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_resp_trinfo_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_TRINFO_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESPTrfInfo is not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le transfert REEE n'est pas disponible.")); }

        // Actions
	};
}



