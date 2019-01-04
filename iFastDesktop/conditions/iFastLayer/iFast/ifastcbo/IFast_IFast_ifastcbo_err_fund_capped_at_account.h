#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_capped_at_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_capped_at_account() { }
		~CIFast_IFast_ifastcbo_err_fund_capped_at_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CAPPED_AT_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUND%/%CLASS% soft capped at account level as of %ASOF%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FUND%/%CLASS% est faiblement plafonné(e) au niveau du compte à partir du %ASOF%.")); }

        // Actions
	};
}



