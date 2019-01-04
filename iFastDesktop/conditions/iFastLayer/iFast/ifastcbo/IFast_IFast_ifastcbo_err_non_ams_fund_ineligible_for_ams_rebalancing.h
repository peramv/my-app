#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_non_ams_fund_ineligible_for_ams_rebalancing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_non_ams_fund_ineligible_for_ams_rebalancing() { }
		~CIFast_IFast_ifastcbo_err_non_ams_fund_ineligible_for_ams_rebalancing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_AMS_FUND_INELIGIBLE_FOR_AMS_REBALANCING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund ineligible for AMS rebalancing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund ineligible for AMS rebalancing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund ineligible for AMS rebalancing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas admissible pour le rebalancement de service de gestion de portefeuille.")); }

        // Actions
	};
}



