#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_auth_max_logons : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_auth_max_logons() { }
		~CIFast_IFast_ifastdbrkr_err_auth_max_logons() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AUTH_MAX_LOGONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User logon maximum reached.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le maximum d'ouverture de session par l'utilisateur a été atteint.")); }

        // Actions
	};
}



