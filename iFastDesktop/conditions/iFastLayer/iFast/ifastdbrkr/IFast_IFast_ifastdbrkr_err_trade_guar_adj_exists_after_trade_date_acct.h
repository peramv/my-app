#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_guar_adj_exists_after_trade_date_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_guar_adj_exists_after_trade_date_acct() { }
		~CIFast_IFast_ifastdbrkr_err_trade_guar_adj_exists_after_trade_date_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee Adjustment exists after trade date for the Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Guarantee Adjustment exists after trade date for the Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un ajustement de garantie existe après la date de transaction pour le compte.")); }

        // Actions
	};
}



