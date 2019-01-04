#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_share_holder_hold_multiple_accounts : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_share_holder_hold_multiple_accounts() { }
		~CIFast_IFast_ifastcbo_err_share_holder_hold_multiple_accounts() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHARE_HOLDER_HOLD_MULTIPLE_ACCOUNTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to setup Investor Authorization rule due to shareholder hold multiple accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de régler la règle d'autorisation de l'investisseur parce que l'actionnaire détient plusieurs comptes.")); }

        // Actions
	};
}



