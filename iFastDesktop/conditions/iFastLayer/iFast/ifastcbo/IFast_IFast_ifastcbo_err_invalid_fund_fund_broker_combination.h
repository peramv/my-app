#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fund_fund_broker_combination : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fund_fund_broker_combination() { }
		~CIFast_IFast_ifastcbo_err_invalid_fund_fund_broker_combination() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_FUND_BROKER_COMBINATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Fund and Fund Broker combination.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid Fund and Fund Broker combination.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Combinaison de fonds et de courtier en fonds invalide")); }

        // Actions
	};
}



