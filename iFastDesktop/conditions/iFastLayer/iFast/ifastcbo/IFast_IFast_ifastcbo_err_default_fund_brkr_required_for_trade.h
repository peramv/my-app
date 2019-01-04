#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_default_fund_brkr_required_for_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_default_fund_brkr_required_for_trade() { }
		~CIFast_IFast_ifastcbo_err_default_fund_brkr_required_for_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEFAULT_FUND_BRKR_REQUIRED_FOR_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("External Fund Broker not configured for this Client Account and Target-Fund")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier externe non configuré pour ce compte client et ce fonds cible.")); }

        // Actions
	};
}



