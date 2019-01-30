#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_giamaturity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_giamaturity() { }
		~CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_giamaturity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NOT_ELIGIBLE_TARGET_FUND_GIA_MATURITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not eligible for Target Fund GIA Maturity/Interest.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("Non admissible aux intérêts/échéances du CPG du Fonds cible.")); }	

        // Actions
	};
}
