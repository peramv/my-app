#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_corresponding_distribution_payment_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_corresponding_distribution_payment_missing() { }
		~CIFast_IFast_ifastcbo_warn_corresponding_distribution_payment_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CORRESPONDING_DISTRIBUTION_PAYMENT_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please enter corresponding Distribution Payment Instruction")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez entrer les instructions de paiement de distribution correspondantes.")); }

        // Actions
	};
}



