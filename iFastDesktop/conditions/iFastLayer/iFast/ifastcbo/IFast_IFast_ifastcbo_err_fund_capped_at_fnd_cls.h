#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_capped_at_fnd_cls : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_capped_at_fnd_cls() { }
		~CIFast_IFast_ifastcbo_err_fund_capped_at_fnd_cls() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CAPPED_AT_FND_CLS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUND%/%CLASS% is soft capped at the fund class level as of %ASOF%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FUND%/%CLASS% est faiblement plafonné(e) au niveau du fonds et de la classe à partir du %ASOF%.")); }

        // Actions
	};
}



