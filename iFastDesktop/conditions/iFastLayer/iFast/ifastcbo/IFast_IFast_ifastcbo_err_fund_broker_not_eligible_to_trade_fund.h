#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_broker_not_eligible_to_trade_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_broker_not_eligible_to_trade_fund() { }
		~CIFast_IFast_ifastcbo_err_fund_broker_not_eligible_to_trade_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_BROKER_NOT_ELIGIBLE_TO_TRADE_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund broker is not eligible to trade fund %fund%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund broker is not eligible to trade fund %fund%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier en fonds n'est pas admissible au traitement du fonds %fund%.")); }

        // Actions
	};
}



