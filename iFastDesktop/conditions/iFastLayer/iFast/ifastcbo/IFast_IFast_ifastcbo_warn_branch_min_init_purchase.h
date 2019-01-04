#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_branch_min_init_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_branch_min_init_purchase() { }
		~CIFast_IFast_ifastcbo_warn_branch_min_init_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BRANCH_MIN_INIT_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Branch: Less then minimum Initial Purchase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unité de service : inférieur à l'achat initial minimal")); }

        // Actions
	};
}



