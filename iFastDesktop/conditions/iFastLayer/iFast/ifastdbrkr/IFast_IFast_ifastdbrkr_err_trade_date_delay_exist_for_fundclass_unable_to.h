#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_date_delay_exist_for_fundclass_unable_to : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_date_delay_exist_for_fundclass_unable_to() { }
		~CIFast_IFast_ifastdbrkr_err_trade_date_delay_exist_for_fundclass_unable_to() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_DELAY_EXIST_FOR_FUNDCLASS_UNABLE_TO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade Date delay exists for FundTo and ClassTo. Unable to find the Trade Date for the selected Valuation Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trade Date delay exists for FundTo and ClassTo. Unable to find the Trade Date for the selected Valuation Date.")); }

        // Actions
	};
}



