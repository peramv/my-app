#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_currencyoption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_currencyoption() { }
		~CIFast_IFast_ifastcbo_err_invalid_currencyoption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CURRENCYOPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("\"Payment in Settlement Currency\" is only valid for \"Redemption\" or \"Distribution\"")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paiement en monnaie de règlement n'est valide que pour le rachat ou la distribution.")); }

        // Actions
	};
}



