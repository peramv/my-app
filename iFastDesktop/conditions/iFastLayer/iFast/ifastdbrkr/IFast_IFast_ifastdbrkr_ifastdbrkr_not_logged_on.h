#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_not_logged_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_not_logged_on() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_not_logged_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_NOT_LOGGED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User needs to log on first.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("User needs to log on first.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Benutzer muss sich erst anmelden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario debe conectarse primero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur doit d'abord se connecter.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker moet zich eerst aanmelden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Log on and retry operation.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Log on and retry operation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Melden Sie sich an und versuchen Sie, diesen Schritt erneut auszuführen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Log on and retry operation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ouvrez une session et réessayez l'opération.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Meld u aan en voer de bewerking opnieuw uit")); }
	};
}



