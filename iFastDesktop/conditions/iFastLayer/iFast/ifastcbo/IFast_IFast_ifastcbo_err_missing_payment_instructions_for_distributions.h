#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_payment_instructions_for_distributions : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_payment_instructions_for_distributions() { }
		~CIFast_IFast_ifastcbo_err_missing_payment_instructions_for_distributions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing pay to entity payment instructions for distribution.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de paiement du Paiement à l'entité pour la distribution sont manquantes.")); }

        // Actions
	};
}



