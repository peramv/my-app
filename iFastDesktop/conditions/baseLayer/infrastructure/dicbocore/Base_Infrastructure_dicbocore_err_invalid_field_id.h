#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_invalid_field_id : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_invalid_field_id() { }
		~CBase_Infrastructure_dicbocore_err_invalid_field_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FIELD_ID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% is an invalid field ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^' is an invalid field ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% ist eine ungültige Feld-ID.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% es una identificación de campo no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FIELD% est un code de champ invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% is een ongeldig veld-ID")); }

        // Actions
	};
}



