#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_unknown_exception : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_unknown_exception() { }
		~CIFast_Infrastructure_dicbocore_err_unknown_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Repeat count element not found for %props%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Repeat count element not found for %props%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wiederholungs-Zählelement nicht gefunden für %props%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. Se detectó una excepción desconocida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Une exception inconnue a été détectée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Er is een onbekende exceptie aangetroffen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



