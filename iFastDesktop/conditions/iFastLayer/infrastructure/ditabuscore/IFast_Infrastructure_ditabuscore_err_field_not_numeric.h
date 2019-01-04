#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_field_not_numeric : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_field_not_numeric() { }
		~CIFast_Infrastructure_ditabuscore_err_field_not_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_NOT_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be numeric. Type a numeric value.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FIELD% must be numeric. Type a numeric value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss nummerisch sein. Geben Sie einen nummerischen Wert ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% debe ser numérico. Escriba un valor numérico.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% doit être numérique. Entrez une valeur numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet numeriek zijn. Typ een numerieke waarde")); }

        // Actions
	};
}



