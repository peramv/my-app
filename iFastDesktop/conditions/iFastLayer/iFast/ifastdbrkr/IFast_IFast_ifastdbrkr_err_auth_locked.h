#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_auth_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_auth_locked() { }
		~CIFast_IFast_ifastdbrkr_err_auth_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AUTH_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User account is locked.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte de l'utilisateur est verrouillé.")); }

        // Actions
	};
}



