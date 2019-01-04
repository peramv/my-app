#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mail_consent_cannt_both_yes_or_no : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mail_consent_cannt_both_yes_or_no() { }
		~CIFast_IFast_ifastcbo_err_mail_consent_cannt_both_yes_or_no() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAIL_CONSENT_CANNT_BOTH_YES_OR_NO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail and Consent can not be both yes or no for %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mail and Consent can not be both yes or no for %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Courrier et Consentement ne peut être tous deux réglés à Oui ou Non pour %DOCTYPE%.")); }

        // Actions
	};
}



