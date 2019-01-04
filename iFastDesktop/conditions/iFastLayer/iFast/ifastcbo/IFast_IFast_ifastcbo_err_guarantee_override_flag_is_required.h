#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_guarantee_override_flag_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_guarantee_override_flag_is_required() { }
		~CIFast_IFast_ifastcbo_err_guarantee_override_flag_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GUARANTEE_OVERRIDE_FLAG_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please choose if you need to override the Guarantees updating option as ‘Recalculation based on MV’, (Yes/No).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez indiquer s'il est nécessaire de changer l'option de mise à jour des garanties pour un recalcul basé sur la VM : Oui/Non.")); }

        // Actions
	};
}



