#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_direct_deposit_bank_investor_authorize_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_direct_deposit_bank_investor_authorize_missing() { }
		~CIFast_IFast_ifastcbo_warn_direct_deposit_bank_investor_authorize_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not find %MISSING% on %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver %MISSING% le %DATE%.")); }

        // Actions
	};
}



