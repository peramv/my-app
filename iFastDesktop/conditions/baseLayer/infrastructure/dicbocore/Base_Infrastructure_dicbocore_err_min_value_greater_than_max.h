#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_min_value_greater_than_max : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_min_value_greater_than_max() { }
		~CBase_Infrastructure_dicbocore_err_min_value_greater_than_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MIN_VALUE_GREATER_THAN_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. The minimum value allowed %MIN_VALUE% is greater than the maximum value allowed %MAX_VALUE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. The minimum value allowed '^' is greater than the maximum value allowed '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Der erlaubte Minimalwert %MIN_VALUE% ist größer als der erlaubte Maximalwert %MAX_VALUE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El valor mínimo permitido %MIN_VALUE% es mayor que el valor máximo permitido %MAX_VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La valeur minimale autorisée %MIN_VALUE% est supérieure à la valeur maximale autorisée %MAX_VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. De toegestane minimumwaarde %MIN_VALUE% is groter dan de toegestane maximumwaarde %MAX_VALUE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



