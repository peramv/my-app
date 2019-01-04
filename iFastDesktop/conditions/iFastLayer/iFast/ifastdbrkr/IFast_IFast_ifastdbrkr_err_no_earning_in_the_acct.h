#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_earning_in_the_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_earning_in_the_acct() { }
		~CIFast_IFast_ifastdbrkr_err_no_earning_in_the_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_EARNING_IN_THE_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No earnings in the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Erträge auf dem Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay ganancias en la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun revenu au compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen inkomsten in dit account")); }

        // Actions
	};
}



