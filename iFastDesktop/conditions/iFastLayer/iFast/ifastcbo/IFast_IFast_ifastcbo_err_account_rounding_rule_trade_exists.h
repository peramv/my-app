#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_rounding_rule_trade_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_rounding_rule_trade_exists() { }
		~CIFast_IFast_ifastcbo_err_account_rounding_rule_trade_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending or processed trade exists, account rounding rule cannot be added/modified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Existence d’une transaction en attente ou traitée.")); }		

        // Actions
	};
}



