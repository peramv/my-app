#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_auth_token_exp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_auth_token_exp() { }
		~CIFast_IFast_ifastdbrkr_err_auth_token_exp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AUTH_TOKEN_EXP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Authentication token has expired.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le jeton d'authentification a expiré.")); }

        // Actions
	};
}



