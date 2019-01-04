#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_err_invalid_field_length : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_err_invalid_field_length() { }
		~CBase_Infrastructure_ditabuscore_err_invalid_field_length() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FIELD_LENGTH")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be %LENGTH% characters long.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^ must be ^ characters long.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss %LENGTH% Zeichen lang sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% debe tener %LENGTH% caracteres.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ doit être composé de %LENGTH% caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet %LENGTH% tekens lang zijn")); }

        // Actions
	};
}



