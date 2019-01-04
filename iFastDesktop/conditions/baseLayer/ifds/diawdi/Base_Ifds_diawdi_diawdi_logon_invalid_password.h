#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawdi_diawdi_logon_invalid_password : public CConditionObject
	{
	public:
		CBase_Ifds_diawdi_diawdi_logon_invalid_password() { }
		~CBase_Ifds_diawdi_diawdi_logon_invalid_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_INVALID_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The received string can not be correctly converted into unicode for codepage %CODEPAGE%.  Reason: %RC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vor dem Stopdatum muss das Effektivdatum kommen. Bitte geben Sie das Stopdatum neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The received string can not be correctly converted into unicode for codepage %CODEPAGE%.  Reason: %RC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La chaîne reçue ne peut être convertie correctement à Unicode pour la page de codes %CODEPAGE%. Raison : %RC%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The received string can not be correctly converted into unicode for codepage %CODEPAGE%.  Reason: %RC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact system support")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact system support")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact system support")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec le soutien informatique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact system support")); }
	};
}



