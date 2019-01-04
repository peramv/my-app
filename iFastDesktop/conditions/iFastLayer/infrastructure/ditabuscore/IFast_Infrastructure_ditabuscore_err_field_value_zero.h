#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_field_value_zero : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_field_value_zero() { }
		~CIFast_Infrastructure_ditabuscore_err_field_value_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_VALUE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be greater than zero. Type a value greater than zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^ must be greater than zero. Type a value greater than zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss größer als Null sein. Geben Sie einen Wert ein, der größer als Null ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% debe ser mayor que cero. Escriba un valor mayor que cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% doit être supérieur à zéro. Entrez une valeur supérieure à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet groter dan nul zijn. Typ een waarde groter dan nul")); }

        // Actions
	};
}



