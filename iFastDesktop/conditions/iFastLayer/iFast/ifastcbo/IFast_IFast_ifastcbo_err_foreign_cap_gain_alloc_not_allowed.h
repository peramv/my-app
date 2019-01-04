#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_foreign_cap_gain_alloc_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_foreign_cap_gain_alloc_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_foreign_cap_gain_alloc_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FOREIGN_CAP_GAIN_ALLOC_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Foreign Cap Gain Alloc Adjustment not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ajustement de répartition des gains de capitaux étrangers n'est pas autorisé.")); }

        // Actions
	};
}



