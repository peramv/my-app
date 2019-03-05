#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_cashsweep : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_cashsweep() { }
		~CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_cashsweep() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NOT_ELIGIBLE_TARGET_FUND_CASHSWEEP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not eligible for Target Fund Cash Sweep.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds cible non permis pour le terme automatique d'investissement.")); }	

        // Actions
	};
}
