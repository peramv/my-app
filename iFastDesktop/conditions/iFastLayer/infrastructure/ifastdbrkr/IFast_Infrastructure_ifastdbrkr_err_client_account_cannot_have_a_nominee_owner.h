#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner() { }
		~CIFast_Infrastructure_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLIENT_ACCOUNT_CANNOT_HAVE_A_NOMINEE_OWNER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Return with errors.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Return with errors.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Ausgabe fehlerhaft.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El sistema devolvió errores.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Renvoi avec erreurs.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Geretourneerd met fouten")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



