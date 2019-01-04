#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ordertype_direct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ordertype_direct() { }
		~CIFast_IFast_ifastcbo_warn_ordertype_direct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ORDERTYPE_DIRECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order type should be direct for non-participant transfers.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'ordre devrait être direct pour les transferts de non-participants.")); }

        // Actions
	};
}



