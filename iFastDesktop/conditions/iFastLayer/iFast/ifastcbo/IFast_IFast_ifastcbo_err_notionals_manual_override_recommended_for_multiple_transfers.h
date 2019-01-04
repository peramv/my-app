#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_notionals_manual_override_recommended_for_multiple_transfers : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_notionals_manual_override_recommended_for_multiple_transfers() { }
		~CIFast_IFast_ifastcbo_err_notionals_manual_override_recommended_for_multiple_transfers() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Manual Override of notionals is recommended for multiple transfers.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'écrasement manuel des valeurs notionnelles est recommandé pour les transferts multiples.")); }		

        // Actions
	};
}



