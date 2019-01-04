#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_field_is_under_minimum_allowed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_field_is_under_minimum_allowed() { }
		~CIFast_Infrastructure_dicbocore_err_field_is_under_minimum_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_IS_UNDER_MINIMUM_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value %VALUE% is less than the minimum value allowed %MIN_VALUE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The value '^' is less than the minimum value allowed '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert %VALUE% ist kleiner als der erlaubte Minimalwert %MIN_VALUE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor %VALUE% es menor que el valor mínimo permitido %MIN_VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur %VALUE% est inférieure à la valeur minimale autorisée %MIN_VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De waarde %VALUE% is kleiner dan de toegestane minimumwaarde %MIN_VALUE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a value greater than the minimum allowed.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Saisissez une valeur superieure a la valeur minimum autorisee.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen Wert ein, der größer als der erlaubte Minimalwert ist.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter a value greater than the minimum allowed.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur supérieure au minimum autorisé.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer een waarde in die groter is dan de minimum toegestane waarde")); }
	};
}



