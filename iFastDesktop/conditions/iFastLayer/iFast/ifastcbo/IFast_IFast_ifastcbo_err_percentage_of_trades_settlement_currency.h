#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_percentage_of_trades_settlement_currency_breached : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_percentage_of_trades_settlement_currency_breached() { }
		~CIFast_IFast_ifastcbo_err_percentage_of_trades_settlement_currency_breached() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("% of Trades in Settlement Currency is breached.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le % des transactions dans la devise de paiement est dépassé.")); }

        // Actions
	};
}



