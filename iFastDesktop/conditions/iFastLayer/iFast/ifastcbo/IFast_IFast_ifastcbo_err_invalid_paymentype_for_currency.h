#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_paymentype_for_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_paymentype_for_currency() { }
		~CIFast_IFast_ifastcbo_err_invalid_paymentype_for_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PAYMENTYPE_FOR_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid payment type for selected currency.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de paiement invalide pour la monnaie sélectionnée")); }

        // Actions
	};
}



