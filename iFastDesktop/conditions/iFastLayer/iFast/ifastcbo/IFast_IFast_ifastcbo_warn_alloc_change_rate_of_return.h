#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_alloc_change_rate_of_return : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_alloc_change_rate_of_return() { }
		~CIFast_IFast_ifastcbo_warn_alloc_change_rate_of_return() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ALLOC_CHANGE_RATE_OF_RETURN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Changing the allocation may affect the Rate of Return calculation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un changement de la répartition pourrait toucher le calcul du taux de remboursement.")); }

        // Actions
	};
}



