#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_inactive_sales_rep : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_inactive_sales_rep() { }
		~CIFast_Infrastructure_ifastcbo_err_inactive_sales_rep() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INACTIVE_SALES_REP")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value %VALUE% is not valid for field %FIELD%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The value '^' is not valid for field '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert %VALUE% ist nicht gültig für das Feld %FIELD%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor %VALUE% no es válido para el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur %VALUE% est invalide pour le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde %VALUE% is niet geldig voor veld %FIELD%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen gültigen Wert ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur valide.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer een geldige waarde in")); }
	};
}



