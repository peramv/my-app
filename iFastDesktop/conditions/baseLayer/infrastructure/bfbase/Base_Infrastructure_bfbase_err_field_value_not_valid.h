#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfbase_err_field_value_not_valid : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfbase_err_field_value_not_valid() { }
		~CBase_Infrastructure_bfbase_err_field_value_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_VALUE_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value %VALUE% is not valid for field %FIELD%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The value '^' is not valid for field '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert %VALUE% ist nicht gültig für das Feld %FIELD%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La propiedad no existe en el índice %index%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur %VALUE% est invalide pour le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eigenschap bestaat niet in index %index%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen gültigen Wert ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el archivo de propiedades")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur valide.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



