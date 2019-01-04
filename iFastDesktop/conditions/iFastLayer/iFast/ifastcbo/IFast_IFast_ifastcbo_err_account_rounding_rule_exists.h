#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_rounding_rule_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_rounding_rule_exists() { }
		~CIFast_IFast_ifastcbo_err_account_rounding_rule_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_ROUNDING_RULE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Rounding Rules record already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Account Rounding Rules record already exists.")); }		

        // Actions
	};
}



