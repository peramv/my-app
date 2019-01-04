#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_eligible_transfer_flag_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_eligible_transfer_flag_changed() { }
		~CIFast_IFast_ifastcbo_warn_eligible_transfer_flag_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ELIGIBLE_TRANSFER_FLAG_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Changing the Transfer % will override the Eligible Transfer to No.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le changement du pourcentage de transfert modifiera le transfert admissible à Non.")); }

        // Actions
	};
}



