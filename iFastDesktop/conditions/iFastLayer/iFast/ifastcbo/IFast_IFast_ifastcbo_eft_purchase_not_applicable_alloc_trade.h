#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_eft_purchase_not_applicable_alloc_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_eft_purchase_not_applicable_alloc_trade() { }
		~CIFast_IFast_ifastcbo_eft_purchase_not_applicable_alloc_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("EFT_PURCHASE_NOT_APPLICABLE_ALLOC_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("EFT Purchase is not applicable for Allocation Trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un achat TEF n'est pas applicable à une transaction de répartition.")); }

        // Actions
	};
}



