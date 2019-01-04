#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_nscc_currency_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_nscc_currency_invalid() { }
		~CIFast_IFast_ifastcbo_err_nscc_currency_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NSCC_CURRENCY_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Currency is not valid for NSCC payment type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Currency is not valid for NSCC payment type.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Currency is not valid for NSCC payment type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Monnaie invalide pour le type de paiement NSCC")); }

        // Actions
	};
}



