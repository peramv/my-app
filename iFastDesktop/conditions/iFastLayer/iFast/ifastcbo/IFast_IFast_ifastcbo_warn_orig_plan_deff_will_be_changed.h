#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_orig_plan_deff_will_be_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_orig_plan_deff_will_be_changed() { }
		~CIFast_IFast_ifastcbo_warn_orig_plan_deff_will_be_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ORIG_PLAN_DEFF_WILL_BE_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Original Plan date will be overridden with the calculated value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date du régime d'origine sera modifiée avec la valeur calculée.")); }

        // Actions
	};
}



