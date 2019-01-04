#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_currency_mismatch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_currency_mismatch() { }
		~CIFast_IFast_ifastcbo_err_currency_mismatch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CURRENCY_MISMATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank account currency: %bankcurr% and %transdescription% currency: %syscurr% do not match.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bank account currency: %bankcurr% and %transdescription% currency: %syscurr% do not match.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie du compte bancaire %bankcurr% et la monnaie %transdescription% : %syscurr% ne correspondent pas.")); }

        // Actions
	};
}



