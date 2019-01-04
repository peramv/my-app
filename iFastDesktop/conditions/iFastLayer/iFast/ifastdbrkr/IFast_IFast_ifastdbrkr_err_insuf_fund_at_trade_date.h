#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_insuf_fund_at_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_insuf_fund_at_trade_date() { }
		~CIFast_IFast_ifastdbrkr_err_insuf_fund_at_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSUF_FUND_AT_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient Funds As At Trade Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unzureichendes Fonds Wie-zu-Handelsdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fondos insuficientes a la fecha de transacción")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds insuffisants en date de la transaction")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onvoldoende fondsen op handelsdatum")); }

        // Actions
	};
}



