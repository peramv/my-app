#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_auth_chpwd_reqd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_auth_chpwd_reqd() { }
		~CIFast_IFast_ifastdbrkr_err_auth_chpwd_reqd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AUTH_CHPWD_REQD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password change required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mot de passe doit être changé.")); }

        // Actions
	};
}



