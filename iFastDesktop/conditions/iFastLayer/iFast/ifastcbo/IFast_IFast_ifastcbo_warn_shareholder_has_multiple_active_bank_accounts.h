#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_shareholder_has_multiple_active_bank_accounts : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_shareholder_has_multiple_active_bank_accounts() { }
		~CIFast_IFast_ifastcbo_warn_shareholder_has_multiple_active_bank_accounts() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SHAREHOLDER_HAS_MULTIPLE_ACTIVE_BANK_ACCOUNTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder has multiple active bank accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Shareholder has multiple active bank accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'actionnaire a plusieurs comptes bancaires actifs.")); }

        // Actions
	};
}



