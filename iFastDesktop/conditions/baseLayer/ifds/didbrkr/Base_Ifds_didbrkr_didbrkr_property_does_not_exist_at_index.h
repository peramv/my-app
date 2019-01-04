#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_property_does_not_exist_at_index : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_property_does_not_exist_at_index() { }
		~CBase_Ifds_didbrkr_didbrkr_property_does_not_exist_at_index() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value is not valid for the field (%FIELD%).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The value %VALUE% is not valid for field %TAG%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert ist nicht gültig für das Feld.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este valor no es válido para el campo (%FIELD%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur est invalide pour le champ (%FIELD%).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De waarde is niet geldig voor het veld (%FIELD%)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen gültigen Wert ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Introduzca un valor válido.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur valide.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer een geldige waarde in.")); }
	};
}



