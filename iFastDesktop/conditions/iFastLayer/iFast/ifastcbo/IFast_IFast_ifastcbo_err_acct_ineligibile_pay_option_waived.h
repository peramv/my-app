#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_ineligibile_pay_option_waived : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_ineligibile_pay_option_waived() { }
		~CIFast_IFast_ifastcbo_err_acct_ineligibile_pay_option_waived() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_INELIGIBILE_PAY_OPTION_WAIVED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is ineligible for Pay Option Waived.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account is ineligible for Pay Option Waived.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account is ineligible for Pay Option Waived.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas admissible pour l'option de paiement exonéré.")); }

        // Actions
	};
}



