#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_as_pension_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_as_pension_acct() { }
		~CIFast_IFast_ifastcbo_err_warn_as_pension_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_AS_PENSION_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is an AS Pension Plan account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dies ist ein AS-Rentenplan-Konto")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ésta es una cuenta de plan de jubilación AS")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ceci est un compte En tant que régime de retraite.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit is een AS-pensioenplanaccount")); }

        // Actions
	};
}



