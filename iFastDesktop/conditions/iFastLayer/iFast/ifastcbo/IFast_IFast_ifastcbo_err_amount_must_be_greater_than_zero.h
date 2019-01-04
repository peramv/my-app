#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_must_be_greater_than_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_must_be_greater_than_zero() { }
		~CIFast_IFast_ifastcbo_err_amount_must_be_greater_than_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be greater than 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss größer als Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser mayor que cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet groter dan nul zijn")); }

        // Actions
	};
}



