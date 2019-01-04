#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_date_outside_min_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_date_outside_min_max() { }
		~CIFast_IFast_ifastcbo_err_trade_date_outside_min_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_OUTSIDE_MIN_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade Date must be between %START% and %END%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction doit être située entre le %START% et le %END%.")); }

        // Actions
	};
}



