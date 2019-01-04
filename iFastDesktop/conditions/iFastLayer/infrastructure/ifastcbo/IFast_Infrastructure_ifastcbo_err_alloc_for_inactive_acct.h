#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_alloc_for_inactive_acct : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_alloc_for_inactive_acct() { }
		~CIFast_Infrastructure_ifastcbo_err_alloc_for_inactive_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOC_FOR_INACTIVE_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value %VALUE% is greater than the maximum allowed value %MAX_VALUE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The value '^' is greater than the maximum allowed value '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert %VALUE% ist größer als der erlaubte Maximalwert %MAX_VALUE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor %VALUE% es mayor que el valor máximo permitido %MAX_VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur %VALUE% est supérieure à la valeur maximale autorisée %MAX_VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De waarde %VALUE% is groter dan de toegestane maximumwaarde %MAX_VALUE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a value less than the maximum allowed.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Saisissez une valeur inferieure a la valeur maximum autorisee.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen Wert ein, der kleiner als der erlaubte Maximalwert ist.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter a value less than the maximum allowed.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur inférieure au maximum autorisé.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer een waarde in die kleiner is dan de maximum toegestane waarde")); }
	};
}



