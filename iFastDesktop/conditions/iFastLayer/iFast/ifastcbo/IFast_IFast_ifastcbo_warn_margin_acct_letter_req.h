#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_margin_acct_letter_req : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_margin_acct_letter_req() { }
		~CIFast_IFast_ifastcbo_warn_margin_acct_letter_req() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MARGIN_ACCT_LETTER_REQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Margin account. A release letter is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Margin account. A release letter is required.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Margin account. A release letter is required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte sur marge. Une lettre d'autorisation est requise.")); }

        // Actions
	};
}



