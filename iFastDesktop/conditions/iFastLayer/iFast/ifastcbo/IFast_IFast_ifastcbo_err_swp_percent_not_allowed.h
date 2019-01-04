#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_swp_percent_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_swp_percent_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_swp_percent_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SWP_PERCENT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percent is not allowed for SWP transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour cent non autorisée pour la transaction PRP")); }

        // Actions
	};
}



