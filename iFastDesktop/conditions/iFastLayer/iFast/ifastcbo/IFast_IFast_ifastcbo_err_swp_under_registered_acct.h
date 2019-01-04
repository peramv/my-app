#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_swp_under_registered_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_swp_under_registered_acct() { }
		~CIFast_IFast_ifastcbo_err_swp_under_registered_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SWP_UNDER_REGISTERED_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SWP is under a registered account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SWP ist unter einem Auslandskonto!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("¡S.W.P está bajo una cuenta registrada!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le PRP est dans un compte enregistré.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("S.W.P. bevindt zich onder een geregistreerd account!")); }

        // Actions
	};
}



