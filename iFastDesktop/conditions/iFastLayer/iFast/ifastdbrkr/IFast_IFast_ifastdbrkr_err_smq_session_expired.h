#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_smq_session_expired : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_smq_session_expired() { }
		~CIFast_IFast_ifastdbrkr_err_smq_session_expired() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SMQ_SESSION_EXPIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Your session has expired.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Votre session a expiré.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please logon again.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez rouvrir une session.")); }
	};
}



