#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_yes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_yes() { }
		~CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_yes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GUARANTEE_OVERRIDE_FLAG_IS_YES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You have chosen the Guarantees updating overrides option of ‘Recalculation based on MV’ as \"Yes\"")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous avez choisi l'option de modification de mise à jour des garanties pour un recalcul basé sur la VM (Oui).")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter to confirm")); }
	};
}



