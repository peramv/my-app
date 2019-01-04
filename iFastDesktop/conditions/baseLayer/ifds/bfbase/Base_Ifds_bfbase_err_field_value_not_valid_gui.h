#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfbase_err_field_value_not_valid_gui : public CConditionObject
	{
	public:
		CBase_Ifds_bfbase_err_field_value_not_valid_gui() { }
		~CBase_Ifds_bfbase_err_field_value_not_valid_gui() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_VALUE_NOT_VALID_GUI")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value is not valid for the field.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The value is not valid for the field.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este valor no es válido para el campo (%FIELD%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur invalide pour le champ")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De waarde is niet geldig voor het veld.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Enter a valid value.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Introduzca un valor válido.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur valide.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer een geldige waarde in.")); }
	};
}



