#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_no : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_no() { }
		~CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_no() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GUARANTEE_OVERRIDE_FLAG_IS_NO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You have chosen the Guarantees updating overrides option of ‘Recalculation based on MV’ as \"No\"")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous n'avez pas choisi l'option de modification de mise à jour des garanties pour un recalcul basé sur la VM (Non).")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter to confirm")); }
	};
}



