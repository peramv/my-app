#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_payins_should_be_eft : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_payins_should_be_eft() { }
		~CIFast_IFast_ifastcbo_warn_payins_should_be_eft() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PAYINS_SHOULD_BE_EFT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PayType for requested Payment Instruction should be set to EFT for Redemption payments")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de paiement pour les instructions de paiement requises devrait être réglé à TEF pour les paiements de rachat.")); }

        // Actions
	};
}



