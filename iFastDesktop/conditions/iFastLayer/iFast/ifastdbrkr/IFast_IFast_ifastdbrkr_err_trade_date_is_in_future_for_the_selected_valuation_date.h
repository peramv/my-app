#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_date_is_in_future_for_the_selected_valuation_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_date_is_in_future_for_the_selected_valuation_date() { }
		~CIFast_IFast_ifastdbrkr_err_trade_date_is_in_future_for_the_selected_valuation_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_IS_IN_FUTURE_FOR_THE_SELECTED_VALUATION_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade Date is in future for the selected Valuation Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trade Date is in future for the selected Valuation Date.")); }

        // Actions
	};
}



