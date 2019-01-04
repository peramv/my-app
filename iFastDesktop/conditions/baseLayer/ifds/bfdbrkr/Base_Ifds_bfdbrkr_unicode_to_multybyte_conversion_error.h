#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdbrkr_unicode_to_multybyte_conversion_error : public CConditionObject
	{
	public:
		CBase_Ifds_bfdbrkr_unicode_to_multybyte_conversion_error() { }
		~CBase_Ifds_bfdbrkr_unicode_to_multybyte_conversion_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("UNICODE_TO_MULTYBYTE_CONVERSION_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The unicode string can not be correctly converted into dbcs string for codepage %CODEPAGE%.  Reason: %RC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Instituts-Code existiert nicht. Bitte geben Sie neu ein oder drücken Sie F4, um eine Liste mit gültigen Banken einzusehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The unicode string can not be correctly converted into dbcs string for codepage %CODEPAGE%.  Reason: %RC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La chaîne Unicode ne peut être convertie corrrectement en chaîne de jeu de caractères à deux octets pour la page de codes %CODEPAGE%. Raison : %RC%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The unicode string can not be correctly converted into dbcs string for codepage %CODEPAGE%.  Reason: %RC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact system support")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact system support")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact system support")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec le soutien informatique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact system support")); }
	};
}



