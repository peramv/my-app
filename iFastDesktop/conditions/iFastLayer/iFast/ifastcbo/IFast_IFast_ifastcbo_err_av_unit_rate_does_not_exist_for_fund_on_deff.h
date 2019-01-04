#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_av_unit_rate_does_not_exist_for_fund_on_deff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_av_unit_rate_does_not_exist_for_fund_on_deff() { }
		~CIFast_IFast_ifastcbo_err_av_unit_rate_does_not_exist_for_fund_on_deff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AV_UNIT_RATE_DOES_NOT_EXIST_FOR_FUND_ON_DEFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AV unit rate does not exist for %FUNDFROM% on %DEFF%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("AV unit rate does not exist for %FUNDFROM% on %DEFF%.")); }

        // Actions
	};
}



