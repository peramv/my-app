#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_not_eligible_fctrfr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_not_eligible_fctrfr() { }
		~CIFast_IFast_ifastcbo_err_fund_not_eligible_fctrfr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_ELIGIBLE_FCTRFR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% is not eligible for Foreign Content Rebalancing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %FUND% is not eligible for Foreign Content Rebalancing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund %FUND% is not eligible for Foreign Content Rebalancing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% n'est pas admissible pour le rebalancement de contenu étranger.")); }

        // Actions
	};
}



