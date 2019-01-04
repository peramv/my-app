#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_domestic_fund_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_domestic_fund_only() { }
		~CIFast_IFast_ifastcbo_err_domestic_fund_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DOMESTIC_FUND_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Foreign Rebalance Fund must be a domestic fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Foreign Rebalance Fund must be a domestic fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Foreign Rebalance Fund must be a domestic fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds de rebalancement étranger doit être un fonds national.")); }

        // Actions
	};
}



