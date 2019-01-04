#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_cannot_backdate_trade_before_money_out_trans : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_cannot_backdate_trade_before_money_out_trans() { }
		~CIFast_IFast_ifastcbo_err_rdsp_cannot_backdate_trade_before_money_out_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot backdate the trade before the Money-out transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cannot backdate the trade before the Money-out transaction.")); }

        // Actions
	};
}



