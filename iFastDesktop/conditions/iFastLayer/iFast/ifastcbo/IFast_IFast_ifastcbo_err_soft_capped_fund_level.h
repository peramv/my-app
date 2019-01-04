#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_soft_capped_fund_level : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_soft_capped_fund_level() { }
		~CIFast_IFast_ifastcbo_err_soft_capped_fund_level() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SOFT_CAPPED_FUND_LEVEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUND%/%CLASS% is soft capped at the fund level as of %ASOF%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FUND%/%CLASS% is soft capped at the fund level as of %ASOF%.")); }

        // Actions
	};
}