#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_purchase_non_bell_for_deposit_27 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_purchase_non_bell_for_deposit_27() { }
		~CIFast_IFast_ifastcbo_warn_purchase_non_bell_for_deposit_27() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PURCHASE_NON_BELL_FOR_DEPOSIT_27")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Non back-end load fund chosen for Deposit Type 27.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Non back-end load fund chosen for Deposit Type 27.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un fonds sans frais de rachat a été choisi pour le code de dépôt 27.")); }

        // Actions
	};
}



