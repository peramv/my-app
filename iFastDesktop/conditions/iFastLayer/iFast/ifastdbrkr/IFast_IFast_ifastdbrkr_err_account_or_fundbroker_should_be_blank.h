#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_or_fundbroker_should_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_or_fundbroker_should_be_blank() { }
		~CIFast_IFast_ifastdbrkr_err_account_or_fundbroker_should_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_OR_FUNDBROKER_SHOULD_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account or Fund Broker Code should be blank")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account or Fund Broker Code should be blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du compte ou du code de courtier en fonds doit être vide.")); }

        // Actions
	};
}



