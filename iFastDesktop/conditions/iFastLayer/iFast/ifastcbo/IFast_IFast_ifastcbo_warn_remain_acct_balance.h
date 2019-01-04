#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_remain_acct_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_remain_acct_balance() { }
		~CIFast_IFast_ifastcbo_warn_remain_acct_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REMAIN_ACCT_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Remaining account balance is insufficient to cover the remaining balance.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Remaining account balance is insufficient to cover the remaining balance.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Remaining account balance is insufficient to cover the remaining balance.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde restant au compte est insuffisant pour couvrir le solde restant.")); }

        // Actions
	};
}



